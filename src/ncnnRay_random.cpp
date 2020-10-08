#define NOUSER //Resolve ray error  error C2660: 'LoadImageA': function does not take 1 arguments

#pragma once
#include <intrin.h> //Resolve ray error  ppltasks.h(2712): error C3861: '_ReturnAddress': identifier not found
#include "raylib.h"
#include "../include/utils/vision_utils.hpp"
#include <string>

#include "mat.h"
#include "prng.h"

static struct prng_rand_t g_prng_rand_state;
#define SRAND(seed) prng_srand(seed, &g_prng_rand_state)
#define RAND()      prng_rand(&g_prng_rand_state)

static ncnn::Mat RandomMat(int w, int h, int elempack)
{
    ncnn::Mat m(w, h, (size_t)elempack, elempack);

    unsigned char* p = m;
    for (int i = 0; i < w * h * elempack; i++)
    {
        p[i] = RAND() % 256;
    }

    return m;
}

int main(int argc, char *argv[]) {
    VisionUtils vu = VisionUtils();

    std::string model_path = ".";
    std::string fileName="face.png";
    std::string fileName1="140908_ISIS_Attkisson.png";

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "random random values (c++17)");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
//        ncnn::Mat a = RandomMat(350, 350, 3);
//        ncnn::Mat m = ncnn::Mat::from_pixels(a,ncnn::Mat::PIXEL_RGB, 350, 350);
        Image image = LoadImage(fileName.c_str());   // Loaded in CPU memory (RAM)
        ncnn::Mat inmat = vu.rayImageToNcnn(image);
        cout << "Total:" << inmat.total() << endl;
        cout << "D:" << vu.tensorDIMS(inmat) << endl;;

        ncnn::Mat to;
        ncnn::resize_bilinear(inmat,to,500,500);
        image=vu.ncnnToRayImage(to);
//        Image image = LoadImage("parrots.png");   // Loaded in CPU memory (RAM)
        ImageFormat(&image,UNCOMPRESSED_R8G8B8A8);
        Texture2D texture = LoadTextureFromImage(image);
        DrawTexture(texture, screenWidth - texture.width - 60, screenHeight / 2 - texture.height / 2, WHITE);

        BeginDrawing();
            ClearBackground(RAYWHITE);
//            DrawText("Generate a random value on the GPU/CPU using PyTorch", 30, 100, 20, MAROON);
        EndDrawing();

    }

    CloseWindow();        // Close window and OpenGL context
    return 0;
}


