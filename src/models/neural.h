//#pragma once
#include "gpu.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include<vector>
#include<iostream>
#include<algorithm>
#include<numeric>
#include<map>
#include<string>
#include "net.h"

#include "styletransfer.id.h"
#include "styletransfer.param.bin.h"

static ncnn::Net styletransfernet[5];

class NeuralStyle {
public:
    NeuralStyle(const std::string &model_path, const std::string &model_name, int num_thread_,
                const ncnn::Option &opt,ncnn::VulkanDevice *device);
    ~NeuralStyle();

    ncnn::Mat transform(ncnn::Mat &in);

private:

private:
    ncnn::Net net;
};


