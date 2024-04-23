/*  reduce.h

    Group X
    Joseph Laible
    Pedro Ortiz
    Vimal Ramnarain 

    Professor Scott Roueche
    CSE  687 Object Oriented Design in C++
    Syracuse University 

    --- Project Phase 1 ---
    ----- 04/22/2024 -----
    
    This header file for the Reduce phase contains 
    the function declarations that takes the
    intermediate key-value pairs from the Map phase 
    and creates an output map with keys representing 
    unique words and values representing their counts
*/

#pragma once
#include <string>

class Reduce { 
public:
    // Constructor
    explicit Reduce(const std::string& outputDir);
    
    // Starts Reduce Phase
    void start();

    // Contains main reduce function that processes map phase results
    void reduce();

    // Ends Reduce Phase
    void end();

private:
   std::string outputDir;
};
