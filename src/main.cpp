#include "FileService.hpp"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <filesystem>

const std::string testDataDir {"test_data/"};

void basicTest() {
    //preparation
    const std::string lInputFileName {testDataDir + "basicTest.txt"};
    const std::string lOutputFileName {testDataDir + "basicTestOutput.txt"};
    size_t lInputFileSize = std::filesystem::file_size(lInputFileName);
    FileService lFileService {lInputFileName, lOutputFileName};

    //source
    lFileService.copyLinesBySorting();

    //expectation
    std::cout << "---------------------" << __FUNCTION__ << std::endl;
    assert(std::filesystem::exists(lOutputFileName) && "output file has not been created");

    std::ifstream lInputFile(lInputFileName, std::ios_base::in | std::ios_base::binary);
    std::ifstream lOutputFile(lOutputFileName, std::ios_base::in | std::ios_base::binary | std::ios_base::app);
    size_t lInputFileLineCount = std::count(std::istreambuf_iterator<char>(lInputFile), std::istreambuf_iterator<char>(), '\n');
    size_t lOutputFileLineCount = std::count(std::istreambuf_iterator<char>(lOutputFile), std::istreambuf_iterator<char>(), '\n');
    size_t lOutputFileSize = std::filesystem::file_size(lOutputFileName);

    assert(lInputFileLineCount == lOutputFileLineCount && "input and output files lines are not equal");
    assert(lInputFileLineCount != 0 && "files are empty");
    assert(lInputFileSize == lOutputFileSize && "input and output files size are not equal");
    assert(lInputFileSize != 0 && "files size equal to 0");
    std::cout << "---------------------" << __FUNCTION__ << " passed\n" << std::endl;

    std::filesystem::remove(lOutputFileName);
}

void emptyInputFileTest() {
    //preparation
    const std::string lInputFileName {testDataDir + "emptyFile.txt"};
    const std::string lOutputFileName {testDataDir + "emptyFileOutput.txt"};
    size_t lInputFileSize = std::filesystem::file_size(lInputFileName);
    FileService lFileService {lInputFileName, lOutputFileName};

    //source
    lFileService.copyLinesBySorting();

    //expectation
    std::cout << "---------------------"<< __FUNCTION__ << std::endl;
    assert(std::filesystem::exists(lOutputFileName) && "output file has not been created");

    std::ifstream lInputFile(lInputFileName, std::ios_base::in | std::ios_base::binary);
    std::ifstream lOutputFile(lOutputFileName, std::ios_base::in | std::ios_base::binary | std::ios_base::ate);
    size_t lInputFileLineCount = std::count(std::istreambuf_iterator<char>(lInputFile), std::istreambuf_iterator<char>(), '\n');
    size_t lOutputFileLineCount = std::count(std::istreambuf_iterator<char>(lOutputFile), std::istreambuf_iterator<char>(), '\n');
    size_t lOutputFileSize = std::filesystem::file_size(lOutputFileName);

    assert(lInputFileLineCount == lOutputFileLineCount && "input and output files lines are not equal");
    assert(lInputFileLineCount == 0 && "files are not empty");
    assert(lInputFileSize == lOutputFileSize && "input and output files size are not equal");
    assert(lInputFileSize == 0 && "files are not empty");
    std::cout << "---------------------" << __FUNCTION__ << " passed\n" << std::endl;

    std::filesystem::remove(lOutputFileName);
}


void multipleSequentialCalls() {
    //preparation
    const std::string lInputFileName {testDataDir + "seqCalls.txt"};
    const std::string lOutputFileName {testDataDir + "seqCallsOutput.txt"};
    size_t lInputFileSize = std::filesystem::file_size(lInputFileName);
    FileService lFileService {lInputFileName, lOutputFileName};

    //source
	lFileService.copyLinesBySorting();
	lFileService.copyLinesBySorting();
	lFileService.copyLinesBySorting();
	lFileService.copyLinesBySorting();

	//expectation
	std::cout << "---------------------"<< __FUNCTION__ << std::endl;
	assert(std::filesystem::exists(lOutputFileName) && "output file has not been created");

	std::ifstream lInputFile(lInputFileName, std::ios_base::in | std::ios_base::binary);
	std::ifstream lOutputFile(lOutputFileName, std::ios_base::in | std::ios_base::binary | std::ios_base::app);
	size_t lInputFileLineCount = std::count(std::istreambuf_iterator<char>(lInputFile), std::istreambuf_iterator<char>(), '\n');
	size_t lOutputFileLineCount = std::count(std::istreambuf_iterator<char>(lOutputFile), std::istreambuf_iterator<char>(), '\n');
	size_t lOutputFileSize = std::filesystem::file_size(lOutputFileName);

	assert(lInputFileLineCount == lOutputFileLineCount && "input and output files lines are not equal");
	assert(lInputFileLineCount != 0 && "files are empty");
	assert(lInputFileSize == lOutputFileSize && "input and output files sizes are not equal");
	assert(lInputFileSize != 0 && "files size equal to 0");
	std::cout << "---------------------" << __FUNCTION__ << " passed\n" << std::endl;

	std::filesystem::remove(lOutputFileName);
}

void runTests() {
	multipleSequentialCalls();
	basicTest();
    emptyInputFileTest();
}

int main(int argc, char** argv) {
    if (argc == 2) {
        const std::string command = argv[1];
        if (command == "test") {
            runTests();
        } else {
            std::cout << "Invalid command line option: " << command << std::endl; 
        }
    } else if (argc == 3) {
        const std::string lInputFileName = argv[1];
        const std::string lOutputFileName = argv[2];
        FileService lFileService {lInputFileName, lOutputFileName};
        lFileService.copyLinesBySorting();
    } else {
        std::cout << "Invalid argument provided!!!" << std::endl;
    }

}
