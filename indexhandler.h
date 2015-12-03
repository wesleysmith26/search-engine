#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "index.h"
#include "avltree.h"
#include "hashtable.h"

using namespace std;

class IndexHandler
{
private:
    Index* avl;
    Index* hash;
    string test = "veda";
    double freq = 0.0;
    ofstream save;
public:
    IndexHandler();
    ~IndexHandler();
    void addWord(map<string, int>& table, int& pg, string& title, string &date, string &user);
    void printSize();

};

#endif // INDEXHANDLER_H

