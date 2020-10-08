//#include <opencv2/opencv.hpp>
#define NOUSER //Resolve ray error  error C2660: 'LoadImageA': function does not take 1 arguments
#include <intrin.h> //Resolve ray error  ppltasks.h(2712): error C3861: '_ReturnAddress': identifier not found
#include <iostream>
#include "models/LFFD.h"
#include "raylib.h"
#include "../include/utils/vision_utils.hpp"

//using namespace cv;

int main(int argc, char** argv) {

    VisionUtils vu=VisionUtils();
    std::string model_path = ".";

	LFFD lffd(model_path,5,0);

    Image image = LoadImage("face.png");   // Loaded in CPU memory (RAM)

//	cv::Mat image = cv::imread(image_file);
//
    std::vector<FaceInfo> face_info;
    ncnn::Mat inmat =vu.rayImageToNcnn(image);

    std::cout<<"Total:" << inmat.total() <<std::endl;
    std::cout<<"D:" << vu.tensorDIMS (inmat) <<std::endl;;


//	ncnn::Mat inmat = ncnn::Mat::from_pixels(frame.data, ncnn::Mat::PIXEL_BGR, frame.cols, frame.rows);
	lffd.detect(inmat, face_info, 240, 320);

    std::cout<<"Face detections:" << face_info.size() <<std::endl;;
//    ImageDrawRectangle(&image, 5, 20, 100, 100, ORANGE);

//	for (int i = 0; i < face_info.size(); i++)
//	{
//		auto face = face_info[i];
//		cv::Point pt1(face.x1, face.y1);
//		cv::Point pt2(face.x2, face.y2);
//		cv::rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0), 2);
//	}
//
//	cv::namedWindow("lffd", CV_WINDOW_NORMAL);
//	cv::imshow("lffd", frame);
//	cv::waitKey();
	return 0;
}