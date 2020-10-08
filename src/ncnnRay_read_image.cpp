
#define NOUSER //Resolve ray error  error C2660: 'LoadImageA': function does not take 1 arguments
#include <intrin.h> //Resolve ray error  ppltasks.h(2712): error C3861: '_ReturnAddress': identifier not found
#include <iostream>
#include "raylib.h"
#include "../include/utils/vision_utils.hpp"

int main(int argc, char** argv) {

    VisionUtils vu=VisionUtils();

    //RGB
    Image image = LoadImage("parrots.png");   // Loaded in CPU memory (RAM)
    ncnn::Mat inmat =vu.rayImageToNcnn(image);
    std::cout<<"Total:" << inmat.total() <<std::endl;
    std::cout<<"D:" << vu.tensorDIMS (inmat) <<std::endl;;
    Image saveImage=vu.ncnnToRayImage(inmat);
    ExportImage(saveImage, "parrots-ncnn-rgb.png");

    Image imageRGBA = LoadImage("windmill.png");   // Loaded in CPU memory (RAM)
    ncnn::Mat inmatimageRGBA =vu.rayImageToNcnn(imageRGBA);
    std::cout<<"Total:" << inmatimageRGBA.total() <<std::endl;
    std::cout<<"D:" << vu.tensorDIMS (inmatimageRGBA) <<std::endl;;
    Image saveImageimageRGBA=vu.ncnnToRayImage(inmatimageRGBA);
    ExportImage(saveImageimageRGBA, "big-cat-ncnn-rgba.png");

    //RGBA

    return 0;
}