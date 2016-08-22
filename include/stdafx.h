#pragma once

#ifndef __linux__
#ifndef WIN32
#ifdef _WIN32
#define WIN32
#endif
#endif

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#endif