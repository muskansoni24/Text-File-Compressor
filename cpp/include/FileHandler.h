#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

class FileHandler {
public:
    std::string readFile(const std::string& filename);
    void writeFile(const std::string& filename, const std::string& data);
};

#endif