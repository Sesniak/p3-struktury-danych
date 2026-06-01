#pragma once
#include <vector>

class CuckooHash 
{
    std::vector<int> table1, table2;
    int size;

    int hash1(int key);
    int hash2(int key);

public:
    CuckooHash(int s);
    void insert(int key);
    void remove(int key);
};
