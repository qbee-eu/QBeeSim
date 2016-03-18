/**
* @file		win_system_info.h
* @author	Xiang Fu - gtaifu@gmail.com
* @date		27-02-2016
* @brief	Functions to get the processor information in Windows OS.
*
* @copyright
*
* Copyright (C) 2016 Xiang Fu, All Rights Reserved.
*
*
* @brief
*
*/

#ifndef __WINSYSTEMINFO__
#define __WINSYSTEMINFO__

#ifdef _MSC_VER

#include <Windows.h>

DWORD get_logical_processor_count_win();
DWORD get_l1_data_cache_line_size_win();
DWORD get_l1_data_cache_size_win();
DWORD get_l1_inst_cache_line_size_win();
DWORD get_l1_inst_cache_size_win();

#endif // _MSC_VER


#endif // !__WINSYSTEMINFO__
