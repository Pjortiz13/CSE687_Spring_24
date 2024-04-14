/*  Group X 
    Joseph Laible
    Pedro Ortiz
    Vimal Ramnarain
    
    CSE 687 - OOD in C++

    --- Project Phase 1 ---
    ----- 04/08/2024 -----
    

The reduce class consolidates the counts of unique words into a single total 
for each and records the word along with its aggregated count to an output directory.
*/

#include "reduce.h"

// the constructor accepts outputDir as a parameter to set the output directory
Reduce::Reduce(std::string outputDir)
{
	this->outputDir = outputDir; // sets the class member outputDir to the passed argument
}

// reduce function iterates through the vector and sums up all of the occurrences
bool Reduce::reduce(std::string word, std::vector<int> occurrences) {

    // variable to store the total count of occurrences of the word
	int totalOccurrences = 0; 

	// loops through each count in the occurrences vector
	for (auto& timesUsed : occurrences) {
		totalOccurrences += timesUsed;
	}

    // calls in Export to write the total count to the file
	Export(word, totalOccurrences); 
	// return true to indicate success
    return true; 
}

// Export function to write the key (word) and its reduced value (total occurrences) to the output file
bool Reduce::Export(std::string key, int reducedValue)
{
    // convert the reduced value to string
	std::string stringRep = std::to_string(reducedValue); 
    // concatenate the key and its occurrences
	std::string keyPlusOccurrences = key + " " + stringRep; 

    // fileWriter is called to write the result to the output file
	fileWriter.write(keyPlusOccurrences); 

    // return true to indicate success
	return true; 
}

// star function to prepare files for writing the output
void Reduce::start()
{
    // delete SUCCESS.txt if it exists
	fileWriter.deleteFile(this->outputDir + "SUCCESS.txt"); 

    // clears the contents of out.txt
	fileWriter.clear(this->outputDir + "out.txt"); 
     // opens out.txt for appending data
	fileWriter.open(this->outputDir + "out.txt", std::ios::out | std::ios::app);
}

// end function called to finalizes the reduce process and marks completion
void Reduce::end()
{
	// closes the currently open file 
    fileWriter.close(); 

    // open SUCCESS.txt to indicate completion
	fileWriter.open(this->outputDir + "SUCCESS.txt", std::ios::out); 

    // closes SUCCESS.txt after marking completion
	fileWriter.close(); 
}
