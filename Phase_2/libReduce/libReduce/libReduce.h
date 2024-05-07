#pragma once

#include <string>

#ifdef LIBREDUCE_EXPORTS
#define LIBREDUCE_API __declspec(dllexport)
#else
#define LIBREDUCE_API __declspec(dllimport)
#endif

extern "C" LIBREDUCE_API void reduce(const char* outputDir);
