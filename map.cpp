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
04/22/2024

The map.cpp file defines the MapClass which processes text data by tokenizing input strings, 
normalizing them,converting to lowercase and removing punctuation, and recording the 
frequency of each word. It outputs these word counts to a specified temporary directory file, 
supporting the mapping phase of a MapReduce workflow by preparing data for subsequent reduction.
*/

#include "map.h"  //keep will be used
#include <algorithm> //keep will be used, for algorithms like std::transform and std::remove_if
#include <fstream> //keep will be used for file input/output operations
#include <iostream> //keep will be used for input and output stream operations, like std::cout
#include <sstream> //keep will be used for string stream operations, used to tokenize strings
#include <cctype> //added becuase it will be used for character handling functions, like ::tolower

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
    // check if the file stream is open
    if (out.is_open()) {
	// wite the word and its count followed by a newline
        out << word << " " << count << std::endl;
    }
    out.close();
}

/*

This is the imp ".cpp" file  for class map
This class contains the public function map that accepts a key and value
This function will tokenize the value into distinc t words (remove everything but the word, no puncation) 
This function will also make a second function called export()

//mapFunction will retrieve user input file via cmd line
//function will use getline and stringstream to make an object of each line of file
//Will use a while loop made of sslines to tokenize each word and place into mapwordTokens
//While loop from lines 66-85 will erase white space and punctions of words.


//#include "fileManagement.h" //remove not used - po
//#include <string> //remove not used - po
//#include <map> //remove not used - po
//#include <unordered_map> //remove not used - po
//#include <cstdlib> //remove not used - po
//#include <vector> //remove not used - po
//#include <cstring> //remove not used - po
//#include<tuple> //remove not used - po
//#include <algorithm> //remove duplicate - po
//#include <filesystem> //remove not used - po

//{  -remove empty spac
	
	// no body needed. everthing was done in the initialization list
//} - remove empty space
// destrutor not needed 
//MapClass::~MapClass()
//{ remove empty space

	// nothing to do at this time
//} remove empty spaace

// my reason to remove the include is to simplify the file by removing unused 
//libraries which clutter the code 

//string lines; // please removed due to scope reduction and unused variable elimation 
//string words; // same as above

	all can be removed will be handled all in fileManagement. we will have map just focusing on map - po
	fileManagement file;
	std::cout << "Please enter the full file path to your text file(.txt). Please use '\\\\' instead of '\\' when entering the filepath: ";
	std::cin >> fileNameInput;
	std::cout << "\n Please enter filepath for output file: ";
	std::cin >> fileNameOutput;
	file.openFile(fileNameInput, std::ios::in);
	std::cout << "\n Processing Raw Data from file: " << fileNameInput << "\n(removing white space, puncuations, captalization, and adding, word + , 1).\n" << "Words now have been manipulated: ";
	std::unordered_map<string, double>wordTokens;
	while (file.readNextBlock(rawData)) {
		std::stringstream ssLines(rawData);
		while (ssLines >> words) {
			wordsCounted++;
			words.erase(remove_if(words.begin(), words.end(), isspace), words.end());
			words.erase(remove_if(words.begin(), words.end(), ispunct), words.end());
			transform(words.cbegin(), words.cend(), words.begin(), [](char c) {return tolower(c); });
			ExportFunction(words, 1);*/
	//	}
//	}
/*	file.closeFile();
	std::cout << "\n\nMapfunciton completed on file: " << fileNameInput;
	std::cout << "\n\nNumber of words in file:   " << wordsCounted;
	std::cout << "\n\nWriting to file:   " << fileNameOutput;
	std::cout << "\nWriting completed";
}
*/
//ExportFunction will write a key (words) from map function, and value of 1, (for each occurence of words)
//create tuples 'wordTuple' from mapFunction of key(words),value(1)
//creates a vector to store tuples
//sets buffer size to 1000 (adjustable)
//writes output to user selected file via for loop on vector buffer
//add buffer to set touple amount
//removed user input handling to fileManagement
	/*fileManagement fileO;
	std::tuple<string, int>wordsTuple(key, value);//create tuple 'wordsTuple'
	static std::vector<std::tuple<string, int>> buffer; // create  vector 'buffer'
	const size_t buffer_size = 1000; //set size of buffer to be 1000bytes?/characters 
	buffer.push_back(wordsTuple); // Add tuples to buffer

	if (buffer.size() >= buffer_size) { //if buffer is not full

		//std::ofstream fileOutput(fileNameOutput, std::ios::app); // Open the file
		//fileO.openFile(fileNameOutput, std::ios::app);
		if (fileO.openFile(fileNameOutput, std::ios::app)) {
			for (const auto& tuple : buffer) { // write each tuple in the buffer with added syntax
				std::string outputString = "(\"" + std::get<0>(tuple) + "\", " + std::to_string(std::get<1>(tuple)) + "), ";
				fileO.writeFile(outputString);
			}
			fileO.closeFile(); // Close the file
		}
		buffer.clear(); // Clear the buffer 
	}
}
*/
