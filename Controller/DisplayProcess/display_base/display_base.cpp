#include "display_base.h"
#include "display_base_impl.h"
#include <mutex>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

static std::mutex g_display_mutex;

namespace display_process
{
    typedef DisplayBaseImpl* (*FuncCreateImpl)();
    typedef void (*FuncDeleteImpl)(DisplayBaseImpl*);
    //=====================================================

    DisplayBase::DisplayBase()
    {
    }

    DisplayBase::~DisplayBase()
    {
        Release();
    }

    bool DisplayBase::Init(infer_process::INFER_TYPE type)
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

    void DisplayBase::Release()
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

    bool DisplayBase::IsValid() const
    {
        return m_is_valid;
    }

    DISPLAY_STATUS DisplayBase::Process(const cv::Mat& image, const infer_process::st_infer_result& result)
    {
        std::lock_guard<std::mutex> lock(g_display_mutex);
        if (m_is_valid && m_impl)
        {
            return m_impl->Process(image, result);
        }
        return DISPLAY_STATUS_FAILED;
    }

    cv::Mat DisplayBase::GetDisplayImage() const
    {
        std::lock_guard<std::mutex> lock(g_display_mutex);
        if (m_impl)
        {
            return m_impl->GetDisplayImage();
        }
        return cv::Mat();
    }

    void DisplayBase::SetDisplayParams(const st_display_params& params)
    {
        std::lock_guard<std::mutex> lock(g_display_mutex);
        if (m_impl)
        {
            m_impl->SetDisplayParams(params);
        }
    }

    const char* DisplayBase::GetLibraryName(infer_process::INFER_TYPE type) const
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