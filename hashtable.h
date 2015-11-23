#ifndef HASHTABLE
#define HASHTABLE
#include <iostream>
#include <functional>
#include <stdio.h>
#include <string>
#include "linkedlist.h"
#include "avltree.h"

using namespace std;

class HashTable
{
private:
    class HashNode
    {
    private:

    public:
        AvlTree* avl;
        HashNode()
        {
            avl = new AvlTree;
        }
        ~HashNode()
        {
            delete avl;
        }
    };
    HashNode** bucket;
    int tableSize;
    int hashValue;
    int size;
    int load;
    AvlTree* error;

public:
    HashTable()
    {
        tableSize = 7919;
        hashValue = 0;
        size = 0;
        error = new AvlTree();
        bucket = new HashNode*[tableSize];
        for(int i = 0; i < tableSize; i++)
            bucket[i] = nullptr;
    }
    ~HashTable()
    {
        for(int i = 0; i < tableSize; i++)
            delete bucket[i];
        delete[] bucket;
    }

    void clear()
    {
        for(int i = 0; i < tableSize; i++)
        {
            delete bucket[i];
            bucket[i] = nullptr;
        }
    }

    void insert(string& keyword, int& pageNumber, double& freq, string& header)
    {
        setHashValue(keyword);
        if(bucket[hashValue] == nullptr)
        {
            bucket[hashValue] = new HashNode();
            load++;
        }
        bucket[hashValue]->avl->insert(keyword, pageNumber, freq, header);
    }

    void setHashValue(string& keyword)
    {
        hash<string> strHash;
        int value = strHash(keyword);
        value = abs(value);
        hashValue = value % tableSize;
    }

    int& getSize()
    {
        for(int i = 0; i < tableSize; i++)
        {
            if(bucket[i] != nullptr)
                size += bucket[i]->avl->getSize();
        }
        return size;
    }
    string& findKeyword(string& keyword)
    {
        setHashValue(keyword);
        if(bucket[hashValue] == nullptr)
            return error->findKeyword(keyword);
        else
            return bucket[hashValue]->avl->findKeyword(keyword);
    }

    LinkedList<int>*& findPageNumber(string& keyword)
    {
        setHashValue(keyword);
        if(bucket[hashValue] == nullptr)
            return error->findPageNumber(keyword);
        else
            return bucket[hashValue]->avl->findPageNumber(keyword);
    }

    LinkedList<double>*& findFrequency(string& keyword)
    {
        setHashValue(keyword);
        if(bucket[hashValue] == nullptr)
            return error->findFrequency(keyword);
        else
            return bucket[hashValue]->avl->findFrequency(keyword);
    }

    LinkedList<string>*& findTitle(string& keyword)
    {
        setHashValue(keyword);
        if(bucket[hashValue] == nullptr)
            return error->findTitle(keyword);
        else
            return bucket[hashValue]->avl->findTitle(keyword);
    }

};
#endif // HASHTABLE

