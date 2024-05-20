#include "libMap.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>
#include <unordered_map>

LIBMAP_API void map_func(const char* fileName, const char* data, const char* temp, int numReducers) {
    std::cout << "[DEBUG] Entering map_func for file: " << fileName << std::endl;
    std::istringstream iss(data);
    std::string word;
    std::unordered_map<int, std::unordered_map<std::string, int>> reducerBuckets;

    while (iss >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());

        std::cout << "[DEBUG] Processing word: " << word << std::endl;

        int bucketIndex = std::hash<std::string>{}(word) % numReducers;
        ++reducerBuckets[bucketIndex][word];

        std::cout << "[DEBUG] Word " << word << " goes to bucket " << bucketIndex << std::endl;
    }

    for (int i = 0; i < numReducers; ++i) {
        std::ofstream outFile(std::string(temp) + "/mapper_output_" + std::to_string(i) + ".txt", std::ios::app);
        if (!outFile.is_open()) {
            std::cerr << "[ERROR] Failed to open mapper output file for bucket " << i << std::endl;
            continue;
        }
        for (const auto& pair : reducerBuckets[i]) {
            outFile << pair.first << " " << pair.second << std::endl;
            std::cout << "[DEBUG] Writing word: " << pair.first << ", count: " << pair.second << " to bucket " << i << std::endl;
        }
        outFile.close();
    }
    std::cout << "[DEBUG] Exiting map_func for file: " << fileName << std::endl;
}
