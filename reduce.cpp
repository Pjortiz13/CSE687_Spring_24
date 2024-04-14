#include <reduce.h>
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
    std::unordered_map<std::string, uint64_t> map = FileManagement::ReadMapFromFile(filepath);
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
    return FileManagement::WriteSortMapToFile(sortRes, filepath);
}

void Reduce::reduce() {
    fs::path sortResPath(mTmp);
    sortResPath.append(mSortRes);

    std::string filepath = sortResPath.string();
    std::unordered_map<std::string, std::vector<uint64_t>> map = FileManagement::ReadSortMapFromFile(filepath);

    std::unordered_map<std::string, uint64_t> reduceMap;

    for (auto it = map.begin(); it != map.end(); it++) {
        auto key = it->first;
        auto value = it->second;

        reduceMap[key] = value.size();
    }

    fs::path reduceResPath(mOut);
    reduceResPath.append(mReduceRes);

    filepath = reduceResPath.string();

    bool res = FileManagement::WriteMapToFile(reduceMap, filepath);

    bool statusFile;

    if (res) {
        statusFile = FileManagement::CreateEmptyFileInDir(mOut, "SUCCESS"); 
    } else {
        statusFile = FileManagement::CreateEmptyFileInDir(mOut, "FAILED");
    }

    if (!statusFile) {
        std::cout << "Failed to create SUCCESS/FAILED file." << std::endl;
    }
}