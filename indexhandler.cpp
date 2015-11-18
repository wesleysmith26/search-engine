#include "indexhandler.h"

IndexHandler::IndexHandler()
{
    avl = new AvlTree();
}

void IndexHandler::addWord(map<string, double>& table, int pg)
{
    int x = pg;
    for(map<string, double>::iterator it = table.begin(); it != table.end(); ++it)
    {
        string word = it->first;
        double freq = it->second;
        avl->insert(word, x, freq);
    }
}
