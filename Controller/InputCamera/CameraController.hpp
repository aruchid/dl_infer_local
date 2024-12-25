#pragma once
#include <opencv2/videoio.hpp>
#include "../../Data/DataManager.hpp"

class CameraController {
public:
    CameraController();
    ~CameraController();

    bool openCamera(int deviceId = 0);
    bool closeCamera();
    bool isOpened() const;
    bool captureFrame();

private:
    cv::VideoCapture camera_;
    DataManager& dataManager_;
}; 