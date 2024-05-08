/*
fileManagement.h
Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase II
05/08/2024

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

private:
    std::fstream file;
};
