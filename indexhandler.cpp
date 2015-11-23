#include "indexhandler.h"
#include <iostream>

using namespace std;

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
        freq = (double)it->second/(double)table.size();
        avl->insert(word, pg, freq, title);
        //hash->insert(word, pg, freq, title);
    }
}

void IndexHandler::printSize()
{
    cout<<avl->getSize()<<endl;
    cout<<avl->findKeyword(test)<<endl;
    avl->findPageNumber(test)->output();
    avl->findFrequency(test)->output();
    avl->findTitle(test)->output();

}

