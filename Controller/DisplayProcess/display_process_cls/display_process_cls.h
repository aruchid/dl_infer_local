#pragma once
#include "../Base/display_base_impl.h"

namespace display_process
{
    class DisplayProcessCls : public DisplayBaseImpl
    {
    public:
        DisplayProcessCls();
        virtual ~DisplayProcessCls();

        // 实现基类接口
        bool Init() override;
        DISPLAY_STATUS Process(const cv::Mat& image, const infer_process::st_infer_result& result) override;
        cv::Mat GetDisplayImage() const override;
        infer_process::INFER_TYPE GetType() const override;
        void SetDisplayParams(const st_display_params& params) override;

    private:
        // 分类结果显示参数
        struct ClsDisplayParams
        {
            cv::Scalar text_color = cv::Scalar(0, 0, 255);  // 文本颜色
            float font_scale = 1.0f;                        // 字体大小
            int thickness = 2;                              // 文本粗细
            bool show_confidence = true;                    // 是否显示置信度
            cv::Point text_pos = cv::Point(30, 30);        // 文本位置
        };

        ClsDisplayParams cls_params_;
    };

    // 导出函数声明
    extern "C" {
        ARC_DISPLAY_PROCESS_EXPORT DisplayBaseImpl* CreateDisplayImpl();
        ARC_DISPLAY_PROCESS_EXPORT void DeleteDisplayImpl(DisplayBaseImpl* impl);
    }

} // namespace display_process 