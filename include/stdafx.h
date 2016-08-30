#pragma once

#include "settings.h"

#ifndef __linux__

#if defined(_WIN32) || defined(_WIN64)
#define __WINDOWS__
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
