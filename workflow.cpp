#include "workflow.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <filesystem>
#include "map.h"
#include "reduce.h"
#include "fileManagement.h"

/**
 Executes the entire MapReduce workflow.
 orchestrates the process from reading the input files mapping the contents to intermediate outputs,
 sorting the intermediate results, and finally reducing them to the final word counts which are
 output to the specified directory.@return bool True if the workflow completes successfully, 
 false if any step fails (i.e if no input files found).
 */

/*
 constructor for the Workflow class.
 initializes directories for input, output, and intermediate data.
 */

Workflow::Workflow(std::string inputD, std::string outputD, std::string intermediateD)
    : inputDir(inputD), outputDir(outputD), intermediateDir(intermediateD) {}

// initializes the Workflow object with directories specified for input, intermediate, and output operations.
bool Workflow::execute() 
{
    // prints message to indicate the process has started.
    std::cout << "\n...Please Stand By..." << std::endl;
    // a variable to count the number of processed files.
    int countFiles = 0;  

    // mapper phase
    // creates a mapper object that will handle the mapping phase.
    Map mapper(this->intermediateDir);
    // initialize the mapper process possibly setting up necessary resources.
    mapper.start();  

    // iterate over each file in the input directory.
    for (const auto& entry : std::filesystem::directory_iterator(this->inputDir))
    {
        // stores the file path as a string.
        std::string filepath = entry.path().string();  
        // checks if the file extension is a .txt
        if (entry.path().extension() == ".txt")
        {
            // increment the file count.
            countFiles++;  
            // creates a fileManager object to handle file reading.
            fileManager reader;  

            // opens the file for reading.
            reader.open(filepath, std::ios::in);
            std::string line;

            // reads the file line by line.
            while (std::getline(reader.getFileStream(), line))
            {
                // passes each line to the mapper to process.
                mapper.map(entry.path().filename().string(), line);
            }

            // closes the file after reading is complete.
            reader.close();  
        }
    }

    // finalize the mapping phase, possibly closing resources or finalizing intermediate output.
    mapper.end();  

    // check if no files were processed.
    if (countFiles == 0)  
    {
        // prints an error message if no files were found.
        std::cout << "Error: text files not found in the input directory." << std::endl;
        // return false to indicate failure.
        return false;  
    }

    // sorter phase
    // creates a map to hold the sorted intermediate data.
    std::unordered_map<std::string, std::vector<int>> sorterMap;
    fileManager Ireader;

    // opens the intermediate file for reading.
    Ireader.open(this->intermediateDir + "/temp.txt", std::ios::in);
    std::string line;

    // reads the intermediate file line by line.
    while (std::getline(Ireader.getFileStream(), line))
    {
        // finds the position of the delimiter ':'.
        size_t pos = line.find(':');  
        // extracts the key word before the delimiter.
        std::string key = line.substr(0, pos);  
        // extracts the value (count) after the delimiter and convert to integer.
        int value = std::stoi(line.substr(pos + 1));  

        // adds the value to the vector of counts associated with the key.
        sorterMap[key].push_back(value);  
    }

    // closes the intermediate file after reading.
    Ireader.close();  

    // reducer phase
    // creates a reducer object for the reducing phase.
    Reduce reducer(this->outputDir);
    // Initialize the reducer process.
    reducer.start();  

    // iterates over each key-value pair in the sorter map.
    for (const auto& pair : sorterMap)
    {
        // calls the reduce function  on each pair to combine counts.
        reducer.reduce(pair.first, pair.second);
    }

    // finalizes the reducing phase.
    reducer.end();  

    // print a completion message.
    std::cout << "\nProcess is complete! Check the output directory." << std::endl;
    // return true to indicate success.
    return true;  
}
