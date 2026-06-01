#include "avltable.h"

AVLTable::AVLTable(int s) : size(s), table(s, nullptr) {}

int AVLTable::hash(int key) 
{
    return key % size;
}

void AVLTable::insert(int key, int value) 
{
    int i = hash(key);
    table[i] = tree.insert(table[i], key, value);
}

void AVLTable::remove(int key) 
{
    int i = hash(key);
    table[i] = tree.remove(table[i], key);
}
