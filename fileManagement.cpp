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
    // ensure any previously opened file is closed first
        file.close();  
    }
    file.open(filename, mode);
    // returns true if the file successfully opens
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
    // returns true if reading is successful
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
    // open with truncation mode to delete contents
    std::ofstream out(filename, std::ios::trunc);  
    // close the file immediately after opening it to truncate it
    out.close();  
}

// removes a file specified by filename
void fileManagement::removeFile(const std::string& filename) {
    // uses the filesystem library to delete the file
    std::filesystem::remove(filename);  
}

// checks if a directory exists at the specified path
bool fileManagement::directoryExists(const std::string& dirPath) {
    // returns true if the path is a directory
    return std::filesystem::is_directory(dirPath);  
}

// creates an empty file in the specified directory
bool fileManagement::CreateEmptyFileInDir(const std::string& dirPath, const std::string& fileName) {
    std::filesystem::path filePath = std::filesystem::path(dirPath) / fileName;
    std::ofstream outFile(filePath);
    // returns true if the file was successfully created
    return outFile.is_open(); 
}

// writes a map of string to uint64_t to a file
bool fileManagement::WriteMapToFile(const std::unordered_map<std::string, uint64_t>& map, const std::string& filepath) {
    std::ofstream out(filepath);
    if (!out.is_open()) return false;
    for (const auto& pair : map) {
        out << pair.first << " " << pair.second << "\n";
    }
    out.close();
    return true;
}

// reads a map of string to uint64_t from a file
std::unordered_map<std::string, uint64_t> fileManagement::ReadMapFromFile(const std::string& filepath) {
    std::unordered_map<std::string, uint64_t> map;
    std::ifstream in(filepath);
    std::string key;
    uint64_t value;
    while (in >> key >> value) {
        map[key] = value;
    }
    in.close();
    return map;
}

// writes a sorted map (string to vector<uint64_t>) to a file
bool fileManagement::WriteSortMapToFile(const std::unordered_map<std::string, std::vector<uint64_t>>& map, const std::string& filepath) {
    std::ofstream out(filepath);
    if (!out.is_open()) return false;
    for (const auto& pair : map) {
        out << pair.first << " ";
        std::copy(pair.second.begin(), pair.second.end(), std::ostream_iterator<uint64_t>(out, " "));
        out << "\n";
    }
    out.close();
    return true;
}

// reads a sorted map (string to vector<uint64_t>) from a file
std::unordered_map<std::string, std::vector<uint64_t>> fileManagement::ReadSortMapFromFile(const std::string& filepath) {
    std::unordered_map<std::string, std::vector<uint64_t>> map;
    std::ifstream in(filepath);
    std::string key, line;
    uint64_t value;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        iss >> key;
        std::vector<uint64_t> values;
        while (iss >> value) {
            values.push_back(value);
        }
        map[key] = values;
    }
    in.close();
    return map;
}
