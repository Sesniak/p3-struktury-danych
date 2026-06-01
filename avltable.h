#pragma once
#include <vector>
#include "avltree.h"

class AVLTable {
    std::vector<AVLNode*> table;
    int size;
    AVLTree tree;

    int hash(int key);

public:
    AVLTable(int s);
    void insert(int key, int value);
    void remove(int key);
};
