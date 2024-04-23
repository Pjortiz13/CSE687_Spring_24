/*
fileManagement.cpp
Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase I 
04/22/2024

Summary: fileManagement class provides functions for managing
file operations such as opening, writing, reading, and deleting
files, as well as handling structured data in files.

*/

#include "fileManagement.h"
#include <iostream>
#include <sstream>
#include <iterator>

// Constructor initializes an instance of the fileManagement class
fileManagement::fileManagement() {}

// Destructor ensures that the file stream is closed when the object is destroyed
fileManagement::~fileManagement() {
    if (file.is_open()) {
        file.close();
    }
}

// Opens a file with specified filename and mode (i.e. input or output)
bool fileManagement::openFile(const std::string& filename, std::ios_base::openmode mode) {
    if (file.is_open()) {
    // Ensures any previously opened file is closed first
        file.close();  
    }
    file.open(filename, mode);
    // Returns true if the file successfully opens
    return file.is_open();  
}

// Writes a string of data to the currently opened file, followed by a newline
void fileManagement::writeFile(const std::string& data) {
    if (file) {
        file << data << std::endl;
    }
}

// Reads the next block (typically a line) from the currently opened file
bool fileManagement::readNextBlock(std::string& data) {
    // Returns true if reading is successful
    return std::getline(file, data) ? true : false;  
}

// Closes the currently opened file
void fileManagement::closeFile() {
    if (file.is_open()) {
        file.close();
    }
}

// Clears the contents of a file specified by filename
void fileManagement::clearFile(const std::string& filename) {
    // Opens with truncation mode to delete contents
    std::ofstream out(filename, std::ios::trunc);  
    // Closes the file immediately after opening to truncate it
    out.close();  
}

// Removes a file specified by filename
void fileManagement::removeFile(const std::string& filename) {
    // Uses the filesystem library to delete the file
    std::filesystem::remove(filename);  
}

// Checks if a directory exists at the specified path
bool fileManagement::directoryExists(const std::string& dirPath) {
    // Returns true if the path is a directory
    return std::filesystem::is_directory(dirPath);  
}

// Creates an empty file in the specified directory
bool fileManagement::CreateEmptyFileInDir(const std::string& dirPath, const std::string& fileName) {
    std::filesystem::path filePath = std::filesystem::path(dirPath) / fileName;
    std::ofstream outFile(filePath);
    // Returns true if the file was successfully created
    return outFile.is_open(); 
}
