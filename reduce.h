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
#include <unordered_map>

class Reduce { 
public:
    // Constructor
    Reduce(std::string tmp, std::string out, std::string mapRes);

    // Sort
    bool Sort();

    // Reduce
    void reduce();
private:
    // Any method of the class can access these members
    std::string mTmp;
    std::string mOut;
    std::string mMapRes;
    static constexpr char mSortRes[] = "sort_res.txt";
    static constexpr char mReduceRes[] = "reduce_res.txt";
};