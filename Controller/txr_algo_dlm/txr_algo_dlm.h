#pragma once

#include "txr_algo_dlm_define.h"
#include <QLibrary>

namespace txr_algo_dlm
{
	class TxrAlgoDlmImpl;
	//======================================================
	class TK_TXR_ALGO_DLM_EXPORT TxrAlgoDlm
	{
	public:
		TxrAlgoDlm();
		~TxrAlgoDlm();

		tk_bool Load(st_dlm_cfg & cfg);
		void Release();
		tk_bool IsVaild();

		void Detect(st_detect_unit * p_unit,tk_int32 size);
		tk_int32 BatchSize();

	private:
		DLM_TYPE GetDlmType(st_dlm_cfg & cfg);

	private:
		TxrAlgoDlmImpl * m_dlm_obj = TK_NULL_PTR;
		QLibrary * m_lib_dlm = TK_NULL_PTR;
		tk_bool m_dlm_vaild = TK_FALSE;
	};
}//namespace txr_algo_dlm
