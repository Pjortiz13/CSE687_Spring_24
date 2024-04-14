/*
Group x
Joseph Laible
Pedro Ortiz
Vimal Ramnarain

CSE 687 OOD
Syracuse University 
Project Phase 1 

Summary:fileManagement header class provides functionality to manage files
such as opening, writing, reading, and deleting files.

*/

#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <inttypes.h>
#include <unordered_map>

#pragma once

class fileManagement
{
public:
    fileManagement();  // constructor

    // opens a file with the given filename and mode (e.g., std::ios::in for reading, std::ios::out for writing).
    bool openFile(const std::string& filename, std::ios_base::openmode mode);

    // writes data to the currently opened file.
    void writeFile(const std::string& data);

    // reads the next block of data from the file into the provided string.
    bool readNextBlock(std::string& data);

    // closes the currently opened file.
    void closeFile();

    // clears the contents of a file with the given filename.
    void clearFile(const std::string& filename);

    // deletes a file with the given filename.
    void removeFile(const std::string& filename);

    // checks if a directory exists at the given path.
    static bool directoryExists(const std::string& dirPath);

    static std::unordered_map<std::string, uint64_t> ReadMapFromFile(std::string filepath); 
    static bool WriteMapToFile(std::unordered_map<std::string, uint64_t> map, std::string filepath);
    static bool WriteSortMapToFile(std::unordered_map<std::string, std::vector<uint64_t>> map, std::string filepath);
    static std::unordered_map<std::string, std::vector<uint64_t>> ReadSortMapFromFile(std::string filepath);
    static bool CreateEmptyFileInDir(std::string dir, std::string filename);

private:
    std::fstream file;  // File stream object used for file operations.
};
