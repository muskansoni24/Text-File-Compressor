#include "HuffmanTree.h"
#include <queue>

HuffmanTree::HuffmanTree() : root(nullptr) {}

void HuffmanTree::buildTree(const std::string& content) {
    auto frequencyMap = buildFrequencyMap(content);
    buildTreeFromFrequencyMap(frequencyMap);
}

std::map<char, int> HuffmanTree::buildFrequencyMap(const std::string& data) {
    std::map<char, int> freqMap;
    for (char ch : data) {
        freqMap[ch]++;
    }
    return freqMap;
}

void HuffmanTree::buildTreeFromFrequencyMap(const std::map<char, int>& freqMap) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> pq;

    for (const auto& [ch, freq] : freqMap) {
        pq.push(new HuffmanNode(ch, freq));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        pq.push(new HuffmanNode('\0', left->getFrequency() + right->getFrequency(), left, right));
    }

    root = pq.top();
    buildHuffmanCodes(root, "");
}

void HuffmanTree::buildHuffmanCodes(HuffmanNode* node, const std::string& code) {
    if (!node) return;
    if (!node->hasLeft() && !node->hasRight()) {
        huffmanCodes[node->getChar()] = code;
    }
    buildHuffmanCodes(node->getLeft(), code + "0");
    buildHuffmanCodes(node->getRight(), code + "1");
}

std::string HuffmanTree::encode(const std::string& content) {
    std::string encoded;
    for (char c : content) {
        encoded += huffmanCodes[c];
    }
    return encoded;
}

std::string HuffmanTree::decode(const std::string& encodedData) {
    std::string decoded;
    HuffmanNode* current = root;
    for (char bit : encodedData) {
        current = (bit == '0') ? current->getLeft() : current->getRight();
        if (!current->hasLeft() && !current->hasRight()) {
            decoded += current->getChar();
            current = root;
        }
    }
    return decoded;
}