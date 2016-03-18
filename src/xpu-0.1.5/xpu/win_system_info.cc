/**
* @file		win_system_info.cpp
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

#ifdef _MSC_VER

#include <windows.h>
#include <malloc.h>
#include <stdio.h>
#include <tchar.h>
#include <xpu/win_system_info.h>

static BOOL executed = FALSE;
static DWORD processorCoreCount = 0;
static DWORD l1_data_cache_line_size = 0;
static DWORD l1_data_cache_size = 0;
static DWORD l1_inst_cache_line_size = 0;
static DWORD l1_inst_cache_size = 0;

typedef BOOL(WINAPI *LPFN_GLPI)(
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
    PDWORD);

int ReadProcInfo()
{
    if (executed)
    {
        return 0;
    }

    LPFN_GLPI glpi;
    BOOL done = FALSE;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = NULL;
    DWORD returnLength = 0;
    DWORD byteOffset = 0;
    PCACHE_DESCRIPTOR Cache;

    glpi = (LPFN_GLPI)GetProcAddress(
        GetModuleHandle(TEXT("kernel32")),
        "GetLogicalProcessorInformation");
    if (NULL == glpi)
    {
        _tprintf(TEXT("\nGetLogicalProcessorInformation is not supported.\n"));
        return (1);
    }

    // Get enough large buffer for GetLogicalProcessorInformation
    while (!done)
    {
        DWORD rc = glpi(buffer, &returnLength);

        if (FALSE == rc)
        {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
                if (buffer)
                    free(buffer);

                buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(
                    returnLength);

                if (NULL == buffer)
                {
                    _tprintf(TEXT("\nError: Allocation failure\n"));
                    return (2);
                }
            }
            else
            {
                _tprintf(TEXT("\nError %d\n"), GetLastError());
                return (3);
            }
        }
        else
        {
            done = TRUE;
        }
    }

    ptr = buffer;

    while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength)
    {
        switch (ptr->Relationship)
        {
        case RelationNumaNode:
            break;

        case RelationProcessorCore:
            processorCoreCount++;
            break;

        case RelationCache:
            // Cache data is in ptr->Cache, one CACHE_DESCRIPTOR structure for each cache. 
            Cache = &ptr->Cache;
            if (Cache->Level == 1)
            {
                switch (Cache->Type)
                {
                case CacheData:
                    l1_data_cache_line_size = Cache->LineSize;
                    l1_data_cache_size = Cache->Size;
                    break;
                case CacheInstruction:
                    l1_inst_cache_line_size = Cache->LineSize;
                    l1_inst_cache_size = Cache->Size;
                    break;
                default:
                    _tprintf("\nError: Unsupported Cache Type: %d .\n", Cache->Type);
                    break;
                }
            }
            break;

        case RelationProcessorPackage:
            break;

        default:
            _tprintf(TEXT("\nError: Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.\n"));
            break;
        }
        byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
        ptr++;
    }
    free(buffer);

    executed = TRUE;
    return 0;
}

DWORD get_logical_processor_count_win()
{
    ReadProcInfo();
    return processorCoreCount;
}

DWORD get_l1_data_cache_line_size_win()
{
    ReadProcInfo();
    return l1_data_cache_line_size;
}

DWORD get_l1_data_cache_size_win()
{
    ReadProcInfo();
    return l1_data_cache_size;
}

DWORD get_l1_inst_cache_line_size_win()
{
    ReadProcInfo();
    return l1_inst_cache_line_size;
}

DWORD get_l1_inst_cache_size_win()
{
    ReadProcInfo();
    return l1_inst_cache_size;
}
#endif // _MSC_VER