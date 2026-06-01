#pragma once
#include <algorithm>

struct AVLNode
{
    int key, value, height;
    AVLNode *left, *right;

    AVLNode(int k, int v) : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree
{
public:
    AVLNode* insert(AVLNode* node, int key, int value);
    AVLNode* remove(AVLNode* node, int key);
private:
    int height(AVLNode* n);
    int balance(AVLNode* n);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* findMin(AVLNode* node);
};
