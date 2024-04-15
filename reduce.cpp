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
#include <filesystem>
#include <vector>
namespace fs = std::filesystem;

// Constructor
Reduce::Reduce(std::string tmp, std::string out, std::string mapRes) 
    : mTmp(tmp), mOut(out), mMapRes(mapRes) {}

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

void Reduce::reduce() {
    fs::path sortResPath(mTmp);
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
