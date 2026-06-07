#include "cuckoo.h"
#include <iostream>
using namespace std;

CuckooHash::CuckooHash(int s) : size(s), table1(s, -1), table2(s, -1) {}

int CuckooHash::hash1(int key) 
{ 
    return key % size; 
}
int CuckooHash::hash2(int key) 
{ 
    int scrambled = key ^ (key >> 7);
    return (scrambled * 31) % size;
}

void CuckooHash::insert(int key) 
{
    int pos1 = hash1(key);
    int pos2 = hash2(key);

    if(table1[pos1] == key || table2[pos2] == key)
    {
        return;
    }

    if (table1[pos1] == -1) 
    {
        table1[pos1] = key;
        return;
    }

    int displaced = table1[pos1];
    table1[pos1] = key;

    for (int i = 0; i < size; i++) 
    {
        int pos2 = hash2(displaced);

        if (table2[pos2] == -1) 
        {
            table2[pos2] = displaced;
            return;
        }

        swap(displaced, table2[pos2]);

        pos1 = hash1(displaced);
        if (table1[pos1] == -1) 
        {
            table1[pos1] = displaced;
            return;
        }

        swap(displaced, table1[pos1]);
    }
}

void CuckooHash::remove(int key) 
{
    int pos1 = hash1(key);
    if (table1[pos1] == key) 
    { 
        table1[pos1] = -1; 
        return; 
    }

    int pos2 = hash2(key);
    if (table2[pos2] == key) 
    { 
        table2[pos2] = -1; 
        return; 
    }
}
