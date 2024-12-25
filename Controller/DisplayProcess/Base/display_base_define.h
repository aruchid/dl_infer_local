#pragma once
#include "../../InferProcess/infer_process_define.h"
#include <opencv2/opencv.hpp>
#include <string>

#if defined(ARC_DISPLAY_PROCESS_LIB)
#  define ARC_DISPLAY_PROCESS_EXPORT Q_DECL_EXPORT
#else
#  define ARC_DISPLAY_PROCESS_EXPORT Q_DECL_IMPORT
#endif

namespace display_process
{
    // 显示处理类型
    enum DISPLAY_TYPE
    {
        DISPLAY_TYPE_UNKNOWN = -1,      // 未知类型
        DISPLAY_TYPE_DETECTION = 0,     // 目标检测显示
        DISPLAY_TYPE_SEGMENTATION,      // 分割显示
        DISPLAY_TYPE_CLASSIFICATION,    // 分类显示
        DISPLAY_TYPE_OCR               // OCR显示
    };

    // 显示处理类型信息
    struct st_display_type_info
    {
        DISPLAY_TYPE type;                     // 显示处理类型
        infer_process::INFER_TYPE infer_type;  // 对应的推理类型
        const char* library_name;              // 动态库名称
        const char* type_name;                 // 类型名称
    };

    // 支持的显示处理类型列表
    static const st_display_type_info DISPLAY_TYPE_INFO[] = {
        {DISPLAY_TYPE_DETECTION,     infer_process::INFER_TYPE_DETECTION,     "display_process_det", "Detection"},
        {DISPLAY_TYPE_SEGMENTATION,  infer_process::INFER_TYPE_SEGMENTATION,  "display_process_seg", "Segmentation"},
        {DISPLAY_TYPE_CLASSIFICATION,infer_process::INFER_TYPE_CLASSIFICATION,"display_process_cls", "Classification"},
        {DISPLAY_TYPE_OCR,          infer_process::INFER_TYPE_OCR,          "display_process_ocr", "OCR"}
    };

    static const int DISPLAY_TYPE_COUNT = sizeof(DISPLAY_TYPE_INFO) / sizeof(DISPLAY_TYPE_INFO[0]);

    // 基本显示参数
    struct st_display_params
    {
        bool show_original = false;     // 是否显示原图
        bool show_result = true;        // 是否显示结果
        float alpha = 1.0f;             // 显示透明度
        int window_width = 800;         // 窗口宽度
        int window_height = 600;        // 窗口高度
        bool show_fps = true;           // 是否显示FPS
        bool show_info = true;          // 是否显示信息
    };

    // 显示结果状态
    enum DISPLAY_STATUS
    {
        DISPLAY_STATUS_SUCCESS = 0,     // 显示成功
        DISPLAY_STATUS_FAILED,          // 显示失败
        DISPLAY_STATUS_NO_RESULT,       // 无结果
        DISPLAY_STATUS_INVALID_PARAM,   // 无效参数
        DISPLAY_STATUS_NOT_INITIALIZED  // 未初始化
    };

    // 显示信息结构
    struct st_display_info
    {
        std::string model_name;         // 模型名称
        std::string type_name;          // 类型名称
        float fps = 0.0f;              // 当前FPS
        int frame_count = 0;           // 帧计数
        bool is_initialized = false;    // 是否已初始化
    };

} // namespace display_process 