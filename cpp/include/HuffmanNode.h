#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

class HuffmanNode {
private:
    char ch;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

public:
    HuffmanNode(char ch, int freq, HuffmanNode* left = nullptr, HuffmanNode* right = nullptr);
    char getChar() const;
    int getFrequency() const;
    HuffmanNode* getLeft() const;
    HuffmanNode* getRight() const;
    bool hasLeft() const;
    bool hasRight() const;
};

struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r);
};

#endif