/*Group X Joseph I Laible
 Professor Scott Roueche
 CSE  687 Object Oriented Design in C++
 Syracuse University 

Project Phase I 
04/07/2024

This is the imp ".cpp" file  for class map
This class contains the public function map that accepts a key and value
This function will tokenize the value into distinc t words (remove everything but the word, no puncation) 
This function will also make a second function called export()
*/

#include "map.h"
#include "fileManagement.h"
#include <string>
#include <map>
#include <unordered_map>
#include <fstream> //file stream lib
#include <iostream> //io stream lib
#include <cstdlib>
#include <sstream>//stringstream lib
#include <vector>
#include <cstring>//prototype for strtok, ref c++ 928
#include <algorithm>//needed for 'for_each'
#include<tuple>
#include <algorithm>
#include <filesystem>


string lines;//variable for lines of file
string words;//varible for words in each line

// default constructor
MapClass::MapClass()
	
{
	
	// no body needed. everthing was done in the initialization list
}




MapClass::~MapClass()
{

	// nothing to do at this time
}


//mapFunction will retrieve user input file via cmd line
//function will use getline and stringstream to make an object of each line of file
//Will use a while loop made of sslines to tokenize each word and place into mapwordTokens
//While loop from lines 66-85 will erase white space and punctions of words.
void MapClass::MapFunction(string& fileNameInput, string& rawData)
{ 
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
			ExportFunction(words, 1);
		}


	}

	file.closeFile();



	std::cout << "\n\nMapfunciton completed on file: " << fileNameInput;
	std::cout << "\n\nNumber of words in file:   " << wordsCounted;
	std::cout << "\n\nWriting to file:   " << fileNameOutput;
	std::cout << "\nWriting completed";







}

//ExportFunction will write a key (words) from map function, and value of 1, (for each occurence of words)
//create tuples 'wordTuple' from mapFunction of key(words),value(1)
//creates a vector to store tuples
//sets buffer size to 1000 (adjustable)
//writes output to user selected file via for loop on vector buffer
//add buffer to set touple amount

void MapClass::ExportFunction(string& key, int value)
{
	fileManagement fileO;
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





