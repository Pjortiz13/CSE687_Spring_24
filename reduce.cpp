/*  reduce.cpp

    Group X
    Joseph Laible
    Pedro Ortiz
    Vimal Ramnarain 

    Professor Scott Roueche
    CSE  687 Object Oriented Design in C++
    Syracuse University 

    --- Project Phase 1 ---
    ----- 04/22/2024 -----
    
    This source file essentially takes 
    the intermediate key-value pairs from
    Map phase and outputs a sorted map 
    with keys representing unique words 
    and values representing their counts.
*/

#include "reduce.h"
#include "fileManagement.h"
#include <iostream>
#include <fstream> // used for file stream ops
#include <sstream> // string stream ops
#include <map>     // manages collection of key values

// Constructor that initializes the output directory for storing results
Reduce::Reduce(const std::string& outputDir)
    : outputDir(outputDir) {}

// Start function announces the beginning of the reduction phase
void Reduce::start() {
    std::cout << "Reduction process started." << std::endl;
}

// Main reduce function where mapping results are processed and summarized
void Reduce::reduce() {
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

    // Tries to create a SUCCESS file to indicate completion
    if (!fileManagement::CreateEmptyFileInDir(outputDir, "SUCCESS")) {
        std::cerr << "Failed to create SUCCESS file." << std::endl;
    } else {
        std::cout << "Reduction process completed successfully." << std::endl;
    }
}
// End function announces the completion of the reduction phase
void Reduce::end() {
    std::cout << "Reduction process ended." << std::endl;
}
