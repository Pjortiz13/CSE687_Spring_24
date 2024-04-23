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
    // Initializes the fileManagement object
    fileManagement();

    // Closes any open file streams upon destruction
    ~fileManagement(); 

    // Opens a file with given mode
    bool openFile(const std::string& filename, std::ios_base::openmode mode);

    // Writes data followed by a newline to the currently open file
    void writeFile(const std::string& data);

    // Reads the next line or data block from the open file
    bool readNextBlock(std::string& data);

    // Closes the currently open file
    void closeFile();

    // Clears the contents of the specified file
    void clearFile(const std::string& filename);

    // Deletes the specified file
    void removeFile(const std::string& filename);

    // Checks if a specified directory exists
    static bool directoryExists(const std::string& dirPath);

    // Creates an empty file in the specified directory
    static bool CreateEmptyFileInDir(const std::string& dirPath, const std::string& fileName);

private:
    // fstream used for file operations that can handle both input and output
    std::fstream file;  
};
