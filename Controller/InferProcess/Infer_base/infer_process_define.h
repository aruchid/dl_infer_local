#pragma once
#include <vector>
#include <string>

#if defined(ARC_INFER_PROCESS_LIB)
#  define ARC_INFER_PROCESS_EXPORT Q_DECL_EXPORT
#else
#  define ARC_INFER_PROCESS_EXPORT Q_DECL_IMPORT
#endif

namespace infer_process
{
    /*******************************************************************************
     * 推理模型类型
     * 
     * 要增加新的推理类型需要完成以下步骤:
     * 1. 在INFER_TYPE枚举中添加新类型
     * 2. 在MODEL_TYPE_INFO数组中添加对应的类型信息
     * 3. 实现对应的动态库,并确保库名与MODEL_TYPE_INFO中的library_name一致
     * 
     * 注意事项:
     * - 动态库名称必须与MODEL_TYPE_INFO中定义的一致
     * - 新增类型需要同时更新相关文档
     * - 确保新增类型的实现符合接口规范
     ******************************************************************************/
    enum INFER_TYPE
    {
        INFER_TYPE_UNKNOWN,
        INFER_TYPE_DETECTION,    // 目标检测
        INFER_TYPE_SEGMENTATION, // 语义分割
        INFER_TYPE_CLASSIFICATION,// 图像分类
        INFER_TYPE_OCR           // OCR文字识别
    };

    // 模型类型信息
    struct st_model_type_info
    {
        INFER_TYPE type;            // 模型类型
        const char* extension;       // 文件扩展名
        const char* library_name;    // 动态库名称
    };

    // 支持的模型类型信息列表
    static const st_model_type_info MODEL_TYPE_INFO[] = {
        {INFER_TYPE_DETECTION,     ".det", "infer_process_detection"},
        {INFER_TYPE_SEGMENTATION,  ".seg", "infer_process_segmentation"},
        {INFER_TYPE_CLASSIFICATION,".cls", "infer_process_classification"},
        {INFER_TYPE_OCR,          ".ocr", "infer_process_ocr"}
    };

    static const int MODEL_TYPE_COUNT = sizeof(MODEL_TYPE_INFO) / sizeof(MODEL_TYPE_INFO[0]);


    // 配置结构体
    struct st_infer_cfg
    {
        INFER_TYPE type = INFER_TYPE_UNKNOWN;
        int device_id = 0;           // CPU/GPU设备ID
        char model_path[260];        // 模型文件路径
        float conf_threshold = 0.5f;  // 置信度阈值
    };

    // 输入图像结构
    struct st_input_image 
    {
        unsigned char* data = nullptr;  // 图像数据
        int width = 0;                 // 宽度
        int height = 0;                // 高度
        int channels = 3;              // 通道数
    };

    // 检测结果结构
    struct st_detect_result 
    {
        float x, y, w, h;     // 边界框
        float confidence;      // 置信度
        int class_id;         // 类别ID
    };

    // OCR文本行结构
    struct st_ocr_text_line
    {
        std::string text;         // 识别的文本内容
        float confidence;         // 置信度
        float x, y, w, h;        // 文本框位置
        float angle;             // 文本方向角度
    };

    // OCR结果结构
    struct st_ocr_result
    {
        std::vector<st_ocr_text_line> text_lines;  // 文本行列表
        int line_count = 0;                        // 文本行数量
    };

    // 推理结果单元
    struct st_infer_result
    {
        std::vector<st_detect_result> detections;  // 检测结果
        st_ocr_result ocr;                        // OCR结果
        int result_count = 0;                     // 结果数量
    };

    // 推理单元(包含输入和输出)
    struct st_infer_unit
    {
        st_input_image input;        // 输入图像
        st_infer_result result;      // 推理结果
    };

} // namespace infer_process 