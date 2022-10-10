#include "FileService.hpp"

#include <iostream>
#include <algorithm>

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
        std::sort(lLine.begin(), lLine.end());
        m_Ofstream << lLine << '\n';
    }
    closeFiles();
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
