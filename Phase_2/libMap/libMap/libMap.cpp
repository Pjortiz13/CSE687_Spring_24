/*
libMap.cpp
Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase II 
05/08/2024

The libmap.cpp file defines the method map_func which processes text data by tokenizing input strings, 
normalizing them,converting to lowercase and removing punctuation, and recording the 
frequency of each word. It outputs these word counts to a specified temporary directory file, 
supporting the mapping phase of a MapReduce workflow by preparing data for subsequent reduction.
*/



#pragma once
#include "libMap.h"
#include "framework.h"
#include <string>
#include <algorithm> 
#include <fstream> 
#include <iostream> 
#include <sstream> 
#include <cctype> 
#include <vector>
#include <string>
#include <tuple>

// provide DLL linkage and call map_func to: processes the text data, tokenizes it, converts to lowercase, removes punctuation, and exports counts to temp directory with buffering
LIBMAP_API void map_func(const char* fileName, const char* data, const char* temp) {

    std::ofstream out(std::string(temp) + "/map_output.txt", std::ios::app);
    if (!out.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return;
    }

    std::istringstream iss(data);
    std::string word;
    const size_t bufferSize = 10;
    static std::vector<std::tuple<std::string, int>> buffer;

    while (iss >> word) {
        // Convert the word to lowercase
        std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return std::tolower(c); });

        // Remove non-alphabetic characters from the word
        word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) { return std::ispunct(c); }), word.end());

        // Export the word
        std::tuple<std::string, int> wordsTuple(word, 1);
        buffer.push_back(wordsTuple);
        //enduce buffer fto write  to temp output file
        if (buffer.size() >= bufferSize) {
            // write each tuple in the buffer with added syntax
            for (const auto& tuple : buffer) {
                std::string outputString = "(\"" + std::get<0>(tuple) + "\", " + std::to_string(std::get<1>(tuple)) + ") ";
                out << outputString << std::endl;
            }
            // Clear the buffer 
            buffer.clear();
        }
    }
    //close the file
    out.close();
}
