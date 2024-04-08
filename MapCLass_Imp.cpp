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
#include "MapClass.h"
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
void MapClass::MapFunction(string& fileNameInput, string& rawData)
{
		cout << "Please enter the full file path to your text file(.txt). Please use \\ instead of \ for the directory navigation: ";
		cin >> fileNameInput; // User inputs file name 
		ifstream fileInput(fileNameInput); //retriev/open file via user input, ref pg 793 C++SL
		cout << " Processing Raw Data from file (removing puncuations,captalization, and adding, word + , 1\n";


		//begin to tokenize the raw data

		//getline used to read line by line function reads all characters until the end of file is reached. while loop to go through each line
		while (getline(fileInput, rawData)) { //getline pgs 677,713,769
			stringstream ssLines(rawData); //make and object for each line of the file

			//get words via stringstream for each line
			string words;
			while (ssLines >> words) {
				
				//get total word count
				wordsCounted++;
				//remove white space *working
				
				//remove puncuations *working
				
				//remove capitalizations *working
				//replace words with words + ,1 *working

				cout << words << " "; //allow user to see new set of words

			}
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










