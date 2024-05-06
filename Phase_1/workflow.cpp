/* 
workflow.cpp
Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase I 
04/22/2024

Summary: workflow.cpp contains the workflow class implementation that manages the 
execution of the MapReduce workflow.It initializes the map and reduce classes, 
iterates through input files, and ensures proper execution and file handling.

*/
#include "Workflow.h"
#include "map.h"
#include "Reduce.h"
#include "fileManagement.h"
#include <filesystem>
#include <iostream>

// constructor: Initializes paths for input, output, and temporary directories
Workflow::Workflow(const std::string& inputD, const std::string& outputD, const std::string& tempD)
    : inputDir(inputD), outputDir(outputD), tempDir(tempD) {}

// executes the MapReduce workflow
bool Workflow::execute() {
    std::cout << "\n...Please Stand By..." << std::endl;
    // count of processed files
    int countFiles = 0;  

    // instantiate a mapper object with the temporary directory
    MapClass mapper(tempDir);
   // starts the mapping process
    mapper.start();  

    // iterate over each file in the input directory
    for (const auto& entry : std::filesystem::directory_iterator(inputDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::string filepath = entry.path().string();
            // increment file count
            countFiles++;  
            fileManagement reader;

            // open the file for reading
            if (!reader.openFile(filepath, std::ios::in)) {
                std::cerr << "Failed to open file: " << filepath << std::endl;
                // skip to the next file if opening fails
                continue;  
            }

            std::string line;
            // reads the file line by line
            while (reader.readNextBlock(line)) {
                mapper.MapFunction(entry.path().filename().string(), line);
            }
            // closes the file after reading
            reader.closeFile();
        }
    }
    
    // end the mapping process
    mapper.end();  
    // if no text files were processed returns an error
    if (countFiles == 0) {
        std::cerr << "Error: No text files found in the input directory." << std::endl;
        return false;
    }

    // instantiate a reducer object with the output directory
    Reduce reducer(outputDir);
    // start the reducing process.
    reducer.start();  
    // perform the reduction.
    reducer.reduce();  
    // ends the reducing process.
    reducer.end();  
    // returns true if the process completes successfully.
    return true;  
}

