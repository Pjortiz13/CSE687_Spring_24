/*
libMap.h
Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase II 
05/08/2024

The libMap.h is a header file for libMap to create a DLL to allow extern use of the map_func method.  
*/

#pragma once

#ifdef LIBMAP_EXPORTS
#define LIBMAP_API __declspec(dllexport)
#else
#define LIBMAP_API __declspec(dllimport)
#endif

#include <string>
#include <iostream> 
//provide C linkage to DLL
extern "C" LIBMAP_API void map_func(const char* fileName, const char* data, const char* temp);
