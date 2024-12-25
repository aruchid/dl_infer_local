#pragma once
#include "../tk_utility/tk_data_type.h"
#include <string>
# if defined(TK_TXR_ALGO_DLM_LIB)
#  define TK_TXR_ALGO_DLM_EXPORT Q_DECL_EXPORT
# else
#  define TK_TXR_ALGO_DLM_EXPORT Q_DECL_IMPORT
# endif

namespace txr_algo_dlm
{
	enum DLM_TYPE
	{
		DLM_TYPE_UNKNOWN,
		DLM_TYPE_YOLOV4_TINY,
		DLM_TYPE_YOLOV4_TINY_TRT,
		DLM_TYPE_YOLOV6_TRT,
		DLM_TYPE_OPENVINO_NANODET,
		DLM_TYPE_YOLOV6SP5_TRT,
		// 2024-12-22 新增
		DLM_TYPE_YOLOV6S_OPENVINO,
	};

	static const tk_int32 MAX_PATH_BYTES = 260;
	struct st_dlm_cfg
	{
		DLM_TYPE	type = DLM_TYPE_UNKNOWN;
		tk_int32	gpu_id = 0;
		tk_char 	file_path_name[MAX_PATH_BYTES];
	};

	static const tk_int32 IMG_CHANNELS = 3;
	//==============================================================
	struct st_img_rgb 
	{
		// pointer to the image data   n * r + n*g + n*b		
		//�ڴ��ַ
		tk_float * pp_rgbf[IMG_CHANNELS] = {0};
		tk_uint8 *	pp_rgb8[IMG_CHANNELS] = {0};
		tk_uint16 * pp_rgb16[IMG_CHANNELS] = {0};
		//�Դ��ַ
		tk_float * pp_dev_rgbf[IMG_CHANNELS] = { 0 };
		tk_uint8 *	pp_dev_rgb8[IMG_CHANNELS] = { 0 };
		tk_uint16 * pp_dev_rgb16[IMG_CHANNELS] = { 0 };

		tk_int32 h = 0;									// height
		tk_int32 w = 0;									// width
		tk_int32 c = IMG_CHANNELS;						// number of chanels (3 - for RGB)
	};

	//===============================================================
	struct st_box {
		tk_int32 x = 0, y = 0, w = 0, h = 0;	// (x,y) - top-left corner, (w, h) - width & height of bounded box
		tk_float prob = 0;						// confidence - probability that the object was found correctly
		tk_int32 obj_id = 0;					// class of object - from range [0, classes-1]
	};
	static const tk_uint32 BOX_MAX_NUM = 1000;

	struct st_result_boxes
	{
		st_box		boxes[BOX_MAX_NUM];
		tk_int32	vaild_num = 0;
	};
	//===============================================================
	struct st_detect_param 
	{
		tk_float	prob_thres = 0.1f; 
		tk_float	nms_thres = 0.5f;
	};

	struct st_detect_unit
	{
		st_img_rgb		img;
		st_detect_param param;
		st_result_boxes   result;
	};
	


}//namespace txr_algo_dlm