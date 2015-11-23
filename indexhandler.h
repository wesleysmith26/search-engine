#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include <iostream>
#include <map>
#include "avltree.h"
#include "hashtable.h"

using namespace std;

class IndexHandler
{
private:
    AvlTree* avl;
    HashTable* hash;
public:
    IndexHandler();
    ~IndexHandler();
    void addWord(map<string, int>& table, int& pg, string& title);

};

#endif // INDEXHANDLER_H

