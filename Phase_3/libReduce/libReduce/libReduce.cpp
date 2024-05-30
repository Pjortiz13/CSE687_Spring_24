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

// Reduce function that consolidates intermediate key-value pairs from mapper outputs
LIBREDUCE_API void reduce(const char* inputFile, const char* outputDir) {
    // Convert input and output directory paths to string
    std::string inputFileString(inputFile);
    std::string outputDirString(outputDir);

    // Map to store the consolidated word counts
    std::map<std::string, int> wordCounts;
    // Log the start of the reduction process
    std::cout << "[DEBUG] Starting reduction process..." << std::endl;
    // Log the input and output directories
    std::cout << "[DEBUG] Input file: " << inputFileString << std::endl;
    std::cout << "[DEBUG] Output directory: " << outputDirString << std::endl;

    // Open the input file for reading
    std::ifstream inFile(inputFileString);
    if (!inFile.is_open()) {
        // Log an error if the file cannot be opened
        std::cerr << "[ERROR] Failed to open file: " << inputFileString << std::endl;
        return;
    }

    std::string line;
    // Read each line from the file
    while (getline(inFile, line)) {
        // Create a string stream from the line
        std::istringstream iss(line);
        std::string word;
        int count;
        // Log the line being processed
        std::cout << "[DEBUG] Processing line: " << line << std::endl;
        // Parse the word and count from the line
        if (!(iss >> word >> count)) {
            // Log an error if parsing fails
            std::cerr << "[ERROR] Failed to parse line: " << line << std::endl;
            continue;
        }
        // Update the word count in the map
        wordCounts[word] += count;
        // Log the processed word and its count
        std::cout << "[DEBUG] Processed word: " << word << ", count: " << count << std::endl;
    }
    // Close the input file
    inFile.close();

    // Sort the word counts
    std::vector<std::pair<std::string, int>> sortedWordCounts(wordCounts.begin(), wordCounts.end());
    std::sort(sortedWordCounts.begin(), sortedWordCounts.end());

    // Open the output file for writing the final results
    std::ofstream outFile(outputDirString + "/results.txt", std::ios_base::app); // Append to results.txt
    if (!outFile.is_open()) {
        // Log an error if the output file cannot be opened
        std::cerr << "[ERROR] Failed to open output file." << std::endl;
        return;
    }

    // Log the start of writing results to the output file
    std::cout << "[DEBUG] Writing results to output file..." << std::endl;
    // Write the sorted word counts to the output file
    for (const auto& pair : sortedWordCounts) {
        outFile << pair.first << " " << pair.second << std::endl;
        // Log the word and count being written
        std::cout << "[DEBUG] Wrote word: " << pair.first << ", count: " << pair.second << std::endl;
    }

    // Close the output file
    outFile.close();
    // Log the completion of the reduction process
    std::cout << "[DEBUG] Reduction process completed." << std::endl;
}
