#include "../include/ncnnRay.hpp"


int main(int argc, char *argv[]) {
    VisionUtils vu = VisionUtils();


    bool use_vulkan_compute = false;
    int gpu_device = -1;
    if (vu.isGPU() & 0 > 1) {
        use_vulkan_compute = true;
        gpu_device = 0;
    }
    // default options
    ncnn::Option opt = vu.optGPU(use_vulkan_compute, gpu_device);

    std::string model_path = ".";
    std::string fileName = "manga.png";
    LFFD lffd1(model_path, 5, 0, opt, g_vkdev);


    const int screenWidth = 1200;
    const int screenHeight = 800;
    Image image = LoadImage(fileName.c_str());   // Loaded in CPU memory (RAM)
    ImageResize(&image, image.width / 2, image.height / 2);
    InitWindow(screenWidth, screenHeight, "random values (c++17)");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        vu.detectFacesAndDrawOnImage(lffd1, image);
        ImageFormat(&image, UNCOMPRESSED_R8G8B8A8);
        Texture2D texture = LoadTextureFromImage(image);
        DrawTexture(texture, screenHeight / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2, WHITE);
        BeginDrawing();
        ClearBackground(RAYWHITE);
//            DrawText("Generate a random value on the GPU/CPU using PyTorch", 30, 100, 20, MAROON);
        EndDrawing();
        UnloadTexture(texture);
    }

    CloseWindow();        // Close window and OpenGL context
    return 0;
}


