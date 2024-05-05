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

        if (buffer.size() >= bufferSize) {
            for (const auto& tuple : buffer) {
                std::string outputString = "(\"" + std::get<0>(tuple) + "\", " + std::to_string(std::get<1>(tuple)) + ") ";
                out << outputString << std::endl;
            }
            buffer.clear();
        }
    }
    out.close();
}