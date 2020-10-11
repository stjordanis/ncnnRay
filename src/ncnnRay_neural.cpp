#include "models/neural.h"
#include <string>
#include <vector>


//class GlobalGpuInstance
//{
//public:
//    GlobalGpuInstance() { ncnn::create_gpu_instance(); }
//    ~GlobalGpuInstance() { ncnn::destroy_gpu_instance(); }
//};
//
//static const GlobalGpuInstance glb;

int main(int argc, char *argv[]) {

    bool use_vulkan_compute = true;
    int gpu_device = 0;

    g_blob_pool_allocator.clear();
    g_workspace_pool_allocator.clear();

#if NCNN_VULKAN
    if (use_vulkan_compute)
    {
        std::cout<< "Using vulkan?: " <<use_vulkan_compute <<std::endl;

        g_vkdev = ncnn::get_gpu_device(gpu_device);
        g_blob_vkallocator = new ncnn::VkBlobAllocator(g_vkdev);
        g_staging_vkallocator = new ncnn::VkStagingAllocator(g_vkdev);

        g_blob_vkallocator->clear();
        g_staging_vkallocator->clear();
    }
#endif // NCNN_VULKAN

    ncnn::Option opt = optGPU(use_vulkan_compute, gpu_device);

    std::string model_path = ".";
    std::string model_name = "candy";
    std::string fileName = "manga.png";

    NeuralStyle nstyle(model_path, model_name, 0, opt, g_vkdev);
    Image image = LoadImage(fileName.c_str());   // Loaded in CPU memory (RAM)

//    ImageResize(&image, image.width / 2, image.height / 2);
    Image saveImage = nstyle.applyStyleOnImage(image);
    ExportImage(saveImage, "manga-ncnn-rgb.png");

}