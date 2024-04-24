/* 
reduce.cpp
Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase I 
04/22/2024
    
    This file for the Reduce class 
    contains functions that take a 
    vector of intermediate key-value 
    pairs from the Map class and then 
    creates an output map with keys 
    representing unique words and 
    values representing their counts
*/

#include "reduce.h"
#include "fileManagement.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>



// Constructor that initializes the output directory for storing results
Reduce::Reduce(const std::string& outputDir)
    : outputDir(outputDir) {}

// start function announces the beginning of the reduction process
void Reduce::start() {
    std::cout << "Reduction process started." << std::endl;
}
// main reduce function where mapping results are processed and summarized
void Reduce::reduce() {
    // defines the file paths for input and output files
    // need to ensure that the folder name is called as shown below and that the map.cpp genereated map_output.txt
    // name follows as well
    std::string inputFile = outputDir + "/../testtemp/map_output.txt"; 
    std::string outputFile = outputDir + "/results.txt";
    // open the input and output files for reading and writing respectively
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);
    // checks if the files are properly opened; if not, print error and return
    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Failed to open files." << std::endl;
        return;
    }

    // unordered map to count occurrences of each word
    std::map<std::string, int> wordCounts;
    std::string line;
    // reads each line from the input file
    while (getline(inFile, line)) {
        // use string stream to parse the line
        std::istringstream iss(line);
        std::string word;
        int count;
        // read each word and its count, and accumulate counts in the map
        while (iss >> word >> count) {
            wordCounts[word] += count;
        }
    }
    // writes the accumulated counts to the output file
    for (const auto& pair : wordCounts) {
        outFile << pair.first << " " << pair.second <<")"<< std::endl;
    }
    // close both the input and output files
    inFile.close();
    outFile.close();

    // tries in creating a SUCCESS file to indicate completion
    if (!fileManagement::CreateEmptyFileInDir(outputDir, "SUCCESS")) {
        std::cerr << "Failed to create SUCCESS file." << std::endl;
    } else {
        std::cout << "Reduction process completed successfully." << std::endl;
    }
}
// end function announces the completion of the reduction process
void Reduce::end() {
    std::cout << "Reduction process ended." << std::endl;
}
