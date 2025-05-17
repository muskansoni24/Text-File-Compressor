#include "Decompressor.h"
#include "FileHandler.h"
#include "HuffmanTree.h"
#include <fstream>
#include <map>
#include <vector>
#include <cstdint>

Decompressor::Decompressor() {}

void Decompressor::decompress(const std::string& inputFile, const std::string& outputFile) {
    // Open binary input file
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Unable to open input file: " + inputFile);
    }

    // Step 1: Read frequency map size
    int mapSize;
    in.read(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));

    // Step 2: Read frequency map
    std::map<char, int> freqMap;
    for (int i = 0; i < mapSize; ++i) {
        uint8_t ch;
        int freq;
        in.read(reinterpret_cast<char*>(&ch), sizeof(ch));
        in.read(reinterpret_cast<char*>(&freq), sizeof(freq));
        freqMap[(char)ch] = freq;
    }

    // Step 3: Read total encoded bit length
    int bitLength;
    in.read(reinterpret_cast<char*>(&bitLength), sizeof(bitLength));

    // Step 4: Read packed encoded data
    std::vector<uint8_t> packedData((std::istreambuf_iterator<char>(in)),
                                    std::istreambuf_iterator<char>());
    in.close();

    // Step 5: Unpack bits into a binary string
    std::string encodedBits;
    encodedBits.reserve(bitLength);

    for (uint8_t byte : packedData) {
        for (int i = 7; i >= 0 && encodedBits.size() < bitLength; --i) {
            encodedBits.push_back(((byte >> i) & 1) ? '1' : '0');
        }
    }

    // Step 6: Decode using Huffman Tree
    HuffmanTree tree;
    tree.buildTreeFromFrequencyMap(freqMap);
    std::string decoded = tree.decode(encodedBits);

    // Step 7: Write decoded output
    FileHandler fh;
    fh.writeFile(outputFile, decoded);
}

// #include "Decompressor.h"
// #include "FileHandler.h"
// #include "HuffmanTree.h"
// #include <sstream>

// Decompressor::Decompressor() {}

// void Decompressor::decompress(const std::string& inputFile, const std::string& outputFile) {
//     FileHandler fh;
//     std::string data = fh.readFile(inputFile);
//     std::istringstream iss(data);

//     int mapSize;
//     iss >> mapSize;
//     iss.ignore();

//     std::map<char, int> freqMap;
//     for (int i = 0; i < mapSize; ++i) {
//         int ch, freq;
//         iss >> ch >> freq;
//         freqMap[(char)ch] = freq;
//     }
//     iss.ignore();

//     std::string encoded;
//     std::getline(iss, encoded, '\0');

//     HuffmanTree tree;
//     tree.buildTreeFromFrequencyMap(freqMap);
//     std::string decoded = tree.decode(encoded);
//     fh.writeFile(outputFile, decoded);
// }
