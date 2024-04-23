/*  Vimal Ramnarain
    Group X 
    Members:
    Joseph Laible
    Pedro Ortiz
    
    CSE 687 - OOD in C++

    --- Project Phase 1 ---
    ----- 04/08/2024 -----
    
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
// used for file stream ops
#include <fstream>
//string stream ops
#include <sstream>
// managing collection of key values
#include <unordered_map>
//#include <filesystem>
//#include <vector>
//namespace fs = std::filesystem;


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
    std::unordered_map<std::string, int> wordCounts;
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
        outFile << pair.first << " " << pair.second << std::endl;
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


//

                            //tmp, std::string out, std::string mapRes) 
    //: mTmp(tmp), mOut(out), mMapRes(mapRes) {}
/*
bool Reduce::Sort() {
    // Handle '/' for Linux and Mac and '\'for Windows
    fs::path mapResPath(mTmp);
    mapResPath.append(mMapRes);

    std::string filepath = mapResPath.string();
    std::unordered_map<std::string, uint64_t> map = fileManagement::ReadMapFromFile(filepath);
    std::unordered_map<std::string, std::vector<uint64_t>> sortRes;

    for (auto it = map.begin(); it != map.end(); it++) {
        auto key = it->first;
        auto value = it->second;

        auto sortIt = sortRes.find(key);
        if (sortIt != sortRes.end()){
            sortIt->second.push_back(1);
        } else {
            sortRes[key] = std::vector<uint64_t>(1, 1);  
        }
    }

    fs::path sortResPath(mTmp);
    sortResPath.append(mSortRes);

    filepath = sortResPath.string();
    return fileManagement::WriteSortMapToFile(sortRes, filepath);
}
*/

    /*fs::path sortResPath(mTmp);
    sortResPath.append(mSortRes);

    std::string filepath = sortResPath.string();
    std::unordered_map<std::string, std::vector<uint64_t>> map = fileManagement::ReadSortMapFromFile(filepath);

    std::unordered_map<std::string, uint64_t> reduceMap;

    for (auto it = map.begin(); it != map.end(); it++) {
        auto key = it->first;
        auto value = it->second;

        reduceMap[key] = value.size();
    }

    fs::path reduceResPath(mOut);
    reduceResPath.append(mReduceRes);

    filepath = reduceResPath.string();

    bool res = fileManagement::WriteMapToFile(reduceMap, filepath);

    bool statusFile;

    if (res) {
        statusFile = fileManagement::CreateEmptyFileInDir(mOut, "SUCCESS"); 
    } else {
        statusFile = fileManagement::CreateEmptyFileInDir(mOut, "FAILED");
    }

    if (!statusFile) {
        std::cout << "Failed to create SUCCESS/FAILED file." << std::endl;
    }
}
*/
