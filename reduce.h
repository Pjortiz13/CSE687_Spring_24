/*  Vimal Ramnarain
    Group X 
    Members:
    Joseph Laible
    Pedro Ortiz
    
    
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
//#include <vector> // not used in revised version
//#include <inttypes.h> // not use in revised version
//#include <unordered_map> // not used in revised version

class Reduce { 
public:
    // Constructor
    //simplified to only take one paramter
    explicit Reduce(const std::string& outputDir //(std::string tmp, std::string out, std::string mapRes);
    
    void start();
    void reduce();
    void end();
    // Sort
    //bool Sort();

    // Reduce
    //void reduce();
private:
   std::string outputDir;
    /* // Any method of the class can access these members
    std::string mTmp;
    std::string mOut;
    std::string mMapRes;
    static constexpr char mSortRes[] = "sort_res.txt";
    static constexpr char mReduceRes[] = "reduce_res.txt";
    */
};
