// libReduce.cpp
#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

#include "libReduce.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <filesystem>
#include <vector>
#include <algorithm>

// Ensure proper function export
extern "C" LIBREDUCE_API void __cdecl reduce(const char* inputFile, const char* outputDir) {
    std::string inputFileString(inputFile);
    std::string outputDirString(outputDir);

    std::map<std::string, int> wordCounts;
    std::cout << "[DEBUG] Starting reduction process..." << std::endl;
    std::cout << "[DEBUG] Input file: " << inputFileString << std::endl;
    std::cout << "[DEBUG] Output directory: " << outputDirString << std::endl;

    std::ifstream inFile(inputFileString);
    if (!inFile.is_open()) {
        std::cerr << "[ERROR] Failed to open file: " << inputFileString << std::endl;
        return;
    }

    std::string line;
    while (getline(inFile, line)) {
        std::istringstream iss(line);
        std::string word;
        int count;
        std::cout << "[DEBUG] Processing line: " << line << std::endl;
        if (!(iss >> word >> count)) {
            std::cerr << "[ERROR] Failed to parse line: " << line << std::endl;
            continue;
        }
        wordCounts[word] += count;
        std::cout << "[DEBUG] Processed word: " << word << ", count: " << count << std::endl;
    }
    inFile.close();

    std::vector<std::pair<std::string, int>> sortedWordCounts(wordCounts.begin(), wordCounts.end());
    std::sort(sortedWordCounts.begin(), sortedWordCounts.end());

    std::string outputFilePath = outputDirString + "/results.txt";
    std::ofstream outFile(outputFilePath, std::ios_base::app);
    if (!outFile.is_open()) {
        std::cerr << "[ERROR] Failed to open output file at " << outputFilePath << std::endl;
        return;
    }

    std::cout << "[DEBUG] Writing results to output file: " << outputFilePath << std::endl;
    for (const auto& pair : sortedWordCounts) {
        outFile << pair.first << " " << pair.second << std::endl;
        std::cout << "[DEBUG] Wrote word: " << pair.first << ", count: " << pair.second << std::endl;
    }

    outFile.close();
    std::cout << "[DEBUG] Reduction process completed." << std::endl;
}
