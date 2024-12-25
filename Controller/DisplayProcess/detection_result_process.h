#pragma once
#include "result_process_base.h"

namespace display_process
{
    class DetectionResultProcess : public ResultProcessBase
    {
    public:
        DetectionResultProcess();
        virtual ~DetectionResultProcess();

        // 实现基类接口
        bool Init() override;
        void Process(const cv::Mat& image, const infer_process::st_infer_result& result) override;
        cv::Mat GetDisplayImage() const override;
        infer_process::INFER_TYPE GetType() const override;
        void SetDisplayParams(const std::string& params) override;

    private:
        // 绘制检测框的参数
        struct DisplayParams
        {
            cv::Scalar box_color = cv::Scalar(0, 255, 0);  // 框的颜色
            int line_thickness = 2;                         // 线条粗细
            float font_scale = 0.5f;                       // 字体大小
            bool show_confidence = true;                    // 是否显示置信度
            bool show_class_id = true;                     // 是否显示类别ID
        };

        DisplayParams params_;
    };

} // namespace display_process 