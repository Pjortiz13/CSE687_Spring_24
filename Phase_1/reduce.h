/*
reduce.h
Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase I 
04/22/2024
    
    This header file for the Reduce class 
    contains function declarations that take 
    a vector of intermediate key-value pairs 
    from the Map class and then creates an 
    output map with keys representing unique 
    words and values representing their counts
*/

#pragma once

#include <string>

class Reduce { 
public:
    // Constructor
    //simplified to only take one paramter
    explicit Reduce(const std::string& outputDir); 
    
    void start();
    void reduce();
    void end();

private:
   std::string outputDir;
};
