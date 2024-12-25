#pragma once
#include "result_process_base.h"
#include <memory>

namespace display_process
{
    class DisplayProcess
    {
    public:
        DisplayProcess();
        ~DisplayProcess();

        // 初始化显示处理器
        bool Init(infer_process::INFER_TYPE type);

        // 处理并显示结果
        void ProcessResult(const cv::Mat& image, const infer_process::st_infer_result& result);

        // 获取处理后的图像
        cv::Mat GetDisplayImage() const;

        // 设置显示参数
        void SetDisplayParams(const std::string& params);

    private:
        std::shared_ptr<ResultProcessBase> processor_;  // 当前使用的结果处理器
    };

} // namespace display_process 