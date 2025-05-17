#include "HuffmanNode.h"

HuffmanNode::HuffmanNode(char ch, int freq, HuffmanNode* l, HuffmanNode* r)
    : ch(ch), frequency(freq), left(l), right(r) {}

char HuffmanNode::getChar() const { return ch; }
int HuffmanNode::getFrequency() const { return frequency; }
HuffmanNode* HuffmanNode::getLeft() const { return left; }
HuffmanNode* HuffmanNode::getRight() const { return right; }
bool HuffmanNode::hasLeft() const { return left != nullptr; }
bool HuffmanNode::hasRight() const { return right != nullptr; }

bool Compare::operator()(HuffmanNode* l, HuffmanNode* r) {
    return l->getFrequency() > r->getFrequency();
}
