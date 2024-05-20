#include "libReduce.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

void reduce_func(const std::vector<std::string>& inputFiles, const char* outputFile) {
    std::unordered_map<std::string, int> wordCount;

    for (const auto& file : inputFiles) {
        std::ifstream inFile(file);
        std::string word;
        int count;
        while (inFile >> word >> count) {
            wordCount[word] += count;
        }
    }

    std::ofstream outFile(outputFile);
    for (const auto& entry : wordCount) {
        outFile << entry.first << " " << entry.second << "\n";
    }
}
