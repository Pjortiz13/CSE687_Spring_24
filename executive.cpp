/*
executive.cpp
Group X
Joseph Laible
Pedro Ortiz
Vimal Ramnarain 
Professor Scott Roueche
CSE  687 Object Oriented Design in C++
Syracuse University 

Project Phase I 
04/22/2024

summary: driver file for the Map class in the mapreduce project
*/
//orchestrates the MapReduce process
#include "workFlow.h"
//#include "map.h"
//#include <string>
//#include <map>
//#include <fstream> //file stream lib

// in/out operations and for exception handling messages and status
#include <iostream> //io stream lib

//#include <cstdlib>
//#include <sstream>//stringstream lib
//declare public variables 
//string fileNameInput;
//string fileNameOutput;
//string rawData;
//string outputData;
//string file;
//double wordsCounted;
//string wordsNew;
//using std::cout;
//using std::cin;

// main function checks command line arguments and runs the workflow
int main(int argc, char* argv[]) {
    // check if the correct number of arguments is passed
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <inputDir> <outputDir> <tempDir>" << std::endl;
        return 1;
    }
    // retrieve directory paths from command-line arguments
    std::string inputDir = argv[1];
    std::string outputDir = argv[2];
    std::string tempDir = argv[3];
    // create a Workflow object configured with the specified directories
    Workflow workflow(inputDir, outputDir, tempDir);
    // execute the workflow and check for success
    if (!workflow.execute()) {
        std::cerr << "Failed to execute the workflow." << std::endl;
        return 1;
    }

    std::cout << "Workflow completed successfully." << std::endl;
    return 0;
}

/*//string rawData = "";
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

*/
