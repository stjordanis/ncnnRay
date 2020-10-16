//#include "../include/ncnnRay.hpp"
#include "models/LFFD.h"

int main() {

    bool use_vulkan_compute = true;
    int gpu_device = 0;

//    g_blob_pool_allocator.clear();
//    g_workspace_pool_allocator.clear();

#if NCNN_VULKAN
    if (use_vulkan_compute) {
        std::cout << "Using vulkan?: " << use_vulkan_compute << std::endl;

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


    LFFD lffd1(model_path, 8, 0, opt);
    Image image = LoadImage(fileName.c_str());   // Loaded in CPU memory (RAM)
//    ImageResize(&image, image.width / 2, image.height / 2);
    lffd1.detectFacesAndDrawOnImage(image);
    ExportImage(image, "manga-ncnn-rgb.png");

}


