#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include <iostream>
#include <string>
#include <map>
#include "avltree.h"
#include "hashtable.h"

using namespace std;

class IndexHandler
{
private:
    AvlTree* avl;
    HashTable* hash;
    string test = "veda";
    double freq = 0.0;
public:
    IndexHandler();
    ~IndexHandler();
    void addWord(map<string, int>& table, int& pg, string& title);
    void printSize();

};

#endif // INDEXHANDLER_H

