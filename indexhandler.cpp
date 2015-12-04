#include "indexhandler.h"
#include <iostream>

using namespace std;

IndexHandler::IndexHandler()
{
    avl = new AvlTree();
    avlSearch = new AvlTree();
    hash = new HashTable();
    hashSearch = new HashTable();
    save.open("save.txt");
}

IndexHandler::~IndexHandler()
{
    delete avl;
    delete hash;
}

void IndexHandler::addWord(map<string, int>& table, int &pg, string &title, string& date, string& user)
{
    for(map<string, int>::iterator it = table.begin(); it != table.end(); ++it)
    {
        string word = it->first;
        freq = (double)it->second/(double)table.size();
        avl->insert(word, pg, freq, title, date, user);
        //hash->insert(word, pg, freq, title);
    }
}

Index*& IndexHandler::searchAvl(vector<string> &searchWords)
{
    string temp;
    string error = "error";
    LinkedList* ll;
    for(vector<string>::iterator it = searchWords.begin(); it != searchWords.end(); it++)
    {
        temp = avl->findKeyword(*it);
        if(temp != error)
        {
            temp = *it;
            ll = avl->findData(temp);
            avlSearch->insertLL(temp, ll);
        }
    }

    return avlSearch;
}

Index*& IndexHandler::searchHash(vector<string> &searchWords)
{
    string temp;
    string error = "error";
    LinkedList* ll;
    for(vector<string>::iterator it = searchWords.begin(); it != searchWords.end(); it++)
    {
        temp = avl->findKeyword(*it);
        if(temp != error)
        {
            temp = *it;
            ll = hash->findData(temp);
            hashSearch->insertLL(temp, ll);
        }
    }
    return hashSearch;
}

void IndexHandler::clear()
{
    avl->clear();
    hash->clear();
}

void IndexHandler::printSize()
{
    LinkedList* ll;
    save.close();
    cout<<avl->getSize()<<endl;
    cout<<avl->findKeyword(test)<<endl;
    ll = avl->findData(test);
    ll->sort();
    ll->output();

}

