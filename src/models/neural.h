//#pragma once
#include "../../include/ncnnRay.hpp"
#include "styletransfer.id.h"
#include "styletransfer.param.bin.h"

static ncnn::Net styletransfernet[5];

class NeuralStyle {
public:
    NeuralStyle(const std::string &model_path, const std::string &model_name,
                const ncnn::Option &opt);

    ~NeuralStyle();

    Image applyStyleOnImage(Image &image);

    ncnn::Mat transform(ncnn::Mat &in);

private:

private:
    ncnn::Net net;
};


