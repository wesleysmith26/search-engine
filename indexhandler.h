#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include <iostream>
#include <vector>
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
    Index* avlSearch;
    Index* hashSearch;
    string test = "veda";
    double freq = 0.0;
    ofstream save;
public:
    IndexHandler();
    ~IndexHandler();
    void addWord(map<string, int>& table, int& pg, string& title, string &date, string &user);
    Index*& searchAvl(vector<string>& searchWords);
    Index*& searchHash(vector<string>& searchWords);
    void clear();
    void printSize();

};

#endif // INDEXHANDLER_H

