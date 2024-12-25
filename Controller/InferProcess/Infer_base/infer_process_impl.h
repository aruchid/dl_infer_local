#pragma once
#include "infer_process_define.h"

namespace infer_process
{
    class InferProcessImpl
    {
    public:
        InferProcessImpl() {}
        virtual ~InferProcessImpl() {}

        // 加载模型
        virtual bool Load(st_infer_cfg& cfg) = 0;
        
        // 执行推理
        virtual void Infer(st_infer_unit* p_unit, int batch_size) = 0;
        
        // 获取批处理大小
        virtual int BatchSize() = 0;
        
        // 获取模型信息
        virtual const char* GetModelInfo() = 0;
    };

} // namespace infer_process 