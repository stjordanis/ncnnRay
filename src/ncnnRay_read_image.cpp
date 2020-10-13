#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_RICONS

#include "../include/raygui/raygui.h"
#include "../bin64/_deps/raylib-src/src/external/glad.h"
#include "../include/raygui/ricons.h"


int main() {
    SetConfigFlags(FLAG_VSYNC_HINT); // Enable V-SYNC.

    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "PONC");

    const char *mainTitle = "ncnnRay: Model Studio";
    InitWindow(screenWidth, screenHeight, mainTitle);
    Font gamefont = LoadFont("GameCube.ttf");
    Sound clickSound = LoadSound("save.ogg");
    Sound saveImageSound = LoadSound("click.ogg");

    const char *torchStyle = "torch2.rgs";
    GuiLoadStyle(torchStyle);
    GuiFade(0.9f);
    GuiSetStyle(DEFAULT, TEXT_SPACING, 1);
    Color defTextCLR = GetColor(GuiGetStyle(DEFAULT, LINE_COLOR));

    SetTargetFPS(60);
    // Set all game variables.
    // Player paddle vars.
    int plPosX = 10;
    int plPosY = 285;
    // Enemy paddle vars.
    int enPosX = 1260;
    int enPosY = 285;
    // Paddle shared vars.
    int paSizX = 10;
    int paSizY = 150;
    // Ball vars.
    int baPosX = 22;
    int baPosY = 356;
    int baVelX = 2;

    // Main game loop.
    while (!WindowShouldClose()) {
        int baVelY = GetRandomValue(-6, 7);
        int baSizA = GetRandomValue(8, 25);

        // Player paddle movement.
        if ((IsKeyDown(KEY_UP)) && (plPosY > 5)) plPosY -= 2;
        else if ((IsKeyDown(KEY_DOWN)) && (plPosY + 150 < 715)) plPosY += 2;
        // Enemy paddle movement.
        if (baPosX > 640) {
            if ((enPosY + 70 > baPosY) && (enPosY > 5)) enPosY -= 2;
            else if ((enPosY + 80 < baPosY) && (enPosY + 150 < 715)) enPosY += 2; }
        // Paddle - Ball collison.
        if ((baPosX <= plPosX + 10) && (baPosY >= plPosY) && (baPosY <= plPosY + paSizY)) baVelX = -baVelX;
        else if ((baPosX >= enPosX - 10) && (baPosY >= enPosY) && (baPosY <= enPosY + paSizY)) {
            baVelX = -baVelX;
            baVelY = GetRandomValue(-2, 2); }
        // Edge - Ball collsion.
        if (baPosY < 5) baVelY = -baVelY;
        else if (baPosY + 8 > 715) baVelY = -baVelY;
        // Ball movement and Game Over logic.
        if ((baPosX > 10) && (baPosX < 1270)) {
            baPosX += baVelX;
            baPosY += baVelY;
        } else { break; }
        // Draw to screen.
        BeginDrawing();
        ClearBackground(DARKGRAY);
        // Player paddle
        DrawRectangle(plPosX, plPosY, paSizX, paSizY, RAYWHITE);
        // Enemy paddle.
        DrawRectangle(enPosX, enPosY, paSizX, paSizY, DARKGREEN);
        // Ball.
        DrawRectangle(baPosX, baPosY, baSizA, baSizA, RED);
        EndDrawing();
    }
}

//int main(int argc, char **argv) {
//
//
//    //RGB
//    Image image = LoadImage("faces.png");   // Loaded in CPU memory (RAM)
//    ncnn::Mat inmat = rayImageToNcnn(image);
//    std::cout << "Total:" << inmat.total() << std::endl;
//    std::cout << "D:" << tensorDIMS(inmat) << std::endl;;
//    Image saveImage = ncnnToRayImage(inmat);
//    ExportImage(saveImage, "faces-ncnn-rgb.png");
//
//    Image imageRGBA = LoadImage("manga.png");   // Loaded in CPU memory (RAM)
//    ncnn::Mat inmatimageRGBA = rayImageToNcnn(imageRGBA);
//    std::cout << "Total:" << inmatimageRGBA.total() << std::endl;
//    std::cout << "D:" << tensorDIMS(inmatimageRGBA) << std::endl;;
//    Image saveImageimageRGBA = ncnnToRayImage(inmatimageRGBA);
//    ExportImage(saveImageimageRGBA, "manga-ncnn-rgba.png");
//
//    //RGBA
//    ncnn::destroy_gpu_instance();
//    return 0;
//}