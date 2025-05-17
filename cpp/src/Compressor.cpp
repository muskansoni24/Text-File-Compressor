#include "Compressor.h"
#include "FileHandler.h"
#include "HuffmanTree.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <iostream>
#include <filesystem>
#include <vector>
#include <cstdint>

Compressor::Compressor() {}

void Compressor::compress(const std::string& inputFile, const std::string& outputFile) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    FileHandler fh;
    std::string content = fh.readFile(inputFile);

    HuffmanTree tree;
    auto freqMap = tree.buildFrequencyMap(content);
    tree.buildTreeFromFrequencyMap(freqMap);
    std::string encoded = tree.encode(content);  // binary string (e.g., "1010110...")

    // Step 1: Pack bits into bytes
    std::vector<uint8_t> packedBits;
    uint8_t currentByte = 0;
    int bitCount = 0;

    for (char bit : encoded) {
        currentByte <<= 1;
        if (bit == '1') currentByte |= 1;
        bitCount++;

        if (bitCount == 8) {
            packedBits.push_back(currentByte);
            currentByte = 0;
            bitCount = 0;
        }
    }

    if (bitCount > 0) {
        currentByte <<= (8 - bitCount);  // pad the last byte
        packedBits.push_back(currentByte);
    }

    // Step 2: Write to output file in binary mode
    std::ofstream out(outputFile, std::ios::binary);

    // 2.1 - Write frequency map size
    int mapSize = freqMap.size();
    out.write(reinterpret_cast<const char*>(&mapSize), sizeof(mapSize));

    // 2.2 - Write frequency map (char + frequency)
    for (const auto& [ch, freq] : freqMap) {
        uint8_t c = static_cast<uint8_t>(ch);
        out.write(reinterpret_cast<const char*>(&c), sizeof(c));
        out.write(reinterpret_cast<const char*>(&freq), sizeof(freq));
    }

    // 2.3 - Write the number of encoded bits
    int encodedBitLength = encoded.size();  // needed for proper decoding
    out.write(reinterpret_cast<const char*>(&encodedBitLength), sizeof(encodedBitLength));

    // 2.4 - Write the packed encoded data
    out.write(reinterpret_cast<const char*>(packedBits.data()), packedBits.size());

    out.close();

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    std::uintmax_t originalSize = std::filesystem::file_size(inputFile);
    std::uintmax_t compressedSize = std::filesystem::file_size(outputFile);

    double compressionRatio = 100.0 * (1.0 - (double)compressedSize / originalSize);

    std::cout << "Original File Size: " << originalSize << " bytes\n";
    std::cout << "Compressed File Size: " << compressedSize << " bytes\n";
    std::cout << "Compression Ratio: " << compressionRatio << "%\n";
    std::cout << "Time taken to compress: " << duration.count() / 1e6 << " seconds\n";
}

// #include "Compressor.h"
// #include "FileHandler.h"
// #include "HuffmanTree.h"
// #include <fstream>
// #include <sstream>
// #include <chrono>
// #include <iostream>
// #include <filesystem>

// Compressor::Compressor() {}

// void Compressor::compress(const std::string& inputFile, const std::string& outputFile) {
//     using namespace std::chrono;
//     auto start = high_resolution_clock::now();

//     FileHandler fh;
//     std::string content = fh.readFile(inputFile);

//     HuffmanTree tree;
//     auto freqMap = tree.buildFrequencyMap(content);
//     tree.buildTreeFromFrequencyMap(freqMap);
//     std::string encoded = tree.encode(content);

//     std::ostringstream oss;
//     oss << freqMap.size() << "\n";
//     for (auto it = freqMap.begin(); it != freqMap.end(); ++it) {
//         char ch = it->first;
//         int freq = it->second;
//         oss << (int)ch << " " << freq << "\n";
//     }
//     oss << encoded;

//     fh.writeFile(outputFile, oss.str());

//     auto end = high_resolution_clock::now();
//     auto duration = duration_cast<microseconds>(end - start);

//     std::uintmax_t originalSize = std::filesystem::file_size(inputFile);
//     std::uintmax_t compressedSize = std::filesystem::file_size(outputFile);

//     double compressionRatio = 100.0 * (1.0 - (double)compressedSize / originalSize);

//     std::cout << "Original File Size: " << originalSize << " bytes\n";
//     std::cout << "Compressed File Size: " << compressedSize << " bytes\n";
//     std::cout << "Compression Ratio: " << compressionRatio << "%\n";
//     std::cout << "Time taken to compress: " << duration.count() / 1e6 << " seconds\n";
// }


// void Compressor::compress(const std::string& inputFile, const std::string& outputFile) {
//     FileHandler fh;
//     std::string content = fh.readFile(inputFile);

//     HuffmanTree tree;
//     auto freqMap = tree.buildFrequencyMap(content);
//     tree.buildTreeFromFrequencyMap(freqMap);

//     std::string encoded = tree.encode(content);

//     std::ostringstream oss;
//     oss << freqMap.size() << "\n";
//     for (auto it = freqMap.begin(); it != freqMap.end(); ++it) {
//     char ch = it->first;
//     int freq = it->second;
//     oss << (int)ch << " " << freq << "\n";
// }
//     oss << encoded;

//     fh.writeFile(outputFile, oss.str());
// }