//Group X Joseph I Laible
// Professor Scott Roueche
// CSE  687 Object Oriented Design in C++
// Syracuse University 
//Project Phase I 
//04/07/2024
// This is the header ".h" file  for class Map
// This class contains the public method map that accepts a key and value
// This function will tokenize the value into distinc t words (remove everything but the word, no puncation) 
//This function will also make a second function called export()

#ifndef MAP_H
#define MAP_H

#include <string>
#include <map>
#include <fstream> //file stream lib,ref pg 791 C++ SL, Josuttis used to acess files 
#include <iostream> //io stream lib
#include <cstdlib>
#include <sstream>//stringstream lib
using std::ostream;
using std::string;
using std::ifstream;


class MapClass
{
public:
	//declare public variables 
	string fileNameInput;
	string fileNameOutput;
	string rawData;
	string outputData;
	double wordsCounted;
	string words;



	// initialization constructor
	MapClass();


	// destructor
	~MapClass();

	//map function
	void MapFunction(string& fileNameInput, string& rawData);
	//export function
	void ExportFunction(string& key, int value);

	//Vitrtual function get file name to be used with every class and derivative 





private:

	std::map<string, string> MappedData ;

};

#endif

