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
    void addWord(map<string, double>& table, int pg);

};

#endif // INDEXHANDLER_H
