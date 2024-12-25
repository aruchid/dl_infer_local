#pragma once
#include "../Base/result_process_base.h"

namespace display_process
{
    class SegmentationProcess : public ResultProcessBase
    {
    public:
        SegmentationProcess();
        virtual ~SegmentationProcess();

        // 实现基类接口
        bool Init() override;
        void Process(const cv::Mat& image, const infer_process::st_infer_result& result) override;
        cv::Mat GetDisplayImage() const override;
        infer_process::INFER_TYPE GetType() const override;
        void SetDisplayParams(const std::string& params) override;

    private:
        // 分割结果显示参数
        struct DisplayParams
        {
            float alpha = 0.5f;                    // 混合透明度
            bool show_mask = true;                 // 是否显示掩码
            bool show_contour = true;              // 是否显示轮廓
            cv::Scalar contour_color = cv::Scalar(0, 255, 0);  // 轮廓颜色
            int contour_thickness = 2;             // 轮廓线条粗细
        };

        DisplayParams params_;
    };

} // namespace display_process 