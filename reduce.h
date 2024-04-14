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
    // constructor of the class
    Reduce(std::string outputDir); 

    //reduce method that takes a string and a vector of integers as an arguement
	bool reduce(std::string word, std::vector<int> occurences); 
	bool Export(std::string key, int reducedValue);
	void start();
	void end();

private:
    // Any method of the class can access these members
	FileManager fileWriter;
	std::string outputDir = "";
};
