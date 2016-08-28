#pragma once

#ifndef __linux__
#ifndef WIN32
#if defined(_WIN32) || defined(_WIN64)
#define __WINDOWS_
#ifdef _WIN32
#define WIN32
#else
#define WIN64
#endif
#endif
#endif

#if USE_WMI && !_MSC_VER
#undef USE_WMI
#endif

/* fixes ambiguity issues with max() macro and numeric_limits<T>::max() when using MSVC */
#ifdef _MSC_VER
#define NOMINMAX
#endif

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#endif
