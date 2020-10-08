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
    Image ncnnToRayImage(ncnn::Mat  &tensor);
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
//    if (bytesPerPixel==4) bytesPerPixel=3;

    auto pointer = new unsigned char[dataSize];
    const unsigned char *imagePointer = (unsigned char *) image.data;
    std::memcpy(pointer, imagePointer, dataSize);

//    error C2664: 'ncnn::Mat ncnn::Mat::from_pixels(const unsigned char *,int,int,int,ncnn::Allocator *)': cannot convert argument 1 from 'void *const ' to 'const unsigned char *'
//    ncnn::Mat tensor = ncnn::Mat::from_pixels(static_cast<const unsigned char *>(image.data), ncnn::Mat::PIXEL_BGR2RGB, width, height);
    ncnn::Mat tensor = ncnn::Mat::from_pixels(static_cast<const unsigned char *>(image.data), ncnn::Mat::PIXEL_RGBA, width, height);
    delete[] pointer;
    return tensor;
}

Image VisionUtils::ncnnToRayImage(ncnn::Mat  &tensor) {
    size_t width = tensor.w;
    size_t height = tensor.h;
    unsigned char* torchPointer = reinterpret_cast<unsigned char *>(RL_MALLOC(3 * height * width * sizeof(unsigned char)));
    tensor.to_pixels(torchPointer, ncnn::Mat::PIXEL_RGB);
//    return Image{0};
    return Image{
            torchPointer,
            (int) width,
            (int) height,
            1, //that line is mipmaps, keep as 1
            UNCOMPRESSED_R8G8B8}; //its an enum specifying formar, 8 bit R, 8 bit G, 8 bit B, no alpha UNCOMPRESSED_R8G8B8A8 UNCOMPRESSED_R8G8B8
}
