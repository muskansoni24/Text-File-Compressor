#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <string>
#include <map>
#include "HuffmanNode.h"

class HuffmanTree {
private:
    HuffmanNode* root;
    std::map<char, std::string> huffmanCodes;

    void buildHuffmanCodes(HuffmanNode* node, const std::string& code);

public:
    HuffmanTree();
    void buildTree(const std::string& content);
    std::string encode(const std::string& content);
    std::string decode(const std::string& encodedData);
    std::map<char, int> buildFrequencyMap(const std::string& data);
    void buildTreeFromFrequencyMap(const std::map<char, int>& freqMap);
};

#endif