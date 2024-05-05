/*  Group X
    Joseph Laible
    Pedro Ortiz
    Vimal Ramnarain

    Professor Scott Roueche
    CSE  687 Object Oriented Design in C++
    Syracuse University

    --- Project Phase 2 ---
    ----- 04/30/2024 -----
*/

#include <string>

#pragma once

#ifdef REDUCELIBRARY_EXPORTS
#define REDUCELIBRARY_API __declspec(dllexport)
#else
#define REDUCELIBRARY_API __declspec(dllimport)
#endif

class Reduce {
public:
    // Contains main reduce function that processes map phase results
    static void reduce(const std::string& outputDir);
};

extern "C" REDUCELIBRARY_API void reduce(const char* outputDir);
