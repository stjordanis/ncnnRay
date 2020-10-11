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

    Image image = LoadImage(fileName.c_str());   // Loaded in CPU memory (RAM)

    ImageResize(&image, image.width / 2, image.height / 2);
    vu.detectFacesAndDrawOnImage(lffd1, image);
    ImageFormat(&image, UNCOMPRESSED_R8G8B8A8);
    ExportImage(image, "manga-ncnn-rgb.png");


}


