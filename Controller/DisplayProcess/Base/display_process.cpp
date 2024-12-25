#include "display_process.h"
#include "display_process_impl.h"
#include <mutex>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

static std::mutex g_display_mutex;

namespace display_process
{
    typedef DisplayProcessImpl* (*FuncCreateImpl)();
    typedef void (*FuncDeleteImpl)(DisplayProcessImpl*);
    //=====================================================

    DisplayProcess::DisplayProcess()
    {
    }

    DisplayProcess::~DisplayProcess()
    {
        Release();
    }

    bool DisplayProcess::Init(infer_process::INFER_TYPE type)
    {
        Release();

        std::lock_guard<std::mutex> lock(g_display_mutex);

        const char* library_name = GetLibraryName(type);
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
            
            FuncCreateImpl func = (FuncCreateImpl)(m_lib->resolve("CreateDisplayImpl"));
            if (func)
            {
                m_impl = func();
                if (m_impl)
                {
                    if (m_impl->Init())
                    {
                        m_is_valid = true;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void DisplayProcess::Release()
    {
        std::lock_guard<std::mutex> lock(g_display_mutex);
        
        if (m_lib)
        {
            FuncDeleteImpl func = (FuncDeleteImpl)(m_lib->resolve("DeleteDisplayImpl"));
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

    bool DisplayProcess::IsValid() const
    {
        return m_is_valid;
    }

    DISPLAY_STATUS DisplayProcess::Process(const cv::Mat& image, const infer_process::st_infer_result& result)
    {
        std::lock_guard<std::mutex> lock(g_display_mutex);
        if (m_is_valid && m_impl)
        {
            return m_impl->Process(image, result);
        }
        return DISPLAY_STATUS_FAILED;
    }

    cv::Mat DisplayProcess::GetDisplayImage() const
    {
        std::lock_guard<std::mutex> lock(g_display_mutex);
        if (m_impl)
        {
            return m_impl->GetDisplayImage();
        }
        return cv::Mat();
    }

    void DisplayProcess::SetDisplayParams(const st_display_params& params)
    {
        std::lock_guard<std::mutex> lock(g_display_mutex);
        if (m_impl)
        {
            m_impl->SetDisplayParams(params);
        }
    }

    const char* DisplayProcess::GetLibraryName(infer_process::INFER_TYPE type) const
    {
        for (int i = 0; i < DISPLAY_TYPE_COUNT; ++i)
        {
            if (DISPLAY_TYPE_INFO[i].type == type)
            {
                return DISPLAY_TYPE_INFO[i].library_name;
            }
        }
        return nullptr;
    }

} // namespace display_process 