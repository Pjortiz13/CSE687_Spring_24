#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iterator>
#include <libMap.h>
#include <libReduce.h>
#include <windows.h>
#include <thread>
#include <future>

// Typedef for function pointers to map and reduce functions
typedef void (*funcMap)(const char*, const char*, const char*, int);
typedef void (*funcReduce)(const char*, const char*);

// Function to run a mapper process
void runMapper(const char* mapLibName, const std::string& inputPath, const std::string& tempDir, int numReducers) {
    std::cout << "[DEBUG] Loading map library: " << mapLibName << std::endl;
    HINSTANCE hDLL_map = LoadLibraryA(mapLibName);
    if (hDLL_map == NULL) {
        std::cerr << "[ERROR] Map library load failed!" << std::endl;
        return;
    }

    auto Map = (funcMap)GetProcAddress(hDLL_map, "map_func");
    if (Map == NULL) {
        std::cerr << "[ERROR] Failed to find map() function!" << std::endl;
        FreeLibrary(hDLL_map);
        return;
    }

    std::ifstream inFile(inputPath);
    if (!inFile.is_open()) {
        std::cerr << "[ERROR] Failed to open file: " << inputPath << std::endl;
        FreeLibrary(hDLL_map);
        return;
    }

    std::string line;
    while (getline(inFile, line)) {
        std::cout << "[DEBUG] Processing line: " << line << std::endl;
        Map(inputPath.c_str(), line.c_str(), tempDir.c_str(), numReducers);
    }

    inFile.close();
    FreeLibrary(hDLL_map);
    std::cout << "[DEBUG] Mapper process completed for: " << inputPath << std::endl;
}

// Function to run a reducer process
void runReducer(const char* reduceLibName, const std::string& tempDir, const std::string& outputDir) {
    std::cout << "[DEBUG] Loading reduce library: " << reduceLibName << std::endl;
    HINSTANCE hDLL_reduce = LoadLibraryA(reduceLibName);
    if (hDLL_reduce == NULL) {
        std::cerr << "[ERROR] Reduce library load failed!" << std::endl;
        return;
    }

    auto Reduce = (funcReduce)GetProcAddress(hDLL_reduce, "reduce");
    if (Reduce == NULL) {
        std::cerr << "[ERROR] Failed to find reduce() function!" << std::endl;
        FreeLibrary(hDLL_reduce);
        return;
    }

    std::cout << "[DEBUG] Starting to process temp directory: " << tempDir << std::endl;
    Reduce(tempDir.c_str(), outputDir.c_str());
    FreeLibrary(hDLL_reduce);
    std::cout << "[DEBUG] Reducer process completed for temp directory: " << tempDir << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "[DEBUG] Starting MapReduce process..." << std::endl;

    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <inputDir> <tempDir> <outputDir>" << std::endl;
        return 1;
    }

    std::string inputDir = argv[1];
    std::string tempDir = argv[2];
    std::string outputDir = argv[3];

    const char* mapLibName = "libMap.dll";
    const char* reduceLibName = "libReduce.dll";

    std::cout << "[DEBUG] Input Directory: " << inputDir << std::endl;
    std::cout << "[DEBUG] Temp Directory: " << tempDir << std::endl;
    std::cout << "[DEBUG] Output Directory: " << outputDir << std::endl;

    // Step 1: Run mappers
    std::cout << "[DEBUG] Starting mappers..." << std::endl;
    std::vector<std::future<void>> mapperFutures;
    for (const auto& entry : std::filesystem::directory_iterator(inputDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::string inputPath = entry.path().string();
            mapperFutures.push_back(std::async(std::launch::async, runMapper, mapLibName, inputPath, tempDir, 4));  // Assuming 4 reducers
        }
    }

    // Wait for all mappers to complete
    for (auto& future : mapperFutures) {
        future.get();
    }

    std::cout << "[DEBUG] All mappers completed." << std::endl;

    // Step 2: Run the reducer
    std::cout << "[DEBUG] Starting reducer..." << std::endl;
    runReducer(reduceLibName, tempDir, outputDir);

    std::cout << "[DEBUG] Reducer completed." << std::endl;

    // Create SUCCESS file
    std::ofstream successFile(outputDir + "/SUCCESS");
    if (successFile.is_open()) {
        successFile << "SUCCESS" << std::endl;
        successFile.close();
    }
    else {
        std::cerr << "[ERROR] Failed to create SUCCESS file." << std::endl;
    }

    std::cout << "[DEBUG] Workflow completed!" << std::endl;
    return 0;
}
