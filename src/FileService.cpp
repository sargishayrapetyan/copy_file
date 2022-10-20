#include "FileService.hpp"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>

FileService::FileService(const std::string& aInputFileName, const std::string& aOutputFileName) 
    : m_InputFileName(aInputFileName)
    , m_OutputFileName(aOutputFileName)
    , m_Ifstream(m_InputFileName, std::ios_base::in | std::ios_base::binary)
    , m_Ofstream(m_OutputFileName, std::ios_base::trunc | std::ios_base::binary)
{
}

void FileService::copyLinesBySorting() {
    openFilesIfNeeded();
    std::string lLine{""};
    while(getline(m_Ifstream, lLine)) {
		sortEachWord(lLine);
    }
    closeFiles();
}

void FileService::copySortedWordsLine() {
    openFilesIfNeeded();
    std::string lLine{""};
    while(getline(m_Ifstream, lLine)) {
		sortWords(lLine);
    }
    closeFiles();
}

void FileService::sortWords(const std::string& aLine) {
	std::stringstream lStrLine(aLine);
	std::string lWord{};
	std::vector<std::string> lWords{};
	while(lStrLine >> lWord) {
		lWords.push_back(lWord);
	}
	std::sort(lWords.begin(), lWords.end());
	std::ostringstream lSorted;
	const char* lDelim = " ";
	std::copy(lWords.begin(), lWords.end(), std::ostream_iterator<std::string>(lSorted, lDelim));
	m_Ofstream << lSorted.str() << '\n';	
}


void FileService::sortEachWord(const std::string& aLine) {
	const char lDelim = ' ';
	std::string lWord{""};
	std::string lWhiteSpace{""};
	for (auto it : aLine) {
		if (it == lDelim) {
			if (!lWord.empty()) {
				std::sort(lWord.begin(), lWord.end());
				m_Ofstream << lWord;
				lWord = "";
			}
			lWhiteSpace += it;
		} else {
			if (!lWhiteSpace.empty()) {
				m_Ofstream << lWhiteSpace;
				lWhiteSpace = "";
			}
			lWord += it;
		}
	}
	if (!lWord.empty()) {
		std::sort(lWord.begin(), lWord.end());
		m_Ofstream << lWord;
	}
	if (!lWhiteSpace.empty()) {
		m_Ofstream << lWhiteSpace;
	}
	m_Ofstream << '\n';
}

void FileService::closeFiles() {
    if (m_Ifstream.is_open()) {
        m_Ifstream.close();
    }
    if (m_Ofstream.is_open()) {
        m_Ofstream.close();
    }
}

void FileService::openFilesIfNeeded() {
    if (!m_Ifstream.is_open()) {
        m_Ifstream.open(m_InputFileName, std::ios_base::in | std::ios_base::binary);
    }
    if (!m_Ofstream.is_open()) {
        m_Ofstream.open(m_OutputFileName, std::ios_base::trunc | std::ios_base::binary);
    }
}

FileService::~FileService() {
    closeFiles();
}
