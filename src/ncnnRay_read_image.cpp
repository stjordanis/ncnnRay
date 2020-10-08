
#define NOUSER //Resolve ray error  error C2660: 'LoadImageA': function does not take 1 arguments
#include <intrin.h> //Resolve ray error  ppltasks.h(2712): error C3861: '_ReturnAddress': identifier not found
#include <iostream>
#include "raylib.h"
#include "models/centerface.h"
#include "../include/utils/vision_utils.hpp"

int main(int argc, char** argv) {

    VisionUtils vu=VisionUtils();
    std::string model_path = ".";
    Image image = LoadImage("parrots.png");   // Loaded in CPU memory (RAM)
    std::vector<FaceInfo> face_info;
    ncnn::Mat inmat =vu.rayImageToNcnn(image);

    std::cout<<"Total:" << inmat.total() <<std::endl;
    std::cout<<"D:" << vu.tensorDIMS (inmat) <<std::endl;;

    Image saveImage=vu.ncnnToRayImage(inmat);
    ExportImage(saveImage, "x.png");

    return 0;
}