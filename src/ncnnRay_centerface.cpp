#undef Rectangle
#pragma warning( push, 0 )
#pragma warning( disable : 4576 )
#include "raylib.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#undef STB_IMAGE_WRITE_IMPLEMENTATION
//#include "../include/stbi/stb_image_write.h"
//#include <opencv2/opencv.hpp>
#define NOUSER //Resolve ray error  error C2660: 'LoadImageA': function does not take 1 arguments
#include <intrin.h> //Resolve ray error  ppltasks.h(2712): error C3861: '_ReturnAddress': identifier not found
#include <iostream>

#include "../include/utils/vision_utils.hpp"
#include "models/LFFD.h"


void detectAndExport(VisionUtils &vu, LFFD &lffd0, const string &fileName);

int main(int argc, char** argv) {
    VisionUtils vu = VisionUtils();
    Image im={0};
//    Rectangle rect={0};
//    Rectangle imageRec = {0.0f};

    std::string model_path = ".";
    LFFD lffd0(model_path, 5, 0);
    LFFD lffd1(model_path, 8, 0);
    std::string fileName="faces.png";
    std::string fileName1="manga.png";
//    detectAndExport(vu, lffd0, fileName);
    detectAndExport(vu, lffd1, fileName);
    detectAndExport(vu, lffd1, fileName1);
    return 0;
}

void detectAndExport(VisionUtils &vu, LFFD &lffd, const string &fileName) {
    Image image = LoadImage(fileName.c_str());   // Loaded in CPU memory (RAM)
    vector<FaceInfo> face_info;
    ncnn::Mat inmat = vu.rayImageToNcnn(image);
    cout << "Total:" << inmat.total() << endl;
    cout << "D:" << vu.tensorDIMS(inmat) << endl;;
//    lffd0.detect(inmat, face_info, 240, 320);
    lffd.detect(inmat, face_info, image.height, image.width);
//    lffd.detect(inmat, face_info, 240, 320);

    cout << "Face detections:" << face_info.size() << endl;;
    ImageDrawRectangle(&image, 5, 20, 20, 20, DARKPURPLE);

    for (int i = 0; i < face_info.size(); i++) {

        cout << "Iteration:" << i << endl;;
        auto face = face_info[i];
        ImageDrawRectangle(&image, face.x1, face.y1, face.x2 - face.x1, face.y2 - face.y1, BLUE);
        Rectangle rec = { 0 };
//        Rectangle rect ={face.x1, face.y1, face.x2 - face.x1, face.y2 - face.y1};

//        ImageDrawRectangleLines(&image, r,3, DARKPURPLE);
//        ImageDrawCircle(&image, face.x1, face.y1, 1, RED);
//        ImageDrawCircle(&image, face.x2, face.y2, 6, RED);
        ImageDrawCircleV(&image, Vector2 {(float)face.x1, (float)face.y1}, 3, RED);
        const char * txt=FormatText("%i",i);
//        ImageDrawText(&image, Vector2 {(float)face.x1, (float)face.y1},txt, 8.0, RED);
    }
    string exportFile=fileName + ".exp.png";
    ExportImage(image, exportFile.c_str());
}
























//Image cat = LoadImage("resources/cat.png");             // Load image in CPU memory (RAM)
//ImageCrop(&cat, (Rectangle){ 100, 10, 280, 380 });      // Crop an image piece
//ImageFlipHorizontal(&cat);                              // Flip cropped image horizontally
//ImageResize(&cat, 150, 200);                            // Resize flipped-cropped image
//
//Image parrots = LoadImage("resources/parrots.png");     // Load image in CPU memory (RAM)
//
//// Draw one image over the other with a scaling of 1.5f
//ImageDraw(&parrots, cat, (Rectangle){ 0, 0, cat.width, cat.height }, (Rectangle){ 30, 40, cat.width*1.5f, cat.height*1.5f }, WHITE);
//ImageCrop(&parrots, (Rectangle){ 0, 50, parrots.width, parrots.height - 100 }); // Crop resulting image
//
//// Draw on the image with a few image draw methods
//ImageDrawPixel(&parrots, 10, 10, RAYWHITE);
//ImageDrawCircle(&parrots, 10, 10, 5, RAYWHITE);
//ImageDrawRectangle(&parrots, 5, 20, 10, 10, RAYWHITE);

//        ImageDrawRectangleLines
//        ImageDrawRectangle(&image,
//                           face.x1,
//                           face.y1,
//                           face.x2 - face.x1,
//                           face.y2- face.y1, WHITE);

//        Rectangle frameRec =  {0};
//        Rectangle{ 0.0f, 0.0f, (float)image.width, (float)image.height };

//	    Rectangle  rect = {face.x1, face.y1,face.x2 - face.x1,face.y2- face.y1};

//        ImageDrawRectangleLines(&image,rect,2, WHITE);
