/**
 * @file FileService.hpp
 * @author Sargis Hayrapetyan
 * @date 10-10-2022
 * @brief The class is responsible for reading file line by line and writing to another file 
 *
 */

#pragma once

#include <string>
#include <fstream>

class FileService {
    
    public:
        FileService(const std::string& aInputFileName, const std::string& aOutputFileName);

    public:
        // default constructor
        FileService() = delete;
        
        // copy/move constructors
        FileService(const FileService&) = delete;
        FileService(FileService&&) = delete;

        // assignment/move operator
        FileService& operator=(const FileService&) = delete;
        FileService& operator=(FileService&&) = delete;

    public:
        //getters
        std::string getInputFileName() const;
        std::string getOutputFileName() const;
        
        void copyLinesBySorting();
		void copySortedWordsLine();

    public:
        virtual ~FileService();

    private:
        void closeFiles();
        void openFilesIfNeeded();
		void sortEachWord(const std::string& aLine);
		void sortWords(const std::string& aLine);

    private:
        std::string m_InputFileName;
        std::string m_OutputFileName;
        std::ifstream m_Ifstream;
        std::ofstream m_Ofstream;
};
