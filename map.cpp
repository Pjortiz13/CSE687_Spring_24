//Group X Joseph I Laible
// Professor Scott Roueche
// CSE  687 Object Oriented Design in C++
// Syracuse University 
//Project Phase I 
//04/07/2024
// This is the imp ".cpp" file  for class MapClass
// This class contains the public method map that accepts a key and value
// This function will tokenize the value into distinc t words (remove everything but the word, no puncation) 
//This function will also make a second function called export()
#include "map.h"
#include <string>
#include <map>
#include <fstream> //file stream lib
#include <iostream> //io stream lib
#include <cstdlib>
#include <sstream>//stringstream lib

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::getline;
using std::fclose;
using std::stringstream;//ref page 805
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
//While loop from lines 66-85 will erase white space and punctions of words. Additionally insert “” around words and insert ,1 for each word occurrence. 
void MapClass::MapFunction(string& fileNameInput, string& rawData)
{
	cout << "Please enter the full file path to your text file(.txt). Please use '\\\\' instead of '\\' when entering the filepath: ";
	cin >> fileNameInput;
	cout << "\n Please enter filepath for output file: ";
	cin >> fileNameOutput;
	ifstream fileInput(fileNameInput);
	cout << "\n Processing Raw Data from file: " << fileNameInput << "\n(removing white space, puncuations, captalization, and adding, word + , 1).\n" << "Words now have been manipulated: ";


	map<string, double>wordTokens;
	


	while (getline(fileInput, rawData)) {
		stringstream ssLines(rawData);
		while (ssLines >> words) {


		wordsCounted++;
		words.erase(remove_if(words.begin(), words.end(), isspace), words.end());
		words.erase(remove_if(words.begin(), words.end(), ispunct), words.end());
		transform(words.cbegin(), words.cend(), words.begin(), [](char c) {return tolower(c); });
		wordTokens.insert(make_pair(words, wordTokens[words]++));
		ExportFunction(words, 1);
			
	
		}
		
		
		
	

	}

	fileInput.close();
	

	cout << "\n\nMapfunciton completed on file: " << fileNameInput;
	cout << "\n\nNumber of words in file:   " << wordsCounted;
	cout << "\n\nWriting map 'wordTokens to file:   " << fileNameOutput;
	cout << "\nWriting completed";
}

//ExportFunction will write a key (words) from map function, and value of 1, (for each occurence of words)
//written to user selected output file (fileNameOutput)
void MapClass::ExportFunction(string& key, int value)
{
	
	tuple<string, int>wordsTuple(key, value);
	ofstream fileOutput(fileNameOutput,ios::app);
	if (fileOutput.is_open()) {	
		fileOutput << "(\"" << get<0>(wordsTuple) << "\", " << get<1>(wordsTuple) << "), ";
		fileOutput.close();
	}
}










