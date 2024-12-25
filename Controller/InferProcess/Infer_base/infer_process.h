#pragma once
#include "infer_process_define.h"
#include <QLibrary>

namespace infer_process
{
    class InferProcessImpl;
    //======================================================
    class ARC_INFER_PROCESS_EXPORT InferProcess
    {
    public:
        InferProcess();
        ~InferProcess();

        // 加载模型
        bool Load(st_infer_cfg& cfg);
        
        // 释放资源
        void Release();
        
        // 检查模型是否有效
        bool IsValid();
        
        // 执行推理
        void Infer(st_infer_unit* p_unit, int batch_size);
        
        // 获取批处理大小
        int BatchSize();
        
        // 获取模型信息
        const char* GetModelInfo();

    private:
        // 获取实现类型
        INFER_TYPE GetInferType(st_infer_cfg& cfg);

    private:
        InferProcessImpl* m_impl = nullptr;     // 实现类指针
        QLibrary* m_lib = nullptr;              // 动态库
        bool m_is_valid = false;                // 模型是否有效
    };

} // namespace infer_process 