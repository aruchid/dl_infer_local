#pragma once
#include "display_process_define.h"
#include <QLibrary>

namespace display_process
{
    class DisplayProcessImpl;
    //======================================================
    class ARC_DISPLAY_PROCESS_EXPORT DisplayProcess
    {
    public:
        DisplayProcess();
        ~DisplayProcess();

        // 初始化显示处理器
        bool Init(infer_process::INFER_TYPE type);

        // 处理并显示结果
        DISPLAY_STATUS Process(const cv::Mat& image, const infer_process::st_infer_result& result);

        // 获取处理后的图像
        cv::Mat GetDisplayImage() const;

        // 设置显示参数
        void SetDisplayParams(const st_display_params& params);

        // 释放资源
        void Release();

        // 检查是否有效
        bool IsValid() const;

    private:
        // 获取显示处理器类型
        const char* GetLibraryName(infer_process::INFER_TYPE type) const;

    private:
        DisplayProcessImpl* m_impl = nullptr;     // 实现类指针
        QLibrary* m_lib = nullptr;               // 动态库
        bool m_is_valid = false;                 // 是否有效
    };

} // namespace display_process 