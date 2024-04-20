/*  
    Group X 
    Members:
    Joseph Laible
    Pedro Ortiz
    Vimal Ramnarain    
    
    CSE 687 - OOD in C++

    --- Project Phase 1 ---
    ----- 04/08/2024 -----
    
    This header file for the workflow class which is responsoible for managing
    the execution of the mapreduce workflow initialization execution of mapping, 
    reduce and handling the output genereatuin
    contains 
*/

#include <string>
#include "map.h"

class Workflow
{
public:
	// initialize the workflow w/ directories for input, intermediate and output files
    Workflow(std::string inputDir, std::string outputDir, std::string intermediateDir);
	// conducts the entire mapreduce process and returns true if sucessful, false if fails
    bool execute();

private:
    // directory containing input files, outputfiles and storing results in temp during process
	std::string inputDir, outputDir, intermediateDir;
};
