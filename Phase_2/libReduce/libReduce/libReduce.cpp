/*
libReduce.cpp
Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase II 
05/08/2024

This file is for the Reduce method 
that take will read and process word-count pairs from the input file (temp directory, file exported from map_func) 
and write these word pairs with thier aggrigated counts to the outputdirectory
*/ 


#pragma once
#include "libReduce.h"
#include "framework.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

//provide DLL linkage and call reduce method 
//method will establish file paths, open input/output files, will read "word"s and aggregate count and
// write output to outputfile in output directory. 
LIBREDUCE_API void reduce(const char* outputDir) {
	std::string outputDirString(outputDir);
	std::string inputFile = outputDirString + "/../testtemp/map_output.txt";
	std::string outputFile = outputDirString + "/results.txt";
	std::ifstream inFile(inputFile);
	std::ofstream outFile(outputFile);

	if (!inFile.is_open() || !outFile.is_open()) {
		std::cerr << "Failed to open files." << std::endl;
		return;
	}

	std::map<std::string, int> wordCounts;
	std::string line;

	while (getline(inFile, line)) {
		std::istringstream iss(line);
		std::string word;
		int count;

		while (iss >> word >> count) {
			wordCounts[word] += count;
		}
	}
	
	for (const auto& pair : wordCounts) {
		outFile << pair.first << " " << pair.second << ")" << std::endl;
	}

	inFile.close();
	outFile.close();
}
