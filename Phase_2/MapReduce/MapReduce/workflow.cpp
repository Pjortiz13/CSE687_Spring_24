/*
workflow.cpp
Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase II 
05/08/2024

Summary: workflow.cpp  servers as the driver file and contains the workflow class implementation  that manages the 
execution of the MapReduce workflow.It links the map and reduce Dlls, establish function pointers, 
iterates through input files, and ensures proper execution and file handling. 

*/ 

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iterator>
#include <libMap.h>
#include <libReduce.h>
#include <windows.h>
#include "fileManagement.h"

typedef void (*funcReduce)(const char*);
typedef void (*funcMap)(const char*, const char*, const char*);

// executes the MapReduce workflow
bool execute(funcMap Map, funcReduce Reduce, std::string inputDir, 
    std::string tempDir, std::string outputDir) {
    std::cout << "\n...Please Stand By..." << std::endl;
    // count of processed files
    int countFiles = 0;

    std::cout << "Mapping process started..." << std::endl;
    // iterate over each file in the input directory
    for (const auto& entry : std::filesystem::directory_iterator(inputDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::string filepath = entry.path().string();
            countFiles++;
            fileManagement reader;

            if (!reader.openFile(filepath, std::ios::in)) {
                std::cerr << "Failed to open file: " << filepath << std::endl;
                continue;
            }

            std::string line;
            while (reader.readNextBlock(line)) {
                Map(entry.path().filename().string().c_str(), line.c_str(), tempDir.c_str());
            }
            reader.closeFile();
        }
    }
 
    if (countFiles == 0) {
        std::cerr << "Error: No text files found in the input directory." << std::endl;
        std::cout << "Mapping process could not be completed." << std::endl;
        return false;
    }
    else {
        std::cout << "Mapping process completed." << std::endl;
    }

    std::cout << "Reducing process started..." << std::endl;
    Reduce(outputDir.c_str());
    
    if (!fileManagement::CreateEmptyFileInDir(outputDir, "SUCCESS")) {
        std::cerr << "Failed to create SUCCESS file." << std::endl;
    }
    else {
        std::cout << "Reducing process completed." << std::endl;
    }
    return true;
}
}
// main function checks command line arguments and runs the workflow
int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <inputDir> <outputDir> <tempDir>" << std::endl;
        return 1;
    }

    std::string inputDir = argv[1];
    std::string outputDir = argv[2];
    std::string tempDir = argv[3];

    HINSTANCE hDLL_reduce;
    HINSTANCE hDLL_map;

    funcReduce Reduce;
    funcMap Map;

    const wchar_t* reduceLibName = L"libReduce.dll";
    const wchar_t* mapLibName = L"libMap.dll";

    // Handle to DLLs
    hDLL_reduce = LoadLibraryEx(reduceLibName, NULL, NULL);
    if (hDLL_reduce == NULL) {
        std::cout << "Reduce library load failed." << std::endl;
        return 1;
    }

    hDLL_map = LoadLibraryEx(mapLibName, NULL, NULL);
    if (hDLL_map == NULL) {
        std::cout << "Map library load failed!" << std::endl;
        FreeLibrary(hDLL_reduce);
        return 1;
    }

    Reduce = (funcReduce)GetProcAddress(hDLL_reduce, "reduce");
    if (Reduce == NULL) {
        std::cout << "Failed to find reduce() function!" << std::endl;
        FreeLibrary(hDLL_reduce);
        FreeLibrary(hDLL_map);
        return 1;
    }

    Map = (funcMap)GetProcAddress(hDLL_map, "map_func");
    if (Map == NULL) {
        std::cout << "Failed to find map() function!" << std::endl;
        FreeLibrary(hDLL_reduce);
        FreeLibrary(hDLL_map);
        return 1;
    }

    bool res = execute(Map, Reduce, inputDir, tempDir, outputDir);
    if (!res) {
        std::cerr << "Failed to execute the workflow!" << std::endl;
    }
    else {
        std::cout << "Workflow completed!" << std::endl;
    }

    std::cin.get();
    FreeLibrary(hDLL_reduce);
    FreeLibrary(hDLL_map);
    return 0;
}
