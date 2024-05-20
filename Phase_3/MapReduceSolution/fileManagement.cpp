#include "fileManagement.h"
#include <iostream>
#include <sstream>
#include <iterator>

fileManagement::fileManagement() {}
fileManagement::~fileManagement() {
    if (file.is_open()) {
        file.close();
    }
}

bool fileManagement::openFile(const std::string& filename, std::ios_base::openmode mode) {
    if (file.is_open()) {
        file.close();
    }
    file.open(filename, mode);
    return file.is_open();
}

void fileManagement::writeFile(const std::string& data) {
    if (file) {
        file << data << std::endl;
    }
}

bool fileManagement::readNextBlock(std::string& data) {
    return std::getline(file, data) ? true : false;
}

void fileManagement::closeFile() {
    if (file.is_open()) {
        file.close();
    }
}

void fileManagement::clearFile(const std::string& filename) {
    std::ofstream out(filename, std::ios::trunc);
    out.close();
}

void fileManagement::removeFile(const std::string& filename) {
    std::filesystem::remove(filename);
}

bool fileManagement::directoryExists(const std::string& dirPath) {
    return std::filesystem::is_directory(dirPath);
}

bool fileManagement::CreateEmptyFileInDir(const std::string& dirPath, const std::string& fileName) {
    std::filesystem::path filePath = std::filesystem::path(dirPath) / fileName;
    std::ofstream outFile(filePath);
    return outFile.is_open();
}
