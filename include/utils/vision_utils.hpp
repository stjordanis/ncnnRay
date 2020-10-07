#pragma once
#include <iostream>
#include <chrono>
#include <iostream>
#include <typeinfo>
#include <thread>
#include <future>

#include "net.h"
#include "raylib.h"

using namespace std;
using namespace std::chrono;

class VisionUtils {
public:
    VisionUtils();

   int tensorDIMS(const ncnn::Mat &tensor);
    ncnn::Mat rayImageToNcnn(const Image &image);
};

VisionUtils::VisionUtils() {}

int VisionUtils::tensorDIMS(const ncnn::Mat &tensor){
    return tensor.dims;
}

ncnn::Mat VisionUtils::rayImageToNcnn(const Image &image) {
    size_t width = image.width;
    size_t height = image.height;
    int dataSize = GetPixelDataSize(width, height, image.format);
    TraceLog(LOG_INFO, "ncnnRay: total pixels:%i", dataSize);

    int bytesPerPixel = dataSize / (width * height);
    TraceLog(LOG_INFO, "ncnnRay: bytesPerPixel:%i", bytesPerPixel);
    if (bytesPerPixel==4) bytesPerPixel=3;

    auto pointer = new unsigned char[dataSize];
    const unsigned char *imagePointer = (unsigned char *) image.data;
    std::memcpy(pointer, imagePointer, dataSize);

//    error C2664: 'ncnn::Mat ncnn::Mat::from_pixels(const unsigned char *,int,int,int,ncnn::Allocator *)': cannot convert argument 1 from 'void *const ' to 'const unsigned char *'
    ncnn::Mat tensor = ncnn::Mat::from_pixels(static_cast<const unsigned char *>(image.data), ncnn::Mat::PIXEL_BGR2RGB, width, height);


//    auto tensor = torch::from_blob(pointer, {(int) height, (int) width, bytesPerPixel},
//                                   torch::kU8).clone().permute({2, 0, 1}).to(device);  // copy
    delete[] pointer;
    return tensor;
}


