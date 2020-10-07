
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#undef STB_IMAGE_WRITE_IMPLEMENTATION
//#include "../include/stbi/stb_image_write.h"
//#include <opencv2/opencv.hpp>
#define NOUSER //Resolve ray error  error C2660: 'LoadImageA': function does not take 1 arguments
#include <intrin.h> //Resolve ray error  ppltasks.h(2712): error C3861: '_ReturnAddress': identifier not found
#include <iostream>
#include "raylib.h"
#include "centerface.h"
#include "../include/utils/vision_utils.hpp"

int main(int argc, char** argv) {

    VisionUtils vu=VisionUtils();
    std::string model_path = ".";
//	std::string image_file = argv[2];
    Centerface centerface;

    centerface.init(model_path);
//    Image image = {0};//ray
    Image image = LoadImage("parrots.png");   // Loaded in CPU memory (RAM)

//	cv::Mat image = cv::imread(image_file);
//
    std::vector<FaceInfo> face_info;
    ncnn::Mat inmat =vu.rayImageToNcnn(image);

    std::cout<<"Total:" << inmat.total() <<std::endl;
    std::cout<<"D:" << vu.tensorDIMS (inmat) <<std::endl;;

//	ncnn::Mat inmat = ncnn::Mat::from_pixels(image.data, ncnn::Mat::PIXEL_BGR2RGB, image.cols, image.rows);
    centerface.detect(inmat, face_info, image.width, image.height);
//
//	for (int i = 0; i < face_info.size(); i++) {
//		cv::rectangle(image, cv::Point(face_info[i].x1, face_info[i].y1), cv::Point(face_info[i].x2, face_info[i].y2), cv::Scalar(0, 255, 0), 2);
//		for (int j = 0; j < 5; j++) {
//			cv::circle(image, cv::Point(face_info[i].landmarks[2*j], face_info[i].landmarks[2*j+1]), 2, cv::Scalar(255, 255, 0), 2);
//		}
//	}
//	cv::imshow("test", image);
//	cv::waitKey();

    return 0;
}