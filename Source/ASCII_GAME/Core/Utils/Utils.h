#ifndef _UTILS_H_
#define _UTILS_H_

#include <Windows.h>
#include <iostream>
#include <cstdarg>
#include <debugapi.h>

#define SAFE_DELETE_PTR(ptr){ if(ptr){ delete ptr; ptr = nullptr; } }
#define SAFE_DELETE_ARY(ptr){ if(ptr){ delete[] ptr; ptr = nullptr; } }

namespace debug
{
    static void log(const char* szFormat, ...)
    {
        char szBuff[1024];
        va_list arg;
        va_start(arg, szFormat);
        _vsnprintf_s(szBuff, sizeof(szBuff), szFormat, arg);
        va_end(arg);

        OutputDebugString(szBuff);
    }
}

#endif
