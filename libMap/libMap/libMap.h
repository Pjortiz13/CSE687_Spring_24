#pragma once

#ifdef LIBMAP_EXPORTS
#define LIBMAP_API __declspec(dllexport)
#else
#define LIBMAP_API __declspec(dllimport)
#endif

#include <string>
#include <iostream> 

extern "C" LIBMAP_API void map_func(const char* fileName, const char* data, const char* temp);