/*Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase I 
04/22/2024

This is the header ".h" file  for class Map
This class contains the public method map that accepts a key and value
This function will tokenize the value into distinc t words (remove everything but the word, no puncation) 
This function will also make a second function called export()
*/
// #ifndef MAP_H - pragma once can be used in its place so the code looks clearner does the same operation 
// #define MAP_H - pragma once can be used in its place so the code looks clearner does the same operation 

#pragma once /* added in in replacement of #ifndef #define and #endif */
#include <string> 
// #include <map> // removed since it is not necessary with the final vision 
// #include <fstream> //file stream lib,ref pg 791 C++ SL, Josuttis used to acess files 
#include <iostream> //io stream lib
// #include <cstdlib> // removed not necessary for final vision
// #include <sstream>//stringstream lib // removed not necessary for final vision
// using std::ostream; // removed to avoid using directive in header files
// using std::string; // removed to avoid using directive in header files
// using std::ifstream; // removed to avoid using directive in header files


class MapClass {
public:
	//consturctor that intiailizes the class with a directory for temp storage
	MapClass(const std::string& tempDir);

	//string fileNameInput; // file handling handled by fileManagement
	//string fileNameOutput; // file handling handled by fileManagement
	//string rawData; // file handling handled by fileManagement
	//string outputData; // file handling handled by fileManagement
	//double wordsCounted; // file handling handled by fileManagement
	//string words; // file handling handled by fileManagement

	// initialization constructor
	//MapClass(); removed since the class requires specific intitializtion parms

	// destructor
	//~MapClass(); // uncessary as thje class does not manage resources needing cleanup 
	// starts map process and setting up resoruces
	void start();

	//MapFunction processes a single data string from aa specified file, perofmring map operation
	void MapFunction(const std::string& fileName, const std::string& data); //(string& fileNameInput, string& rawData);
	// ends map function 
	void end();

	//outputs the mapped data, word and count, to a temp storage file 
	void ExportFunction(const std::string& word, int count); //(string& key, int value);

	//Vitrtual function get file name to be used with every class and derivative 

private:
	// stores the path to the temp directory where interm. results will be stored 
	std::string tempDir;

};
// #endif - pragma once can be used in its place so the code looks clearner does the same operation 
