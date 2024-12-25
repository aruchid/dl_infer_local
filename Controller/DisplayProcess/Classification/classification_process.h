#pragma once
#include "../Base/result_process_base.h"

namespace display_process
{
    class ClassificationProcess : public ResultProcessBase
    {
    public:
        ClassificationProcess();
        virtual ~ClassificationProcess();

        // 实现基类接口
        bool Init() override;
        void Process(const cv::Mat& image, const infer_process::st_infer_result& result) override;
        cv::Mat GetDisplayImage() const override;
        infer_process::INFER_TYPE GetType() const override;
        void SetDisplayParams(const std::string& params) override;

    private:
        // 分类结果显示参数
        struct DisplayParams
        {
            cv::Scalar text_color = cv::Scalar(0, 0, 255);  // 文本颜色
            float font_scale = 1.0f;                        // 字体大小
            int thickness = 2;                              // 文本粗细
            bool show_confidence = true;                    // 是否显示置信度
            cv::Point text_pos = cv::Point(30, 30);        // 文本位置
        };

        DisplayParams params_;
    };

} // namespace display_process 