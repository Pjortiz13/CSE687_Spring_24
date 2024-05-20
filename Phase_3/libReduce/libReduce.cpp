#include "libReduce.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <filesystem>
#include <vector>
#include <algorithm>

LIBREDUCE_API void reduce(const char* inputDir, const char* outputDir) {
    std::string inputDirString(inputDir);
    std::string outputDirString(outputDir);

    std::map<std::string, int> wordCounts;
    std::cout << "[DEBUG] Starting reduction process..." << std::endl;
    std::cout << "[DEBUG] Input directory: " << inputDirString << std::endl;
    std::cout << "[DEBUG] Output directory: " << outputDirString << std::endl;

    for (const auto& entry : std::filesystem::directory_iterator(inputDirString)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::ifstream inFile(entry.path());
            if (!inFile.is_open()) {
                std::cerr << "[ERROR] Failed to open file: " << entry.path().string() << std::endl;
                continue;
            }
            std::cout << "[DEBUG] Processing file: " << entry.path().string() << std::endl;

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
        }
    }

    // Sort the word counts
    std::vector<std::pair<std::string, int>> sortedWordCounts(wordCounts.begin(), wordCounts.end());
    std::sort(sortedWordCounts.begin(), sortedWordCounts.end());

    std::ofstream outFile(outputDirString + "/results.txt");
    if (!outFile.is_open()) {
        std::cerr << "[ERROR] Failed to open output file." << std::endl;
        return;
    }

    std::cout << "[DEBUG] Writing results to output file..." << std::endl;
    for (const auto& pair : sortedWordCounts) {
        outFile << pair.first << " " << pair.second << std::endl;
        std::cout << "[DEBUG] Wrote word: " << pair.first << ", count: " << pair.second << std::endl;
    }

    outFile.close();
    std::cout << "[DEBUG] Reduction process completed." << std::endl;
}
