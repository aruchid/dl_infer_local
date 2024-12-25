#pragma once
#include "../Base/display_base_impl.h"

namespace display_process
{
    class DisplayProcessSeg : public DisplayBaseImpl
    {
    public:
        DisplayProcessSeg();
        virtual ~DisplayProcessSeg();

        // 实现基类接口
        bool Init() override;
        DISPLAY_STATUS Process(const cv::Mat& image, const infer_process::st_infer_result& result) override;
        cv::Mat GetDisplayImage() const override;
        infer_process::INFER_TYPE GetType() const override;
        void SetDisplayParams(const st_display_params& params) override;

    private:
        // 分割结果显示参数
        struct SegDisplayParams
        {
            float alpha = 0.5f;                    // 混合透明度
            bool show_mask = true;                 // 是否显示掩码
            bool show_contour = true;              // 是否显示轮廓
            cv::Scalar contour_color = cv::Scalar(0, 255, 0);  // 轮廓颜色
            int contour_thickness = 2;             // 轮廓线条粗细
        };

        SegDisplayParams seg_params_;
    };

    // 导出函数声明
    extern "C" {
        ARC_DISPLAY_PROCESS_EXPORT DisplayBaseImpl* CreateDisplayImpl();
        ARC_DISPLAY_PROCESS_EXPORT void DeleteDisplayImpl(DisplayBaseImpl* impl);
    }

} // namespace display_process 