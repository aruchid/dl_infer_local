#pragma once
#include "../Base/display_base_impl.h"

namespace display_process
{
    class DisplayProcessDet : public DisplayBaseImpl
    {
    public:
        DisplayProcessDet();
        virtual ~DisplayProcessDet();

        // 实现基类接口
        bool Init() override;
        DISPLAY_STATUS Process(const cv::Mat& image, const infer_process::st_infer_result& result) override;
        cv::Mat GetDisplayImage() const override;
        infer_process::INFER_TYPE GetType() const override;
        void SetDisplayParams(const st_display_params& params) override;

    private:
        // 绘制检测框的参数
        struct DetDisplayParams
        {
            cv::Scalar box_color = cv::Scalar(0, 255, 0);  // 框的颜色
            int line_thickness = 2;                         // 线条粗细
            float font_scale = 0.5f;                       // 字体大小
            bool show_confidence = true;                    // 是否显示置信度
            bool show_class_id = true;                     // 是否显示类别ID
        };

        DetDisplayParams det_params_;
    };

    // 导出函数声明
    extern "C" {
        ARC_DISPLAY_PROCESS_EXPORT DisplayBaseImpl* CreateDisplayImpl();
        ARC_DISPLAY_PROCESS_EXPORT void DeleteDisplayImpl(DisplayBaseImpl* impl);
    }

} // namespace display_process 