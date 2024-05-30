#pragma once

#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <vector>

//class to manage file oepartions 
class fileManagement {
public:
    // constructor then destructor
    fileManagement();
    ~fileManagement();

    // function to open a file with the given mode (read, write, etc.)
    bool openFile(const std::string& filename, std::ios_base::openmode mode);
    // Function to write data to the file
    void writeFile(const std::string& data);
    // Function to read the next block of data from the file
    bool readNextBlock(std::string& data);
    // Function to close the file
    void closeFile();
    // Function to clear the contents of a file
    void clearFile(const std::string& filename);
    // Function to remove a file from the filesystem
    void removeFile(const std::string& filename);
    // Static function to check if a directory exists
    static bool directoryExists(const std::string& dirPath);
    // Static function to create an empty file in a directory
    static bool CreateEmptyFileInDir(const std::string& dirPath, const std::string& fileName);

private:
    // File stream object to manage file operations
    std::fstream file;
};
