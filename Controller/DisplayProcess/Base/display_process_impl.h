#pragma once
#include "display_process_define.h"

namespace display_process
{
    class DisplayProcessImpl
    {
    public:
        DisplayProcessImpl() {}
        virtual ~DisplayProcessImpl() {}

        // 初始化处理器
        virtual bool Init() = 0;

        // 处理结果
        virtual DISPLAY_STATUS Process(const cv::Mat& image, const infer_process::st_infer_result& result) = 0;

        // 获取处理后的图像
        virtual cv::Mat GetDisplayImage() const = 0;

        // 获取处理器类型
        virtual infer_process::INFER_TYPE GetType() const = 0;

        // 设置显示参数
        virtual void SetDisplayParams(const st_display_params& params) = 0;

    protected:
        cv::Mat display_image_;          // 处理后的显示图像
        st_display_params params_;       // 显示参数
    };

} // namespace display_process 