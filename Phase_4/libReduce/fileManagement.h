#pragma once

#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <vector>

class fileManagement {
public:
    fileManagement();
    ~fileManagement();

    bool openFile(const std::string& filename, std::ios_base::openmode mode);
    void writeFile(const std::string& data);
    bool readNextBlock(std::string& data);
    void closeFile();
    void clearFile(const std::string& filename);
    void removeFile(const std::string& filename);
    static bool directoryExists(const std::string& dirPath);
    static bool CreateEmptyFileInDir(const std::string& dirPath, const std::string& fileName);

private:
    std::fstream file;
};
