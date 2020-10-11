#include "../include/ncnnRay.hpp"

int main(int argc, char** argv) {
    VisionUtils vu=VisionUtils();


    // initialize when app starts
    vu.isGPU();
//    auto ins=ncnn::create_gpu_instance();// line1
//    std::cout<<"GPU instance=?:" << ins <<std::endl;;
//    auto g= ncnn::get_gpu_device(0);
//    std::cout<<"GPU Device=?:" << g <<std::endl;;

//    GPU instance=?:0
//    [0 GeForce GTX 1080]  queueC=2[8]  queueT=1[2]  memU=10  memDL=7  memHV=8
//    [0 GeForce GTX 1080]  fp16p=1  fp16s=1  fp16a=0  int8s=1  int8a=1
//    GPU Device=?:000001BD02A57F90

    //RGB
    Image image = LoadImage("faces.png");   // Loaded in CPU memory (RAM)
    ncnn::Mat inmat =vu.rayImageToNcnn(image);
    std::cout<<"Total:" << inmat.total() <<std::endl;
    std::cout<<"D:" << vu.tensorDIMS (inmat) <<std::endl;;
    Image saveImage=vu.ncnnToRayImage(inmat);
    ExportImage(saveImage, "faces-ncnn-rgb.png");

    Image imageRGBA = LoadImage("manga.png");   // Loaded in CPU memory (RAM)
    ncnn::Mat inmatimageRGBA =vu.rayImageToNcnn(imageRGBA);
    std::cout<<"Total:" << inmatimageRGBA.total() <<std::endl;
    std::cout<<"D:" << vu.tensorDIMS (inmatimageRGBA) <<std::endl;;
    Image saveImageimageRGBA=vu.ncnnToRayImage(inmatimageRGBA);
    ExportImage(saveImageimageRGBA, "manga-ncnn-rgba.png");

    //RGBA
    ncnn::destroy_gpu_instance();
    return 0;
}