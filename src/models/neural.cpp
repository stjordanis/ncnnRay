#include "neural.h"

NeuralStyle::NeuralStyle(const std::string &model_path,
                         const std::string &model_name,
                         int num_thread_, const ncnn::Option &opt,
                         ncnn::VulkanDevice *device) {

    net.opt = opt;
    if (net.opt.use_vulkan_compute) {
        std::cout<< "Opt using vulkan:" <<net.opt.use_vulkan_compute <<std::endl;
        net.set_vulkan_device(device);
    }
//    std::string param = model_path + "/" + model_name +".param";
    std::string bin = model_path + "/" + model_name +".bin";
    net.load_param(styletransfer_param_bin);
//    net.load_param(styletransfer_param_bin[0]);
    net.load_model(bin.data());

}

NeuralStyle::~NeuralStyle() = default;

ncnn::Mat NeuralStyle::transform(ncnn::Mat &in) {
    // styletransfer
    ncnn::Mat out;
    {
        ncnn::Extractor ex = net.create_extractor();
//        #if NCNN_VULKAN
        if (net.opt.use_vulkan_compute) {
            ex.set_vulkan_compute(true);
            std::cout<< "ex using vulkan:" <<net.opt.use_vulkan_compute <<std::endl;
        }
//        #endif // NCNN_VULKAN
        ex.input(styletransfer_param_id::BLOB_input1, in);
        ex.extract(styletransfer_param_id::BLOB_output1, out);
    }

    return out;
}