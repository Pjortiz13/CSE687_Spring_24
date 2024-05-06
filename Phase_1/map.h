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

#pragma once 
//added for use of string 
#include <string> 
//io stream lib
#include <iostream> 


class MapClass {
public:
	//consturctor that intiailizes the class with a directory for temp storage
	MapClass(const std::string& tempDir);


	// starts map process and setting up resoruces
	void start();

	//MapFunction processes a single data string from aa specified file, perofmring map operation
	//(string& fileNameInput, string& rawData);
	void MapFunction(const std::string& fileName, const std::string& data); 

	// ends map function 
	void end();

	//outputs the mapped data, word and count, to a temp storage file 
	void ExportFunction(const std::string& word, int count); 


private:
	// stores the path to the temp directory where interm. results will be stored 
	std::string tempDir;

};


