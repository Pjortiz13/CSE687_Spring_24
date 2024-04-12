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
		ifstream fileInput(fileNameInput);
		cout << "\n Processing Raw Data from file: "<< fileNameInput << "\n(removing white space, puncuations, captalization, and adding, word + , 1).\n"<<"Words now have been manipulated: ";

		
		map<string,double>wordTokens;
	
		
		while (getline(fileInput, rawData)) { 
			stringstream ssLines(rawData); 

		
		
			
			while (ssLines >> words) {
				
				
				wordsCounted++;
				
				words.erase(remove_if(words.begin(), words.end(), isspace),words.end()); //remove if pg 576 C++SL, & https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c 
				
				 
				words.erase(remove_if(words.begin(), words.end(), ispunct), words.end());

				
				transform(words.cbegin(), words.cend(), words.begin(), [](char c) {return tolower(c); });
				
				words.insert(0, "\"");
				words.insert(words.length(), "\"" );
												
				wordTokens.insert(make_pair(words, wordTokens[words]++));

				
				cout << words<<" "; 


			}
			cout << "\nManipulated words added to map 'wordTokens' :\n";

			
			for (auto wordList : wordTokens)
				cout << "\n  (" << wordList.first << """, [" << wordList.second << "]),";
		}

		
		fileInput.close();

		cout << "\n\nMapfunciton completed on file: " << fileNameInput; 

		cout << "\n\nNumber of words in file:   " << wordsCounted;  



}


//void MapClass::ExportFunction(string& fileNameOutput, string& rawData)
//{
	//cout << "Please enter the full file path to your text file(.txt). Please use \\ instead of \ for the directory navigation: ";
	//cin >> fileNameInput; // User inputs file name 
	//ifstream fileInput(fileNameInput); //retriev file via user input, ref pg 793 C++SL


	//





//}










