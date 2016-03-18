/**
* @file		win_time.cpp
* @author	Xiang Fu - gtaifu@gmail.com
* @date		27-02-2016
* @brief	Implementation of windows version clock_gettime(CLOCK_REALTIME, timespec* t)
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
#include <xpu/win_time.h>

int clock_get_time(timespec *t)
{
    static LARGE_INTEGER frequency;
    if (frequency.QuadPart == 0)
        ::QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER now;
    ::QueryPerformanceCounter(&now);

    double absolute = now.QuadPart / double(frequency.QuadPart);
    t->tv_sec = int(absolute);
    t->tv_nsec = int(absolute*1e9)%1000000000;

    return 0;
}

#endif //_MSC_VER