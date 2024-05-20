#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef LIBMAP_EXPORTS
#define LIBMAP_API __declspec(dllexport)
#else
#define LIBMAP_API __declspec(dllimport)
#endif

extern "C" LIBMAP_API void map_func(const char* fileName, const char* data, const char* temp, int numReducers);
