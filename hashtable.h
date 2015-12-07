// Owner: Zach
// File History:
// https://github.com/SMUCSE2341/BSSearch/commits/DocumentParser/hashtable.h
#ifndef HASHTABLE
#define HASHTABLE
#include <iostream>
#include <functional>
#include <stdio.h>
#include <string>
#include <map>
#include "linkedlist.h"
#include "avltree.h"

using namespace std;

/*!
 * \class HashTable an Index subclass
 * \brief contains contain a word, page number, page title,
 * page date, and page contributor's username for each page.
 */
class HashTable:public Index
{
private:
    /*!
     * \class HashNode a node that contains an AVL Tree.
     */
    class HashNode
    {
    private:

    public:
        /*!
         * \var avl an AvlTree pointer.
         */
        AvlTree* avl;

        /*!
         * \brief HashNode default constructor
         */
        HashNode()
        {
            avl = new AvlTree;
        }

        /*!
         * \brief HashNode destructor
         */
        ~HashNode()
        {
            delete avl;
        }
    };

    /*!
     * \var bucket is a pointer to a HashNode pointer.
     */
    HashNode** bucket;

    /*!
     * \var tableSize an integer that contains the amount of buckets in the hash
     * table.
     */
    int tableSize;

    /*!
     * \var hashValue an integer that contains the hash value of a word.
     */
    int hashValue;

    /*!
     * \var size an integer that contains the amount of words in the hash table.
     */
    int size;

    /*!
     * \var load an integer that contains the amount of buckets being used.
     */
    int load;

    /*!
     * \var error an AvlNode pointer that contains an error message if the
     * search keyword doesn't exist.
     */
    AvlTree* error;

public:

    /*!
     * \brief HashTable default constructor
     */
    HashTable()
    {
        tableSize = 500009;
        hashValue = 0;
        size = 0;
        error = new AvlTree();
        bucket = new HashNode*[tableSize];
        for(int i = 0; i < tableSize; i++)
            bucket[i] = nullptr;
    }

    /*!
     * \brief HashTable copy constructor
     * \param cp a constant HashTable object
     */
    HashTable(const HashTable &cp)
    {
        tableSize = cp.tableSize;
        hashValue = cp.hashValue;
        size = cp.size;
        error = new AvlTree();
        error = cp.error;
        bucket = new HashNode*[tableSize];
        bucket = cp.bucket;
        for(int i = 0; i < tableSize; i++)
            bucket[i] = cp.bucket[i];
    }

    /*!
     * \brief operator = overloaded assignment operator
     * \param cp a constant HashTable object
     * \return a reference to a HashTable object
     */
    HashTable& operator=(const HashTable &cp)
    {
        if(this == &cp)
            return *this;

        tableSize = cp.tableSize;
        hashValue = cp.hashValue;
        size = cp.size;
        error = cp.error;
        bucket = cp.bucket;
        for(int i = 0; i < tableSize; i++)
            bucket[i] = cp.bucket[i];

    }

    /*!
     * \brief ~HashTable HashTable virtual destructor
     */
    virtual ~HashTable()
    {
        for(int i = 0; i < tableSize; i++)
            delete bucket[i];
        delete[] bucket;
    }

    /*!
     * \brief clear clears all the buckets in the hash table.
     */
    void clear()
    {
        for(int i = 0; i < tableSize; i++)
        {
            delete bucket[i];
            bucket[i] = nullptr;
        }
    }

    /*!
     * \brief insert all the information into a node.
     * \param keyword a string containing a keyword
     * \param pageNumber an integer containing a page number
     * \param freq a double containing the frequency of a word
     * \param header a string containing the page number
     * \param date a string containing the page date
     * \param user a string containing the page contributor's username
     */
    void insert(string& keyword, int& pageNumber, double& freq, string& header, string& date, string& user)
    {
        setHashValue(keyword);
        if(bucket[hashValue] == nullptr)
        {
            bucket[hashValue] = new HashNode();
            load++;
        }
        bucket[hashValue]->avl->insert(keyword, pageNumber, freq, header, date, user);
    }

    /*!
     * \brief insertLL inserts a word and linked list into a linked list.
     * \param keyword a string containing a word
     * \param ll a linked list pointer containing the page number, frequency,
     * page title, page date, and page contributor's username for the word
     */
    void insertLL(string& keyword, LinkedList*& ll)
    {
        setHashValue(keyword);
        if(bucket[hashValue] == nullptr)
        {
            bucket[hashValue] = new HashNode();
            load++;
        }
        bucket[hashValue]->avl->insertLL(keyword, ll);
    }

    /*!
     * \brief setHashValue sets a hash value for a word used to insert into a
     * bucket.
     * \param keyword a string containing a word
     */
    void setHashValue(string& keyword)
    {
        hash<string> strHash;
        int value = strHash(keyword);
        value = abs(value);
        hashValue = value % tableSize;
    }

    /*!
     * \brief getSize returns the size of the hash table
     * \return an integer reference
     */
    int& getSize()
    {
        for(int i = 0; i < tableSize; i++)
        {
            if(bucket[i] != nullptr)
                size += bucket[i]->avl->getSize();
        }
        return size;
    }

    /*!
     * \brief findKeyword finds a keyword in a node in the hash table.
     * \param keyword a string containing a word
     * \return
     */
    string& findKeyword(string& keyword)
    {
        setHashValue(keyword);
        if(bucket[hashValue] == nullptr)
            return error->findKeyword(keyword);
        else
            return bucket[hashValue]->avl->findKeyword(keyword);
    }

    /*!
     * \brief findData finds the data associated with a keyword in the linked
     * list.
     * \param keyword a string containing a keyword
     * \return a reference to a linked list pointer
     */
    LinkedList*& findData(string& keyword)
    {
        setHashValue(keyword);
        if(bucket[hashValue] == nullptr)
            return error->findData(keyword);
        else
            return bucket[hashValue]->avl->findData(keyword);
    }
};
#endif // HASHTABLE

