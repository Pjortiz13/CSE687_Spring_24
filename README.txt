Project Phase 1 - MapReduce 

The MapReduce project is a standalone command line program written in C++ and developed using Visual Studio.

The project responsibilites were split equally between the team and team members used github to edit, commit, 
and share ideas.

The code includes classes for handling file management 'fileManagement.h/cpp', mapping 'map.h/cpp', reducing 
'reduce.h/cpp', and worlflow 'workflow.h/cpp', which orchestrates the MapReduce process. 

The program processes Shakespeares works in a text file to perform a word count operation, storing intermediate 
and final results in user specfied directories.

HOW TO RUN:
1. Compile the source code using C++ compiler. Use the following command:

g++ -o MapReduceProgram executive.cpp workflow.cpp map.cpp reduce.cpp fileManagement.cpp -std=c++17

2. Generate three folders, first folder with the Shakespeare .txt files named 'testinput', second folder 
labeled 'testoutput', and a third folder named 'testtemp'.

*Note: If a different folder name is preferred, then changes to the map.cpp and reduce.cpp files are needed.

3. Execute the compiled program via the commandline using the format below .\MapReduceProgram "<input directory>" 
"<output directory>" "<temporary directory>".

*Note: Replace <input directory> , <output directory> , and <temporary directory> with the file paths 
to the respective directories.

Example: 
.\MapReduceProgram "D:\school\2024\Spring 2024\Object Oriented Design\map_reduce_main_working_2\testinput" 
"D:\school\2024\Spring 2024\Object Oriented Design\map_reduce_main_working_2\testoutput" 
"D:\school\2024\Spring 2024\Object Oriented Design\map_reduce_main_working_2\testtemp"

4. Once the program has executed sucessfully, the final word count "results" and a SUCCESS file will be generated
within the <output directory>.
