/*
map.cpp
Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase I 
04/23/2024

The map.cpp file defines the MapClass which processes text data by tokenizing input strings, 
normalizing them,converting to lowercase and removing punctuation, and recording the 
frequency of each word. It outputs these word counts to a specified temporary directory file, 
supporting the mapping phase of a MapReduce workflow by preparing data for subsequent reduction.
*/
//included for use of map functions
#include "map.h" 
//used, for algorithms like std::transform and std::remove_if
#include <algorithm> 
// used for file input/output operations
#include <fstream> 
// used for input and output stream operations, like std::cout
#include <iostream> 
// used for string stream operations, used to tokenize strings
#include <sstream> 
// used for character handling functions, like ::tolower
#include <cctype> 
//added for creation of vector 'buffer'
#include <vector>
//added for additonal syntax on 'outputstring' to out file
#include <string>

// constructor: Initializes a MapClass object with a specified directory for temporary files
MapClass::MapClass(const std::string& tempD) : tempDir(tempD) {}
// start function Indicates the beginning of the mapping process
void MapClass::start() {
    std::cout << "Mapping process started." << std::endl;
}
// MapFunction processes the text data, tokenizes it, converts to lowercase, removes punctuation, and exports counts
void MapClass::MapFunction(const std::string& fileName, const std::string& data) {
    // uses string stream to process the data line
    std::istringstream iss(data);
    // variable to store each word token
    std::string word;
    // loop through each word in the data string
    while (iss >> word) {
        // convert each word to lowercase
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
	// removes punctuation from each word
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
	// call ExportFunction to output the word count to a file
        ExportFunction(word, 1);
    }
}

void MapClass::end() {
    std::cout << "Mapping process ended." << std::endl;
}

// exportFunction writes the word and its count to a temporary file
void MapClass::ExportFunction(const std::string& word, int count) {
    // open the output file in append mode
    std::ofstream out(tempDir + "/map_output.txt", std::ios::app);
	//create tuple 'wordsTuple'
	std::tuple<std::string, int>wordsTuple(word, count);
	// create  vector 'buffer'
	static std::vector<std::tuple<std::string, int>> buffer; 
	//set size of buffer to be 10 tuples
	const size_t bufferSize = 10; 
	// Add tuples 'wordsTuple' to buffer
	buffer.push_back(wordsTuple); 
	

	//if buffer is not full
	if (buffer.size() >= bufferSize) { 
		  // check if the file stream is open
   		 if (out.is_open()) {
			
			for (const auto& tuple : buffer) { 
				//create string 'outputString' to output tuples with better formatting
				std::string outputString = "(\"" + std::get<0>(tuple) + "\", " + std::to_string(std::get<1>(tuple)) + ") ";
				// write each tuple in the buffer to the out file with added syntax
				out << outputString << std::endl;
			}
    	}
		//close the file
    	out.close();
		// Clear the buffer 
		buffer.clear(); 
	}
}

