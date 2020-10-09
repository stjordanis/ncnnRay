#include "../include/utils/vision_utils.hpp" // MUST BE INCLUDED FIRST

void detectAndExport(VisionUtils &vu, LFFD &lffd0, const string &fileName);

int main(int argc, char** argv) {
    VisionUtils vu = VisionUtils();
    Image im={0};
//    Rectangle rect={0};
//    Rectangle imageRec = {0.0f};

    std::string model_path = ".";
    LFFD lffd0(model_path, 5, 0);
    LFFD lffd1(model_path, 8, 0);
    std::string fileName="faces.png";
    std::string fileName1="manga.png";
//    detectAndExport(vu, lffd0, fileName);
    detectAndExport(vu, lffd1, fileName);
    detectAndExport(vu, lffd1, fileName1);
    return 0;
}

void detectAndExport(VisionUtils &vu, LFFD &lffd, const string &fileName) {
    Image image = LoadImage(fileName.c_str());   // Loaded in CPU memory (RAM)
    vector<FaceInfo> face_info;
    ncnn::Mat inmat = vu.rayImageToNcnn(image);
    cout << "Total:" << inmat.total() << endl;
    cout << "D:" << vu.tensorDIMS(inmat) << endl;;
//    lffd0.detect(inmat, face_info, 240, 320);
    lffd.detect(inmat, face_info, image.height, image.width);
//    lffd.detect(inmat, face_info, 240, 320);

    cout << "Face detections:" << face_info.size() << endl;;
    ImageDrawRectangle(&image, 5, 20, 20, 20, DARKPURPLE);

    for (int i = 0; i < face_info.size(); i++) {

        cout << "Iteration:" << i << endl;;
        auto face = face_info[i];
//        ImageDrawRectangle(&image, face.x1, face.y1, face.x2 - face.x1, face.y2 - face.y1, BLUE);
//        Rectangle rec = { 0 };
        Rectangle rect ={face.x1, face.y1, face.x2 - face.x1, face.y2 - face.y1};

        ImageDrawRectangleLines(&image, rect,5, RED);
//        ImageDrawCircle(&image, face.x1, face.y1, 1, RED);
//        ImageDrawCircle(&image, face.x2, face.y2, 6, RED);
        ImageDrawCircleV(&image, Vector2 {(float)face.x1, (float)face.y1}, 5, BLUE);
//        const char * txt=FormatText("%i",i);
//        ImageDrawText(&image, Vector2 {(float)face.x1, (float)face.y1},txt, 8.0, RED);
    }
    string exportFile=fileName + ".exp.png";
    ExportImage(image, exportFile.c_str());
}
