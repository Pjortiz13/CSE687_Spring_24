#pragma once
#include "libReduce.h"
#include "framework.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

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
