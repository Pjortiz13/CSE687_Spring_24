#include "fileManagement.h"
#include <iostream>
#include <sstream>
#include <iterator>

// Constructor: Initializes the fileManagement object
fileManagement::fileManagement() {}
// Destructor: Ensures the file is closed if it's open
fileManagement::~fileManagement() {
    if (file.is_open()) {
        file.close();
    }
}

// Function to open a file with the specified mode (read, write, etc.)
bool fileManagement::openFile(const std::string& filename, std::ios_base::openmode mode) {
    if (file.is_open()) {
        file.close();
    }
    file.open(filename, mode);
    return file.is_open();
}

// Function to write data to the file
void fileManagement::writeFile(const std::string& data) {
    if (file) {
        file << data << std::endl;
    }
}

// Function to read the next block of data from the file
bool fileManagement::readNextBlock(std::string& data) {
    return std::getline(file, data) ? true : false;
}

// Function to close the file
void fileManagement::closeFile() {
    if (file.is_open()) {
        file.close();
    }
}

// Function to clear the contents of a file
void fileManagement::clearFile(const std::string& filename) {
    std::ofstream out(filename, std::ios::trunc);
    out.close();
}

// Function to remove a file from the filesystem
void fileManagement::removeFile(const std::string& filename) {
    std::filesystem::remove(filename);
}

// Static function to check if a directory exists
bool fileManagement::directoryExists(const std::string& dirPath) {
    return std::filesystem::is_directory(dirPath);
}

// Static function to create an empty file in a directory
bool fileManagement::CreateEmptyFileInDir(const std::string& dirPath, const std::string& fileName) {
    std::filesystem::path filePath = std::filesystem::path(dirPath) / fileName;
    std::ofstream outFile(filePath);
    return outFile.is_open();
}
