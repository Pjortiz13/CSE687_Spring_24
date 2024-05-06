/*
fileManagement.h
Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase I 
04/22/2024

Summary: the fileManagement header class provides functionality to manage files
such as opening, writing, reading, and deleting files.
*/

#include <fstream>
#include <string>
#include <filesystem>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <vector>

#pragma once

class fileManagement {
public:
    // initializes the fileManagement object
    fileManagement();

    // closes any open file streams upon destruction
    ~fileManagement(); 

    // opens a file with given mode
    bool openFile(const std::string& filename, std::ios_base::openmode mode);

    // writes data followed by a newline to the currently open file
    void writeFile(const std::string& data);

    // reads the next line or data block from the open file
    bool readNextBlock(std::string& data);

    // closes the currently open file
    void closeFile();

    // clears the contents of the specified file
    void clearFile(const std::string& filename);

    // deletes the specified file
    void removeFile(const std::string& filename);

    // checks if a specified directory exists
    static bool directoryExists(const std::string& dirPath);

    // creates an empty file in the specified directory
    static bool CreateEmptyFileInDir(const std::string& dirPath, const std::string& fileName);

    // writes a map of string-uint64_t pairs to a file
    static bool WriteMapToFile(const std::unordered_map<std::string, uint64_t>& map, const std::string& filepath);

    // reads a map from a file into a string-uint64_t map
    static std::unordered_map<std::string, uint64_t> ReadMapFromFile(const std::string& filepath);

    // writes a sorted map to a file
    static bool WriteSortMapToFile(const std::unordered_map<std::string, std::vector<uint64_t>>& map, const std::string& filepath);

    // reads a sorted map from a file
    static std::unordered_map<std::string, std::vector<uint64_t>> ReadSortMapFromFile(const std::string& filepath);

private:
    // fstream used for file operations that can handle both input and output
    std::fstream file;  
};
