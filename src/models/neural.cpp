#include "neural.h"

NeuralStyle::NeuralStyle(const std::string &model_path,
                         const std::string &model_name,
                         int num_thread_, const ncnn::Option &opt,
                         ncnn::VulkanDevice *device) {

    net.opt = opt;
    if (net.opt.use_vulkan_compute) {
        TraceLog(LOG_INFO, "ncnnRay: Opt using vulkan::%i", net.opt.use_vulkan_compute);
        net.set_vulkan_device(device);
    }
//    std::string param = model_path + "/" + model_name +".param";
    std::string bin = model_path + "/" + model_name +".bin";
    net.load_param(styletransfer_param_bin);
//    net.load_param(styletransfer_param_bin[0]);
    net.load_model(bin.data());

}

NeuralStyle::~NeuralStyle() = default;

Image NeuralStyle::applyStyleOnImage(Image &image) {
    ncnn::Mat inmat = rayImageToNcnn(image);
    cout << "Total:" << inmat.total() << endl;
    cout << "D:" << tensorDIMS(inmat) << endl;;
//    lffd0.detect(inmat, face_info, 240, 320);
    ncnn::Mat out=transform(inmat);
//    lffd.detect(inmat, face_info, 240, 320);

    Image saveImage =ncnnToRayImage(out);
    return saveImage;
//    ImageFormat(&image,UNCOMPRESSED_R8G8B8A8);
//    Texture2D texture = LoadTextureFromImage(image);
}

ncnn::Mat NeuralStyle::transform(ncnn::Mat &in) {
    // styletransfer
//    std::cout<< "styletransfer ex using vulkan in :" <<in.dims <<std::endl;
    ncnn::Mat out;
    {
        ncnn::Extractor ex = net.create_extractor();
        #if NCNN_VULKAN
//        if (net.opt.use_vulkan_compute)
//        {
//            net.set_vulkan_device(g_vkdev);
//            ex.set_vulkan_compute(true);
//            std::cout<< "ex using vulkan:" <<net.opt.use_vulkan_compute <<std::endl;
//        }
        #endif // NCNN_VULKAN

        ex.input(styletransfer_param_id::BLOB_input1, in);
        ex.extract(styletransfer_param_id::BLOB_output1, out);
//        std::cout<< "styletransfer ex finished out:" <<out.dims <<std::endl;
    }

    return out;
}