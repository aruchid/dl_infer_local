#pragma once

#include "txr_algo_dlm_define.h"

namespace txr_algo_dlm
{
	class TxrAlgoDlmImpl
	{
	public:
		TxrAlgoDlmImpl() {}
		virtual ~TxrAlgoDlmImpl() {}

		virtual tk_bool Load(st_dlm_cfg& cfg) = 0;
		virtual tk_int32 BatchSize() = 0;
		virtual void Detect(st_detect_unit* p_unit, tk_int32 size) = 0;
	};

}//namespace txr_algo_dlm
