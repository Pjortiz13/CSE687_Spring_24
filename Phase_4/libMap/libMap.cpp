#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

#include "libMap.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>
#include <unordered_map>
#include <exception>

LIBMAP_API void map_func(const char* fileName, const char* data, const char* temp, int numReducers) {
    try {
        std::cout << "[DEBUG] Entering map_func for file: " << fileName << std::endl;

        if (numReducers <= 0) {
            throw std::invalid_argument("Number of reducers must be greater than zero.");
        }

        std::istringstream iss(data);
        std::string word;
        std::unordered_map<int, std::unordered_map<std::string, int>> reducerBuckets;

        while (iss >> word) {
            word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) {
                return !std::isalpha(static_cast<unsigned char>(c)) && !std::isspace(static_cast<unsigned char>(c));
                }), word.end());

            std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) {
                return std::tolower(static_cast<unsigned char>(c));
                });

            if (word.empty()) {
                continue;
            }

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
    catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception in map_func: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "[ERROR] Unknown exception in map_func." << std::endl;
    }
}
