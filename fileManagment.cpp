/*
Group x
Joseph Laible
Pedro Ortiz
Vimal Ramnarain

CSE 687 OOD
Syracuse University 
Project Phase 1 

Summary: implementation of fileManagement class which provides functionality to manage files,
such as opening, writing, reading, and deleting files.

*/

#include "fileManagement.h"

// constructor
fileManagement::fileManagement()
{
}

// opens a file with the given filename and mode (e.g., std::ios::in for reading, std::ios::out for writing).
bool fileManagement::openFile(const std::string& filename, std::ios_base::openmode mode)
{
    file.open(filename, mode);
    return file.is_open();
}

// writes data to the currently opened file.
void fileManagement::writeFile(const std::string& data)
{
    file << data << std::endl;
}

// reads the next block of data from the file into the provided string.
bool fileManagement::readNextBlock(std::string& data)
{
    if (std::getline(file, data))
        return true;
    return false;
}

// closes the currently opened file.
void fileManagement::closeFile()
{
    file.close();
}

// clears the contents of a file with the given filename.
void fileManagement::clearFile(const std::string& filename)
{
    file.open(filename, std::ios::out);
    file.close();
}

// deletes a file with the given filename.
void fileManagement::removeFile(const std::string& filename)
{
    std::filesystem::remove(filename);
}

// checks if a directory exists at the given path.
bool fileManagement::directoryExists(const std::string& dirPath)
{
    std::filesystem::path path(dirPath);
    return std::filesystem::is_directory(path);
}
