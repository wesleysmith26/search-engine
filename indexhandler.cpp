#include "indexhandler.h"

IndexHandler::IndexHandler()
{
    avl = new AvlTree();
    hash = new HashTable();
}

IndexHandler::~IndexHandler()
{
    delete avl;
    delete hash;
}

void IndexHandler::addWord(map<string, int>& table, int &pg, string &title)
{
    for(map<string, int>::iterator it = table.begin(); it != table.end(); ++it)
    {
        string word = it->first;
        double freq = it->second/table.size();
        //avl->insert(word, pg, freq, title);
        hash->insert(word, pg, freq, title);
    }
}

