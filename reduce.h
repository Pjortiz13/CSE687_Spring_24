/*  Group X 
    Joseph Laible
    Pedro Ortiz
    Vimal Ramnarain
    
    CSE 687 - OOD in C++

    --- Project Phase 1 ---
    ----- 04/08/2024 -----
    
    This header file for the Reduce class 
    contains function declarations that take 
    a vector of intermediate key-value pairs 
    from the Map class and then creates an 
    output map with keys representing unique 
    words and values representing their counts
*/

#pragma once

#include <string>
#include <vector>
#include <inttypes.h>
#include <fstream>
#include <unordered_map>
#include "fileManagement.h"

class Reduce { 
public:
    // constructor initializes the reduce object with a specified output directory
    Reduce(std::string outputDir); 

    // reduce fucntion processes a word and its occurrences to compute a reduced value
    bool reduce(std::string word, std::vector<int> occurrences); 

    // export funciton writes the reduced key-value pair to the output file
    bool Export(std::string key, int reducedValue);

    // start function preps the environment before reducing (e.g., opens output file)
    void start();

    // end function finalizes the reducing process (e.g., closes the output file)
    void end();

private:
    // fileManagement object to handle file writing operations
    fileManagement fileWriter;

    // output directory path where the reduced results are stored
    std::string outputDir = "";
};
