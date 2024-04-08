//Group X Joseph I Laible
// Professor Scott Roueche
// CSE  687 Object Oriented Design in C++
// Syracuse University 
//Project Phase I 
//04/07/2024
// This is the  driver file  for class Map







#include "MapClass.h"
#include <string>
#include <map>
#include <fstream> //file stream lib
#include <iostream> //io stream lib
#include <cstdlib>
#include <sstream>//stringstream lib
//declare public variables 
string fileNameInput;
string fileNameOutput;
string rawData;
string outputData;
string file;
double wordsCounted;
string wordsNew;
using std::cout;
using std::cin;





int userDriver;
int main() {
string rawData = "";
// welcome heading for user:  show what the program is and prompt user input 

	cout << "################################################################\n     Group X Utilizing Map Reduce on  Shakespeare's Works   \n################################################################";
	cout << "\n This Program will take an input file (.txt) of one of Shakespeare's Works and replace each word with: word, 1 ";
	cout << "\n################################################################";
	cout << "\n\n Please enter 1 to begin: ";
	cin >> userDriver;


	if (userDriver == 1) {

		
		MapClass ObjX;//make object to test imp file
		ObjX.MapFunction(fileNameInput, rawData);





	}

	cin >> userDriver;

}

