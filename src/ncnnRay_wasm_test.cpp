#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_RICONS
#include "../include/raygui/raygui.h"
#include "../include/raygui/ricons.h"


//#define PLATFORM_WEB

//#if defined(PLATFORM_WEB)
//#include <emscripten/emscripten.h>
//#endif

#if EMSCRIPTEN
#include <emscripten.h>
#endif

#include "models/LFFD.h"
#include "models/neural.h"
#include "models/FaceDetector.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 1200;
int screenHeight = 800;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(Detector &detector);     // Update and Draw one frame

void handleImageScaling(const int screenWidth, const int screenHeight, const Image &image, bool imageLoaded,
                        float &imageScale, Rectangle &imageRec);

void handleDroppedFiles(const int screenWidth, const int screenHeight, Image &image,
                        Texture2D &texture, bool &imageLoaded, float &imageScale);

//----------------------------------------------------------------------------------
// Main Enry Point
//----------------------------------------------------------------------------------
Image image = {0};
Texture2D texture = {0};
bool imageLoaded = false;
bool vidLoaded = false;
float imageScale = 1.0f;
float randomSeed = 0;
Rectangle imageRec = {0.0f};
const char *mainTitle = "ncnnRay: Model Studio";
Color defTextCLR = GetColor(GuiGetStyle(DEFAULT, LINE_COLOR));


// Default sizes.
float buttonWidth = 120;
float buttonHeight = 40;
float padding = 50;
float smallPadding = 40;
float leftPadding = 160;

auto statusBarRect = Rectangle{0, (float) GetScreenHeight() - 28, (float) GetScreenWidth(), 28};


std::unique_ptr<Detector> _det;

int main() {
    bool use_vulkan_compute = false;
#if EMSCRIPTEN
    use_vulkan_compute = false;
#endif
    int gpu_device = 0;

#if NCNN_VULKAN
    if (use_vulkan_compute) {
        std::cout << "Using vulkan?: " << use_vulkan_compute << std::endl;

        g_vkdev = ncnn::get_gpu_device(gpu_device);
        g_blob_vkallocator = new ncnn::VkBlobAllocator(g_vkdev);
        g_staging_vkallocator = new ncnn::VkStagingAllocator(g_vkdev);

        g_blob_vkallocator->clear();
        g_staging_vkallocator->clear();
    }
#endif // NCNN_VULKAN

    std::string model_path = ".";
    ncnn::Option opt = optGPU(use_vulkan_compute, gpu_device);
    TraceLog(LOG_INFO, "ncnnRay: Opt using vulkan::%i", opt.use_vulkan_compute);
//    LFFD lffd1(model_path, 8, 0, opt);
    Detector(model_path, opt, false);
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, mainTitle);
    const char *torchStyle = "torch2.rgs";
    GuiLoadStyle(torchStyle);
    GuiFade(0.9f);
    GuiSetStyle(DEFAULT, TEXT_SPACING, 1);
    // TTF Font loading with custom generation parameters
    Font font = LoadFontEx("GameCube.ttf", 18, 0, 0);
//    std::string fileName = "faces.png";
//    image = LoadImage(fileName.c_str());
//    texture = LoadTextureFromImage(image);

    GuiPanel(Rectangle{0, 0, (float) GetScreenWidth(), (float) GetScreenHeight()});

#if (PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame(detector), 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame(detector);
    }
#endif
    CloseWindow();        // Close window and OpenGL context
    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(Detector &detector) {
    handleDroppedFiles(screenWidth, screenHeight, image, texture, imageLoaded, imageScale);
    handleImageScaling(screenWidth, screenHeight, image, imageLoaded, imageScale, imageRec);
    BeginDrawing();
    ClearBackground(DARKGRAY);
    DrawFPS(10, 10);
    DrawTextEx(GuiGetFont(), mainTitle, Vector2{10, 40}, 19, 1.0f, WHITE);

    if (texture.id > 0) {
        if (texture.id > 0) {
            DrawTextureEx(texture, Vector2{screenWidth / 2 - (float) texture.width * imageScale / 2,
                                           screenHeight / 2 - (float) texture.height * imageScale / 2}, 0.0f,
                          imageScale, WHITE);
            DrawRectangleLinesEx(imageRec, 1,
                                 CheckCollisionPointRec(GetMousePosition(), imageRec) ? RED : DARKGRAY);
            DrawText(FormatText("SCALE: %.2f%%", imageScale * 100.0f), 10, screenHeight - 60, 20, defTextCLR);
        }

    } else {
        DrawTextEx(GuiGetFont(), "ncnnRay MODEL STUDIO: DRAG & DROP A PNG IMAGE HERE.",
                   Vector2{10, (float) GetScreenHeight() - 52},
                   19, 0.0f, WHITE);
        GuiDisable();
    }

    if (GuiButton(
            Rectangle{screenWidth - leftPadding, screenHeight - smallPadding - 4 * padding, buttonWidth, buttonHeight},
            "LFFD")) {
//        lffd1.detectFacesAndDrawOnImage(image);
        detector.detectFaces(image);
        TraceLog(LOG_INFO, "ncnnRay: LFFD");
        UnloadTexture(texture);
        texture = LoadTextureFromImage(image);
    }
    GuiEnable();
    EndDrawing();
    //----------------------------------------------------------------------------------
}

void handleImageScaling(const int screenWidth, const int screenHeight, const Image &image, bool imageLoaded,
                        float &imageScale, Rectangle &imageRec) {
    if (imageLoaded) {
        imageScale += (float) GetMouseWheelMove() * 0.15f;   // Image scale control
        if (imageScale <= 0.1f) imageScale = 0.1f;
        else if (imageScale >= 4) imageScale = 4;

        imageRec = Rectangle{screenWidth / 2 - (float) image.width * imageScale / 2,
                             screenHeight / 2 - (float) image.height * imageScale / 2,
                             (float) image.width * imageScale, (float) image.height * imageScale};
    }
}

void handleDroppedFiles(const int screenWidth, const int screenHeight, Image &image,
                        Texture2D &texture, bool &imageLoaded, float &imageScale) {
    if (IsFileDropped()) {
        int fileCount = 0;
        char **droppedFiles = GetDroppedFiles(&fileCount);

        if (fileCount == 1) {
            if (IsFileExtension(droppedFiles[0], ".png")) {
                TraceLog(LOG_INFO, "ncnnRay: image");
                Image imTemp = LoadImage(droppedFiles[0]);
                if (imTemp.data != nullptr) {
                    UnloadImage(image);
                    image = imTemp;
                    UnloadTexture(texture);
                    texture = LoadTextureFromImage(image);
                    imageLoaded = true;
                    if (texture.height > texture.width)
                        imageScale = (float) (screenHeight - 100) / (float) texture.height;
                    else imageScale = (float) (screenWidth - 100) / (float) texture.width;
                }
            }
        }
        ClearDroppedFiles();
    }
}