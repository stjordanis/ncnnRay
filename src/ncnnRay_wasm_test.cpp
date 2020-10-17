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

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 1200;
int screenHeight = 800;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame

//----------------------------------------------------------------------------------
// Main Enry Point
//----------------------------------------------------------------------------------
Texture2D texture;
Image image ={0};

int main()
{
    bool use_vulkan_compute = false;
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

    ncnn::Option opt = optGPU(use_vulkan_compute, gpu_device);
    TraceLog(LOG_INFO, "ncnnRay: Opt using vulkan::%i", opt.use_vulkan_compute);
    // Initialization
    //--------------------------------------------------------------------------------------
    const char *mainTitle = "ncnnRay: Model Studio";
    InitWindow(screenWidth, screenHeight, mainTitle);
    const char * torchStyle="resources/torch2.rgs";
    GuiLoadStyle(torchStyle);
    GuiFade(0.9f);
    GuiSetStyle(DEFAULT, TEXT_SPACING, 1);
    // TTF Font loading with custom generation parameters
    Font font = LoadFontEx("resources/GameCube.ttf", 18, 0, 0);

    Color defTextCLR = GetColor(GuiGetStyle(DEFAULT, LINE_COLOR));

    std::string fileName = "resources/faces.png";
    image = LoadImage(fileName.c_str());
    texture = LoadTextureFromImage(image);

//    SetTextureFilter(GetFontDefault().texture, FILTER_POINT); // Fix for HighDPI display problems
//    SetTextureFilter(font.texture, FILTER_BILINEAR)

//    GuiPanel(Rectangle{0, 0, (float) GetScreenWidth(), (float) GetScreenHeight()});

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(DARKGRAY);
    DrawFPS(10, 10);
//    DrawText("ncnn AI in the browser", 360, 370, 30, WHITE);

    DrawTextEx(GuiGetFont(),"ncnn AI model studio. Drop a PNG image here.",Vector2 { 10, (float)GetScreenHeight() - 52 },
               19,0.0f,WHITE);
    DrawTextEx(GuiGetFont(),"ncnnRay++",Vector2 { 10, 40},19,1.0f,WHITE);

    // Load a dropped TTF file dynamically (at current fontSize)
    if (IsFileDropped())
    {
        int count = 0;
        char **droppedFiles = GetDroppedFiles(&count);

        // NOTE: We only support first ttf file dropped
        if (IsFileExtension(droppedFiles[0], ".png"))
        {
            image = LoadImage(droppedFiles[0]);
            texture = LoadTextureFromImage(image);
            ClearDroppedFiles();
        }
    }

    DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

////#include "../../include/ncnnRay.hpp"
//
//#define RAYGUI_IMPLEMENTATION
//#define RAYGUI_SUPPORT_RICONS
//#include "../include/raygui/raygui.h"
//#include "../include/raygui/ricons.h"
//
//
//
//#if EMSCRIPTEN
//#include <emscripten.h>
//#endif
//
//
//int main() {
//    SetConfigFlags(FLAG_VSYNC_HINT); // Enable V-SYNC.
//
//    const int screenWidth = 800;
//    const int screenHeight = 600;
//    InitWindow(screenWidth, screenHeight, "PONC");
//
//    const char *mainTitle = "ncnnRay: Model Studio";
//    InitWindow(screenWidth, screenHeight, mainTitle);
////    Font gamefont = LoadFont("GameCube.ttf");
////    Sound clickSound = LoadSound("save.ogg");
////    Sound saveImageSound = LoadSound("click.ogg");
//
//    const char *torchStyle = "torch2.rgs";
//    GuiLoadStyle(torchStyle);
//    GuiFade(0.9f);
//    GuiSetStyle(DEFAULT, TEXT_SPACING, 1);
//    Color defTextCLR = GetColor(GuiGetStyle(DEFAULT, LINE_COLOR));
//
//    SetTargetFPS(60);
//    // Set all game variables.
//    // Player paddle vars.
//    int plPosX = 10;
//    int plPosY = 285;
//    // Enemy paddle vars.
//    int enPosX = 1260;
//    int enPosY = 285;
//    // Paddle shared vars.
//    int paSizX = 10;
//    int paSizY = 150;
//    // Ball vars.
//    int baPosX = 22;
//    int baPosY = 356;
//    int baVelX = 2;
//
//    // Main game loop.
//    while (!WindowShouldClose()) {
//        int baVelY = GetRandomValue(-6, 7);
//        int baSizA = GetRandomValue(8, 25);
//
//        // Player paddle movement.
//        if ((IsKeyDown(KEY_UP)) && (plPosY > 5)) plPosY -= 2;
//        else if ((IsKeyDown(KEY_DOWN)) && (plPosY + 150 < 715)) plPosY += 2;
//        // Enemy paddle movement.
//        if (baPosX > 640) {
//            if ((enPosY + 70 > baPosY) && (enPosY > 5)) enPosY -= 2;
//            else if ((enPosY + 80 < baPosY) && (enPosY + 150 < 715)) enPosY += 2; }
//        // Paddle - Ball collison.
//        if ((baPosX <= plPosX + 10) && (baPosY >= plPosY) && (baPosY <= plPosY + paSizY)) baVelX = -baVelX;
//        else if ((baPosX >= enPosX - 10) && (baPosY >= enPosY) && (baPosY <= enPosY + paSizY)) {
//            baVelX = -baVelX;
//            baVelY = GetRandomValue(-2, 2); }
//        // Edge - Ball collsion.
//        if (baPosY < 5) baVelY = -baVelY;
//        else if (baPosY + 8 > 715) baVelY = -baVelY;
//        // Ball movement and Game Over logic.
//        if ((baPosX > 10) && (baPosX < 1270)) {
//            baPosX += baVelX;
//            baPosY += baVelY;
//        } else { break; }
//        // Draw to screen.
//        BeginDrawing();
//        ClearBackground(DARKGRAY);
//        // Player paddle
//        DrawRectangle(plPosX, plPosY, paSizX, paSizY, RAYWHITE);
//        // Enemy paddle.
//        DrawRectangle(enPosX, enPosY, paSizX, paSizY, DARKGREEN);
//        // Ball.
//        DrawRectangle(baPosX, baPosY, baSizA, baSizA, RED);
//        EndDrawing();
//    }
//}
//
