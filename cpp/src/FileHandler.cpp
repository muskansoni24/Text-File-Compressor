#include "FileHandler.h"
#include <fstream>
#include <sstream>

std::string FileHandler::readFile(const std::string& filename) {
    std::ifstream inFile(filename);
    std::ostringstream ss;
    ss << inFile.rdbuf();
    return ss.str();
}

void FileHandler::writeFile(const std::string& filename, const std::string& data) {
    std::ofstream outFile(filename);
    outFile << data;
}