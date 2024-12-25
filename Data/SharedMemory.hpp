#pragma once
#include <mutex>
#include <opencv2/core.hpp>

class SharedMemory {
public:
    SharedMemory();
    
    // 图像帧的读写操作
    void writeFrame(const cv::Mat& frame);
    cv::Mat readFrame();
    
    // 推理结果的读写操作
    void writeInferenceResult(const std::vector<float>& result);
    std::vector<float> readInferenceResult();

private:
    std::mutex frameMutex_;
    std::mutex resultMutex_;
    cv::Mat currentFrame_;
    std::vector<float> inferenceResult_;
}; 