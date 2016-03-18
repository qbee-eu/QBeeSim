/**
* @file		win_time.h
* @author	Xiang Fu - gtaifu@gmail.com
* @date		27-02-2016
* @brief	windows version clock_gettime(CLOCK_REALTIME, timespec* t)
*
* @copyright
*
* Copyright (C) 2016 Xiang Fu, All Rights Reserved.
*
*
* @brief
*
*/

#ifdef _MSC_VER
// Windows
#include <windows.h>
#include <pthread/include/pthread.h>
int clock_get_time(timespec *t);

#endif //_MSC_VER