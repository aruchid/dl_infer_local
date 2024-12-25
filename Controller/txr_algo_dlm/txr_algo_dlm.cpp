#include "txr_algo_dlm.h"
#include "../tk_utility/tk_mutex.h"
#include "txr_algo_dlm_impl.h"

#include <boost/filesystem.hpp>
#include <QSysInfo>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

using namespace tk;

static TkMutex g_dlm_mutex;

namespace txr_algo_dlm
{
	typedef TxrAlgoDlmImpl* (*FuncCreateDlmObj)();
	typedef void (*FuncDeleteDlmObj)(TxrAlgoDlmImpl*);
	//=====================================================

	//=====================================================
	TxrAlgoDlm::TxrAlgoDlm()
	{

	}

	TxrAlgoDlm::~TxrAlgoDlm()
	{
		Release();
	}

	tk_bool TxrAlgoDlm::Load(st_dlm_cfg & cfg)
	{
		Release();

		TkMutexLocker lock(g_dlm_mutex);

		QString app_path = QCoreApplication::applicationDirPath();
		switch (GetDlmType(cfg))
		{
		case DLM_TYPE_YOLOV4_TINY:
			m_lib_dlm = new QLibrary(QDir::toNativeSeparators(app_path + "/txr_algo_dlm_v1"));
			break;

		case DLM_TYPE_YOLOV4_TINY_TRT:
			m_lib_dlm = new QLibrary(QDir::toNativeSeparators(app_path + "/txr_algo_dlm_v2"));
			break;
		case DLM_TYPE_YOLOV6_TRT:
			m_lib_dlm = new QLibrary(QDir::toNativeSeparators(app_path + "/txr_algo_dlm_v3"));
			break;
		case DLM_TYPE_OPENVINO_NANODET:
			if (QSysInfo::WindowsVersion == QSysInfo::WV_WINDOWS10)
			{
				m_lib_dlm = new QLibrary(QDir::toNativeSeparators(app_path + "/txr_algo_dlm_v4"));
			}
			else
			{
				qWarning() << "txr_algo_dlm_v4 can not load : only support win10 ";
			}
			break;
		case DLM_TYPE_YOLOV6SP5_TRT:
			m_lib_dlm = new QLibrary(QDir::toNativeSeparators(app_path + "/txr_algo_dlm_v5"));
			break;
		case DLM_TYPE_YOLOV6S_OPENVINO:
			m_lib_dlm = new QLibrary(QDir::toNativeSeparators(app_path + "/txr_algo_dlm_v5_o"));
			break;
		default:
			return TK_FALSE;
		}

		if (m_lib_dlm)
		{
			if (!m_lib_dlm->load())
			{
				qWarning() << "Library load fail: " << m_lib_dlm->errorString();
				return TK_FALSE;
			}
			FuncCreateDlmObj func = (FuncCreateDlmObj)(m_lib_dlm->resolve("CreateDlmObj"));
			if (func)
			{
				m_dlm_obj = func();
				if (m_dlm_obj)
				{
					if (m_dlm_obj->Load(cfg))
					{
						m_dlm_vaild = TK_TRUE;
						return TK_TRUE;
					}
				}
			}
		}
		return TK_FALSE;
	}

	void TxrAlgoDlm::Release()
	{
		TkMutexLocker lock(g_dlm_mutex);
		
		if (m_lib_dlm)
		{
			FuncDeleteDlmObj func = (FuncDeleteDlmObj)(m_lib_dlm->resolve("DeleteDlmObj"));
			if (func)
			{
				func(m_dlm_obj);
				m_dlm_obj = TK_NULL_PTR;
			}
			m_lib_dlm->unload();
			m_lib_dlm = TK_NULL_PTR;
		}
		m_dlm_vaild = TK_FALSE;
	}

	void TxrAlgoDlm::Detect(st_detect_unit * p_unit, tk_int32 size)
	{
		TkMutexLocker lock(g_dlm_mutex);
		if (m_dlm_vaild)
		{
			m_dlm_obj->Detect(p_unit, size);
		}
	}
	tk_bool TxrAlgoDlm::IsVaild()
	{
		return m_dlm_vaild == TK_TRUE;
	}

	tk_int32 TxrAlgoDlm::BatchSize()
	{
		TkMutexLocker lock(g_dlm_mutex);
		if (m_dlm_obj)
		{
			return m_dlm_obj->BatchSize();
		}
		return 0;
	}
	//=============================================================================

	DLM_TYPE TxrAlgoDlm::GetDlmType(st_dlm_cfg & cfg)
	{
		if (cfg.type != DLM_TYPE_UNKNOWN)
		{
			return cfg.type;
		}
		using namespace boost::filesystem;
		{
			path path_cfg(std::string(cfg.file_path_name) + ".dat");
			path path_weight(std::string(cfg.file_path_name) + ".dats");
			if (exists(path_cfg) && exists(path_weight))
			{
				return DLM_TYPE_YOLOV4_TINY;
			}
		}
		{
			path path_weight(std::string(cfg.file_path_name) + ".fdats");
			if (exists(path_weight))
			{
				return DLM_TYPE_YOLOV4_TINY_TRT;
			}
		}
		{
			path path_weight(std::string(cfg.file_path_name) + ".gdats");
			if (exists(path_weight))
			{
				return DLM_TYPE_YOLOV6_TRT;
			}
		}
		{
			path path_json(std::string(cfg.file_path_name) + ".json");
			path path_xml(std::string(cfg.file_path_name) + ".xml");
			path path_bin(std::string(cfg.file_path_name) + ".bin");
			if (exists(path_json) && exists(path_xml) && exists(path_bin))
			{
				return DLM_TYPE_OPENVINO_NANODET;
			}
		}
		{
			path path_weight(std::string(cfg.file_path_name) + ".hdats");
			if (exists(path_weight))
			{
				return DLM_TYPE_YOLOV6SP5_TRT;
			}
		}
		{
			path path_weight(std::string(cfg.file_path_name) + ".ohdats");
			if (exists(path_weight))
			{
				return DLM_TYPE_YOLOV6S_OPENVINO;
			}
		}
		return DLM_TYPE_UNKNOWN;
	}

}//namespace txr_algo_dlm