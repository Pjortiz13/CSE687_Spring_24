/*
libReduce.h
Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase II 
05/08/2024

This is the header file for the  Reduce method: for function definitions and DLL C linkage

*/ 

#pragma once

#include <string>

#ifdef LIBREDUCE_EXPORTS
#define LIBREDUCE_API __declspec(dllexport)
#else
#define LIBREDUCE_API __declspec(dllimport)
#endif
//Provide DLL C linkage 
extern "C" LIBREDUCE_API void reduce(const char* outputDir);
