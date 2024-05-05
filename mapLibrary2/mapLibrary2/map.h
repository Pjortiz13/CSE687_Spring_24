#pragma once 
#include <string> 
#include <iostream> 

#ifdef MAPLIBRARY_EXPORTS
#define MAPLIBRARY_API __declspec(dllexport)
#else
#define MAPLIBRARY_API __declspec(dllimport)
#endif

class MapClass {
public:
	//MapFunction processes a single data string from aa specified file, perofmring map operation
	//(string& fileNameInput, string& rawData);
	static void MapFunction(const std::string& fileName, const std::string& data, const std::string& tempDir);
	//outputs the mapped data, word and count, to a temp storage file 
	static void ExportFunction(const std::string& word, int count, const std::string& tempDir);
};

extern "C" MAPLIBRARY_API void map(const char* filename, const char* data, const char* tempDir);
extern "C" MAPLIBRARY_API void export_res(const char* word, int count, const char* tempDir);
