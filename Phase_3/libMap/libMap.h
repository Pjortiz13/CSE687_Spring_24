#pragma once

#ifdef LIBMAP_EXPORTS
#define LIBMAP_API __declspec(dllexport)
#else
#define LIBMAP_API __declspec(dllimport)
#endif

extern "C" LIBMAP_API void map_func(const char* inputFilePath, const char* fileContents, const char* tempDir, int numReducers);
