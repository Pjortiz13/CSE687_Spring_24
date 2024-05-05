#include "reduce.h"
#include <iostream>
#include <fstream> // used for file stream ops
#include <sstream> // string stream ops
#include <map>     // manages collection of key values

// Main reduce function where mapping results are processed and summarized
void Reduce::reduce(const std::string& outputDir) {
    // Defines the file paths for input and output files
    // and ensures that the folder name is called as shown below and 
    // that the map.cpp generated map_output.txt name follows as well 
    std::string inputFile = outputDir + "/../testtemp/map_output.txt";
    std::string outputFile = outputDir + "/results.txt";
    // Opens the input and output files for reading and writing respectively
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);
    // Checks if the files are properly opened; if not, print error and return
    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Failed to open files." << std::endl;
        return;
    }

    // Creates a map to count occurrences of each word
    std::map<std::string, int> wordCounts;
    std::string line;

    // Reads each line from the input file
    while (getline(inFile, line)) {
        // Uses string stream to parse the line
        std::istringstream iss(line);
        std::string word;
        int count;
        // Read each word and its count, and accumulate counts in the map
        while (iss >> word >> count) {
            // Using emplace to insert or update the count for the word
            wordCounts.emplace(word, count);
        }
    }

    // Writes the accumulated counts to the output file
    for (const auto& pair : wordCounts) {
        outFile << pair.first << " " << pair.second << ")" << std::endl;
    }
    // Closes both the input and output files
    inFile.close();
    outFile.close();
}

void reduce(const char* outputDir) {
    Reduce::reduce(outputDir);
}
