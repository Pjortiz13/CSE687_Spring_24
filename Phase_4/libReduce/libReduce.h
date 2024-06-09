#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef LIBREDUCE_EXPORTS
#define LIBREDUCE_API __declspec(dllexport)
#else
#define LIBREDUCE_API __declspec(dllimport)
#endif

extern "C" LIBREDUCE_API void reduce(const char* inputDir, const char* outputDir);
