#include "../include/ncnnRay.hpp"

int main(int argc, char *argv[]) {
    VisionUtils vu = VisionUtils();

    std::string model_path = ".";
    std::string fileName="faces.png";

    vu.getGPU();
    // initialize when app starts
//    ncnn::create_gpu_instance();// line1
    // enable vulkan compute feature before loading
//    ncnn::Net net;
//    net.opt.use_vulkan_compute = 1;// line2
    // enable vulkan compute feature before loading
//    model.opt.use_vulkan_compute = 1;
    bool useGPU = false;
    LFFD lffd1(model_path, 8, 0, useGPU);
//    lffd1.opt.use_vulkan_compute = 1;

    const int screenWidth = 800;
    const int screenHeight = 600;
    Image image = LoadImage(fileName.c_str());   // Loaded in CPU memory (RAM)


//
    InitWindow(screenWidth, screenHeight, "random values (c++17)");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        vu.detectFacesAndDrawOnImage(lffd1, image);

        ImageFormat(&image,UNCOMPRESSED_R8G8B8A8);
        Texture2D texture = LoadTextureFromImage(image);
        DrawTexture(texture, screenWidth - texture.width - 60, screenHeight / 2 - texture.height / 2, WHITE);
        BeginDrawing();
            ClearBackground(RAYWHITE);
//            DrawText("Generate a random value on the GPU/CPU using PyTorch", 30, 100, 20, MAROON);
        EndDrawing();
        UnloadTexture(texture);
    }

    CloseWindow();        // Close window and OpenGL context
    return 0;
}


