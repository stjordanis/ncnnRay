#include "../include/ncnnRay.hpp"
#include "models/LFFD.h"


int main(int argc, char *argv[]) {

    bool use_vulkan_compute = true;
    int gpu_device = 0;

    g_blob_pool_allocator.clear();
    g_workspace_pool_allocator.clear();

#if NCNN_VULKAN
    if (use_vulkan_compute)
    {
        std::cout<< "Using vulkan?: " <<use_vulkan_compute <<std::endl;

        g_vkdev = ncnn::get_gpu_device(gpu_device);
        g_blob_vkallocator = new ncnn::VkBlobAllocator(g_vkdev);
        g_staging_vkallocator = new ncnn::VkStagingAllocator(g_vkdev);

        g_blob_vkallocator->clear();
        g_staging_vkallocator->clear();
    }
#endif // NCNN_VULKAN

    ncnn::Option opt = optGPU(use_vulkan_compute, gpu_device);
    std::string model_path = ".";
    std::string fileName = "manga.png";

    LFFD lffd1(model_path, 8, 0, opt, g_vkdev);
    lffd1.detectFacesAndExportImage( fileName);

    const int screenWidth = 1200;
    const int screenHeight = 800;
    Image image = LoadImage(fileName.c_str());   // Loaded in CPU memory (RAM)
    ImageResize(&image, image.width / 2, image.height / 2);
    InitWindow(screenWidth, screenHeight, "random values (c++17)");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        lffd1.detectFacesAndDrawOnImage(image);
//        ImageFormat(&image, UNCOMPRESSED_R8G8B8A8);
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


