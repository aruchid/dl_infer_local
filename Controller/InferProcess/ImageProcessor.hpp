#pragma once
#include <opencv2/core.hpp>
#include "../../Data/DataManager.hpp"

class ImageProcessor {
public:
    ImageProcessor();
    
    // 基础图像处理功能
    void preprocess(cv::Mat& frame);
    void postprocess(cv::Mat& frame);
    
    // 设置处理参数
    void setParameters(const ProcessingParameters& params);

private:
    ProcessingParameters params_;
    DataManager& dataManager_;
}; 