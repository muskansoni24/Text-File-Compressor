#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <string>

class Compressor {
public:
    Compressor();
    void compress(const std::string& inputFile, const std::string& outputFile);
};

#endif