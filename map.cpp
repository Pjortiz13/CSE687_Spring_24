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

//Mapfunction to retrieve file and call additional function export
//request user input for filepath to open file
void MapClass::MapFunction(string& fileNameInput, string& rawData)
{
		cout << "Please enter the full file path to your text file(.txt). Please use '\\\\' instead of '\\' when entering the filepath: "; 
		cin >> fileNameInput; // User inputs file name 
		ifstream fileInput(fileNameInput); //retriev/open file via user input, ref pg 793 C++SL
		cout << "\n Processing Raw Data from file: "<< fileNameInput << "\n(removing white space, puncuations, captalization, and adding, word + , 1).\n"<<"Words now have been manipulated: ";

		//map used to store processed data **chagne to map ref 689/691 C++how to program, dietel
		//map performs fast storage and retrieval of uniuqe keys and associated values. These values will be in order by default use of map, for unordered use unorderdmap 
		map<string,double>wordTokens;
	
		//getline used to read line by line function reads all characters until the end of file is reached. while loop to go through each line o file 
		while (getline(fileInput, rawData)) { //getline pgs 677,713,769
			stringstream ssLines(rawData); //make and object for each line of the file

		
		
			
			while (ssLines >> words) {
				
				//get total word count for all words
				wordsCounted++;
				//remove white space 
				words.erase(remove_if(words.begin(), words.end(), isspace),words.end()); //remove if pg 576 C++SL, & https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c 
				
				//remove puncuations 
				words.erase(remove_if(words.begin(), words.end(), ispunct), words.end());

				//remove capitalizations aka lowercase all words  ref pg 225, 564-565 C++SL, is/to functions ref pg 896 
				transform(words.cbegin(), words.cend(), words.begin(), [](char c) {return tolower(c); }); //formatting reference pg 686

				//add + ,1 *via .insert / length() used add "" in  place positions start and end of word see685 C++SL & 
				words.insert(0, "\"");
				words.insert(words.length(), "\"" );
				
				

				//tokenize data via addint each word to map 'wordTokens'
				//wordTokens.insert(words/number of occruence of words);
				wordTokens.insert(make_pair(words, wordTokens[words]++));

				//allow user to see new set of words
				cout << words<<" "; 


			}
			cout << "\nManipulated words added to map 'wordTokens' :\n";

			//display map Wordtokenes to user 
			for (auto wordList : wordTokens)
				cout << "\n  (" << wordList.first << """, [" << wordList.second << "]),";
		}

		//close file after data has been utilized
		fileInput.close();

		cout << "\n\nMapfunciton completed on file: " << fileNameInput; //cout filename for user to verify

		cout << "\n\nNumber of words in file:   " << wordsCounted;  // Outputting the total word count



}


//void MapClass::ExportFunction(string& fileNameOutput, string& rawData)
//{
	//cout << "Please enter the full file path to your text file(.txt). Please use \\ instead of \ for the directory navigation: ";
	//cin >> fileNameInput; // User inputs file name 
	//ifstream fileInput(fileNameInput); //retriev file via user input, ref pg 793 C++SL


	//





//}










