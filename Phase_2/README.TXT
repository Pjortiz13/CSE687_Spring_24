Project Phase 2 - MapReduce DLL

This phase uses a client program written in C++ that calls in the Map and Reduce DLLs to carry out the MapReduce functionality.
The code includes two DLLs, one that carries out the Map function and the other that carries out the Reduce function, along with a 
client app that contains the 'fileManagement.h/cpp' and 'workflow.h/cpp'. Similar to Phase 1, the program processes a directory of 
Shakespeare's works in text files, performs a word count operation, and stores the intermediate and final results in user specified directories. 
As per Phase 1, the project responsibilites were split equally between the team and team members used github to edit, commit, and share ideas. 

HOW TO RUN:
1. Download the MapReduce, libMap, and libReduce folders from the GitHub.

2. Enter directory located at ..\..\MapReduce\x64\Debug (NOT ..\..\MapReduce\MapReduce\x64\Debug) and generate three folders. T
he first folder is named 'testinput', which contains the Shakespeare .txt files (this folder may already exist in this project); the second folder is 
labeled 'testoutput', which holds the final output of the program; and a third folder named 'testtemp'.

**NOTE: If a different folder name is wanted, then changes to the source files of the Map and Reduce libraries are necessary.

3. Open the command prompt (preferably as Admin) and navigate to the directory that contains "MapReduce.exe". This can be done by using the command below: 

cd C:\..\..\MapReduce\x64\Debug

**NOTE: C:\..\..\ should be replaced with appropriate file path. 
	For example: C:\SU\Phase_2\MapReduce\x64\Debug 

**NOTE: Use command "dir" to check current directory for MapReduce.exe 
	and also ensure that libMap.dll and libReduce.dll are present.

4. Execute the client program via the command line using the format below:

MapReduce.exe "<input directory>" "<output directory>" "<temporary directory>"

**NOTE: replace <input directory> , <output directory> , and <tempoary directory> with the names of the folders. 
	If using the default names, then use the format below:

MapReduce.exe "testinput" "testoutput" "testtemp"

5. Once the program has executed succesfully, the final word count results will be within the <output directory> as well as a .txt file named "SUCCESS". 
Additionally, a .txt file is generated within the "testtemp" folder that should hold the intermediate output. 

