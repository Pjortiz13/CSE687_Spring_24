Project Phase 1 - MapReduce 

The MapReduce project is a standalone command line program written in C++ and developed using visual studios.
The project responsibilites were split equally between the team and team members used github to edit, 
commit, and share ideas.
The code includes classes for handling file management 'fileManagement.h/cpp', 
mapping 'map.h/cpp', reducing 'reduce.h/cpp', and
to orchestate the mapreduce worlflow 'workflow.h/cpp'. The program processes shakesspearts in a text file 
to perform a word count opeartion, storing intermediate and final results in user specfied directories.

HOW TO RUN:
1. Compile the soruce code using C++ compiler

g++ -o MapReduceProgram executive.cpp workflow.cpp map.cpp reduce.cpp fileManagement.cpp -std=c++17

2. generate three folders, first folder with the shakespear .txt files named 'testinput', second folder labeled 'testoutput'
and a third folder named 'testtemp'

**note if a different folder name is wanted changes to the map.cpp and reduce.cpp files are needed

3. Execute the compiuled program via the commandline using the format below
.\MapReduceProgram "<input directory>" "<output directory>" "<temporary directory>"

replace <input directory> , <output directory> , and <tempoary directory> with the file paths 
to the resptevice directories

example: 

.\MapReduceProgram "D:\school\2024\Spring 2024\Object Oriented Design\map_reduce_main_working_2\testinput" "D:\school\2024\Spring 2024\Object Oriented Design\map_reduce_main_working_2\testoutput" "D:\school\2024\Spring 2024\Object Oriented Design\map_reduce_main_working_2\testtemp"

4. once the program has executed sucesffuly within the <output director> the final word count results and a sucess file
will be generated. along with a .txt file within the testtemp folder that should hold the intermediate output. 
