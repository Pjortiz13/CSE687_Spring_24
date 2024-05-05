#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iterator>
#include <map.h>
#include <reduce.h>
#include <windows.h>
#pragma once

class fileManagement {
public:
    fileManagement();
    ~fileManagement();

    bool openFile(const std::string& filename, std::ios_base::openmode mode);
    bool readNextBlock(std::string& data);
    void closeFile();

private:
    std::fstream file;
};

fileManagement::fileManagement() {}

fileManagement::~fileManagement() {
    if (file.is_open()) {
        file.close();
    }
}
bool fileManagement::openFile(const std::string& filename, std::ios_base::openmode mode) {
    if (file.is_open()) {
        file.close();
    }
    file.open(filename, mode);
    return file.is_open();
}

bool fileManagement::readNextBlock(std::string& data) {
    return std::getline(file, data) ? true : false;
}

void fileManagement::closeFile() {
    if (file.is_open()) {
        file.close();
    }
}

typedef void (*funcReduce)(const char*); // Reduce::reduce(outputDir_str);
typedef void (*funcMap)(const char*, const char*); // MapClass::MapFunction(filename_str, data_str);
typedef void (*funcExport)(const char*, int, const char*); // MapClass::ExportFunction(word_str, int_count, tempDir_str);

bool execute(funcMap Map, funcExport Export, funcReduce Reduce,
    std::string inputDir, std::string tempDir, std::string outputDir) {
    std::cout << "\n...Please Stand By..." << std::endl;
    int countFiles = 0;

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
                Map(entry.path().filename().string().c_str(), line.c_str());
            }
            reader.closeFile();
        }
    }
    if (countFiles == 0) {
        std::cerr << "Error: No text files found in the input directory." << std::endl;
        return false;
    }

    Reduce(outputDir.c_str());
    return true;
}

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
    funcExport Export;

    const wchar_t* reduceLibName = L"reduceLibrary2";
    const wchar_t* mapLibName = L"mapLibrary2";

    // Handle to DLLs
    hDLL_reduce = LoadLibraryEx(reduceLibName, NULL, NULL);
    if (hDLL_reduce == NULL) {
        std::cout << "Reduce library load failed!" << std::endl;
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
        std::cout << "Failed to find reduce() function." << std::endl;
        FreeLibrary(hDLL_reduce);
        FreeLibrary(hDLL_map);
        return 1;
    }

    Map = (funcMap)GetProcAddress(hDLL_map, "map");
    if (Map == NULL) {
        std::cout << "Failed to find map() function." << std::endl;
        FreeLibrary(hDLL_reduce);
        FreeLibrary(hDLL_map);
        return 1;
    }

    Export = (funcExport)GetProcAddress(hDLL_map, "export");
    if (Export == NULL) {
        std::cout << "Failed to find export() function." << std::endl;
        FreeLibrary(hDLL_reduce);
        FreeLibrary(hDLL_map);
        return 1;
    }

    // TODO: use Reduce(), Map(), and Export() handlers from above. 
    bool res = execute(Map, Export, Reduce, inputDir, tempDir, outputDir);
    if (!res) {
        std::cerr << "Failed to execute the workflow." << std::endl;
    }

    std::cin.get();
    FreeLibrary(hDLL_reduce);
    FreeLibrary(hDLL_map);
    return 0;
}