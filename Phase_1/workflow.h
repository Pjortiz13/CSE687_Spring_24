
/* 
workflow.h
Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase I 
04/22/2024
summary: defines the Workflow class that manages the orchestration of the MapReduce process

*/
#pragma once
#include <string>


class Workflow {
public:
    // constructor for Workflow, initializes directories for input, output, and intermediate processing
    Workflow(const std::string& inputDir, const std::string& outputDir, const std::string& tempDir);

    // executes the map-reduce workflow; returns true if successful
    bool execute();

private:
    // cirectory where input files are located
    std::string inputDir;
    
    // directory where output files will be stored
    std::string outputDir;
    
    // temporary directory used for intermediate files
    std::string tempDir;
};
