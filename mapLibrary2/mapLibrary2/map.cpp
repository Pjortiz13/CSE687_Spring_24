#include "map.h" 
#include <algorithm> 
#include <fstream> 
#include <iostream> 
#include <sstream> 
#include <cctype> 
#include <vector>
#include <string>
#include <tuple>

// MapFunction processes the text data, tokenizes it, converts to lowercase, removes punctuation, and exports counts
void MapClass::MapFunction(const std::string& fileName, const std::string& data, const std::string& tempDir) {
    std::istringstream iss(data);
    std::string word;

    while (iss >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
        ExportFunction(word, 1, tempDir);
    }
}

// ExportFunction writes the word and its count to a temporary file
void MapClass::ExportFunction(const std::string& word, int count, const std::string& tempDir) {
    std::ofstream out(tempDir + "/map_output.txt", std::ios::app);
    std::tuple<std::string, int>wordsTuple(word, count);
    static std::vector<std::tuple<std::string, int>> buffer;
    const size_t bufferSize = 10;

    buffer.push_back(wordsTuple);

    if (buffer.size() >= bufferSize) {
        if (out.is_open()) {

            for (const auto& tuple : buffer) {
                std::string outputString = "(\"" + std::get<0>(tuple) + "\", " + std::to_string(std::get<1>(tuple)) + ") ";
                out << outputString << std::endl;
            }
        }
        out.close();
        buffer.clear();
    }
}

// wrapper functions to export in DLL
void map(const char* filename, const char* data, const char* tempDir) {
    MapClass::MapFunction(filename, data, tempDir);
}

void export_res(const char* word, int count, const char* tempDir) {
    MapClass::ExportFunction(word, count, tempDir);
}
