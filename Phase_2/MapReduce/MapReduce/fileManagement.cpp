/*
fileManagement.cpp
Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase II
05/08/2024

summary: fileManagement class provides functions for managing
file operations such as opening, writing, reading, and deleting
files, as well as handling structured data in files.
*/

#include "fileManagement.h"
#include <iostream>
#include <sstream>
#include <iterator>
// constructor initializes an instance of the fileManagement class
fileManagement::fileManagement() {}
// destructor ensures that the file stream is closed when the object is destroyed
fileManagement::~fileManagement() {
    if (file.is_open()) {
        file.close();
    }
}
// opens a file with specified filename and mode i.e. input or output
bool fileManagement::openFile(const std::string& filename, std::ios_base::openmode mode) {
    if (file.is_open()) {
        file.close();
    }
    file.open(filename, mode);
    return file.is_open();
}
// writes a string of data to the currently opened file, followed by a newline
void fileManagement::writeFile(const std::string& data) {
    if (file) {
        file << data << std::endl;
    }
}
// reads the next block (typically a line) from the currently opened file
bool fileManagement::readNextBlock(std::string& data) {
    return std::getline(file, data) ? true : false;
}
// closes the currently opened file
void fileManagement::closeFile() {
    if (file.is_open()) {
        file.close();
    }
}
// clears the contents of a file specified by filename
void fileManagement::clearFile(const std::string& filename) {
    std::ofstream out(filename, std::ios::trunc);
    out.close();
}
// removes a file specified by filename
void fileManagement::removeFile(const std::string& filename) {
    std::filesystem::remove(filename);
}
// checks if a directory exists at the specified path
bool fileManagement::directoryExists(const std::string& dirPath) {
    return std::filesystem::is_directory(dirPath);
}
// creates an empty file in the specified directory
bool fileManagement::CreateEmptyFileInDir(const std::string& dirPath, const std::string& fileName) {
    std::filesystem::path filePath = std::filesystem::path(dirPath) / fileName;
    std::ofstream outFile(filePath);
    return outFile.is_open();
}
