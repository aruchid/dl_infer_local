#pragma once
#include "../Base/display_base_impl.h"

namespace display_process
{
    class DisplayProcessOcr : public DisplayBaseImpl
    {
    public:
        DisplayProcessOcr();
        virtual ~DisplayProcessOcr();

        // 实现基类接口
        bool Init() override;
        DISPLAY_STATUS Process(const cv::Mat& image, const infer_process::st_infer_result& result) override;
        cv::Mat GetDisplayImage() const override;
        infer_process::INFER_TYPE GetType() const override;
        void SetDisplayParams(const st_display_params& params) override;

    private:
        // OCR结果显示参数
        struct OcrDisplayParams
        {
            cv::Scalar text_color = cv::Scalar(255, 0, 0);   // 文本颜色
            cv::Scalar box_color = cv::Scalar(0, 255, 0);    // 框的颜色
            int line_thickness = 2;                          // 线条粗细
            float font_scale = 0.5f;                        // 字体大小
            bool show_confidence = true;                     // 是否显示置信度
            bool show_text_box = true;                      // 是否显示文本框
        };

        OcrDisplayParams ocr_params_;
    };

    // 导出函数声明
    extern "C" {
        ARC_DISPLAY_PROCESS_EXPORT DisplayBaseImpl* CreateDisplayImpl();
        ARC_DISPLAY_PROCESS_EXPORT void DeleteDisplayImpl(DisplayBaseImpl* impl);
    }

} // namespace display_process 