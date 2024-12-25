#pragma once
#include "../InferProcess/infer_process_define.h"
#include <opencv2/opencv.hpp>

namespace display_process
{
    class ResultProcessBase
    {
    public:
        ResultProcessBase() {}
        virtual ~ResultProcessBase() {}

        // 初始化处理器
        virtual bool Init() = 0;

        // 处理结果
        virtual void Process(const cv::Mat& image, const infer_process::st_infer_result& result) = 0;

        // 获取处理后的图像
        virtual cv::Mat GetDisplayImage() const = 0;

        // 获取处理器类型
        virtual infer_process::INFER_TYPE GetType() const = 0;

        // 设置显示参数
        virtual void SetDisplayParams(const std::string& params) = 0;

    protected:
        cv::Mat display_image_;  // 处理后的显示图像
    };

} // namespace display_process 