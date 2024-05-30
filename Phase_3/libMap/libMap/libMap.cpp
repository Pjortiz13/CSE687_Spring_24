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

// Map function that processes a given data file and outputs intermediate key-value pairs
LIBMAP_API void map_func(const char* fileName, const char* data, const char* temp, int numReducers) {
    try {
        // Log entry into the map function
        std::cout << "[DEBUG] Entering map_func for file: " << fileName << std::endl;

        if (numReducers <= 0) {
            throw std::invalid_argument("Number of reducers must be greater than zero.");
        }

        // Input string stream to read data line by line
        std::istringstream iss(data);
        std::string word;
        // Hash map to store words and their counts divided by reducer buckets
        std::unordered_map<int, std::unordered_map<std::string, int>> reducerBuckets;

        // Process each word in the input data
        while (iss >> word) {
            // Remove invalid characters and convert valid characters to lowercase
            word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) {
                return !std::isalpha(static_cast<unsigned char>(c)) && !std::isspace(static_cast<unsigned char>(c));
                }), word.end());

            std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) {
                return std::tolower(static_cast<unsigned char>(c));
                });

            // Skip empty words after processing
            if (word.empty()) {
                continue;
            }

            // Log the processed word
            std::cout << "[DEBUG] Processing word: " << word << std::endl;

            // Determine the reducer bucket for the word using a hash function
            int bucketIndex = std::hash<std::string>{}(word) % numReducers;
            // Increment the word count in the appropriate bucket
            ++reducerBuckets[bucketIndex][word];

            // Log the bucket assignment
            std::cout << "[DEBUG] Word " << word << " goes to bucket " << bucketIndex << std::endl;
        }

        // Write each bucket's contents to its corresponding output file
        for (int i = 0; i < numReducers; ++i) {
            // Open output file for the current bucket
            std::ofstream outFile(std::string(temp) + "/mapper_output_" + std::to_string(i) + ".txt", std::ios::app);
            if (!outFile.is_open()) {
                // Log an error if the file cannot be opened
                std::cerr << "[ERROR] Failed to open mapper output file for bucket " << i << std::endl;
                continue;
            }
            // Write word counts to the output file
            for (const auto& pair : reducerBuckets[i]) {
                // Log the word and count being written
                outFile << pair.first << " " << pair.second << std::endl;
                std::cout << "[DEBUG] Writing word: " << pair.first << ", count: " << pair.second << " to bucket " << i << std::endl;
            }
            // Close the output file
            outFile.close();
        }
        // Log exit from the map function
        std::cout << "[DEBUG] Exiting map_func for file: " << fileName << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception in map_func: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "[ERROR] Unknown exception in map_func." << std::endl;
    }
}
