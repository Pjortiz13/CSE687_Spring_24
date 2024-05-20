#include "libMap.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

void map_func(const char* inputFilePath, const char* fileContents, const char* tempDir, int numReducers) {
    std::unordered_map<std::string, int> wordCount;
    std::istringstream iss(fileContents);
    std::string word;

    while (iss >> word) {
        ++wordCount[word];
    }

    int reducerIndex = 0;
    for (const auto& entry : wordCount) {
        std::ofstream outFile(std::string(tempDir) + "/mapper_output_" + std::to_string(reducerIndex) + ".txt", std::ios::app);
        outFile << entry.first << " " << entry.second << "\n";
        reducerIndex = (reducerIndex + 1) % numReducers;
    }
}
