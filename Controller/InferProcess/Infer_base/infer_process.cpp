#include "infer_process.h"
#include "infer_process_impl.h"
#include <mutex>
#include <boost/filesystem.hpp>
#include <QSysInfo>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

static std::mutex g_infer_mutex;

namespace infer_process
{
    typedef InferProcessImpl* (*FuncCreateImpl)();
    typedef void (*FuncDeleteImpl)(InferProcessImpl*);
    //=====================================================

    InferProcess::InferProcess()
    {
    }

    InferProcess::~InferProcess()
    {
        Release();
    }

    bool InferProcess::Load(st_infer_cfg& cfg)
    {
        Release();

        std::lock_guard<std::mutex> lock(g_infer_mutex);

        INFER_TYPE type = GetInferType(cfg);
        if (type == INFER_TYPE_UNKNOWN)
        {
            return false;
        }

        // 查找对应的库名称
        const char* library_name = nullptr;
        for (int i = 0; i < MODEL_TYPE_COUNT; ++i)
        {
            if (MODEL_TYPE_INFO[i].type == type)
            {
                library_name = MODEL_TYPE_INFO[i].library_name;
                break;
            }
        }

        if (!library_name)
        {
            return false;
        }

        QString app_path = QCoreApplication::applicationDirPath();
        m_lib = new QLibrary(QDir::toNativeSeparators(app_path + "/" + library_name));

        if (m_lib)
        {
            if (!m_lib->load())
            {
                qWarning() << "Library load fail: " << m_lib->errorString();
                return false;
            }
            
            FuncCreateImpl func = (FuncCreateImpl)(m_lib->resolve("CreateInferImpl"));
            if (func)
            {
                m_impl = func();
                if (m_impl)
                {
                    if (m_impl->Load(cfg))
                    {
                        m_is_valid = true;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void InferProcess::Release()
    {
        std::lock_guard<std::mutex> lock(g_infer_mutex);
        
        if (m_lib)
        {
            FuncDeleteImpl func = (FuncDeleteImpl)(m_lib->resolve("DeleteInferImpl"));
            if (func)
            {
                func(m_impl);
                m_impl = nullptr;
            }
            m_lib->unload();
            m_lib = nullptr;
        }
        m_is_valid = false;
    }

    bool InferProcess::IsValid()
    {
        return m_is_valid;
    }

    void InferProcess::Infer(st_infer_unit* p_unit, int batch_size)
    {
        std::lock_guard<std::mutex> lock(g_infer_mutex);
        if (m_is_valid && m_impl)
        {
            m_impl->Infer(p_unit, batch_size);
        }
    }

    int InferProcess::BatchSize()
    {
        std::lock_guard<std::mutex> lock(g_infer_mutex);
        if (m_impl)
        {
            return m_impl->BatchSize();
        }
        return 0;
    }

    const char* InferProcess::GetModelInfo()
    {
        std::lock_guard<std::mutex> lock(g_infer_mutex);
        if (m_impl)
        {
            return m_impl->GetModelInfo();
        }
        return "";
    }

    INFER_TYPE InferProcess::GetInferType(st_infer_cfg& cfg)
    {
        // 如果配置中已指定类型，直接返回
        if (cfg.type != INFER_TYPE_UNKNOWN)
        {
            return cfg.type;
        }

        // 根据文件扩展名判断类型
        using namespace boost::filesystem;
        path model_path(cfg.model_path);
        
        if (exists(model_path))
        {
            std::string ext = model_path.extension().string();
            // 遍历类型信息表查找匹配的扩展名
            for (int i = 0; i < MODEL_TYPE_COUNT; ++i)
            {
                if (ext == MODEL_TYPE_INFO[i].extension)
                {
                    return MODEL_TYPE_INFO[i].type;
                }
            }
        }
        
        return INFER_TYPE_UNKNOWN;
    }

} // namespace infer_process 