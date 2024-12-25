#pragma once
#include "result_process_base.h"
#include <memory>
#include <unordered_map>

namespace display_process
{
    class ResultProcessFactory
    {
    public:
        static ResultProcessFactory& Instance()
        {
            static ResultProcessFactory instance;
            return instance;
        }

        // 根据类型创建对应的结果处理器
        std::shared_ptr<ResultProcessBase> CreateProcessor(infer_process::INFER_TYPE type);

        // 注册新的处理器类型
        template<typename T>
        void RegisterProcessor(infer_process::INFER_TYPE type)
        {
            creators_[type] = []() { return std::make_shared<T>(); };
        }

    private:
        ResultProcessFactory() = default;
        ~ResultProcessFactory() = default;
        ResultProcessFactory(const ResultProcessFactory&) = delete;
        ResultProcessFactory& operator=(const ResultProcessFactory&) = delete;

        using CreatorFunc = std::function<std::shared_ptr<ResultProcessBase>()>;
        std::unordered_map<infer_process::INFER_TYPE, CreatorFunc> creators_;
    };

} // namespace display_process 