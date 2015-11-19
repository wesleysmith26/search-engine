#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include <iostream>
#include <map>
#include "avltree.h"

using namespace std;

class IndexHandler
{
private:
    AvlTree* avl;
public:
    IndexHandler();
    void addWord(map<string, int>& table, int& pg, string& title);

};

#endif // INDEXHANDLER_H
