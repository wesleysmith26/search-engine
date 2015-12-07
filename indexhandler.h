// Owner: Charlie
// file history:
// https://github.com/SMUCSE2341/BSSearch/commits/DocumentParser/indexhandler.h

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

/*!
 * \class IndexHandler
 * \brief Adds information from the document parser to the avl tree or hash
 * table, searches the avl tree or hash table for query keywords from the
 * query processor, and prints the number of words indexed.
 */
class IndexHandler
{
private:
    /*!
     * \var avl an Index pointer used to call functions for the avl tree
     */
    Index* avl;

    /*!
     * \var hash an Index pointer used to call functions for the hash table
     */

    Index* hash;
    /*!
     * \var avlSearch an Index pointer used to search the avl tree
     */

    Index* avlSearch;
    /*!
     * \brief hashSearch an Index pointer used to search the hash table
     */
    Index* hashSearch;

    /*!
     * \var freq a double containing the td/idf for the word
     */
    double freq = 0.0;
public:
    /*!
     * \brief IndexHandler default constructor
     */
    IndexHandler();

    /*!
     * \brief IndexHandler destructor
     */
    ~IndexHandler();

    /*!
     * \brief addWord adds a word to the index.
     * \param table a map with string keys and int values containg words and
     * their frequency from the parsed page
     * \param pg an integer containing the page number parsed
     * \param title a string containing the title of the parsed page
     * \param date a string containing the date of the parsed page
     * \param user a string containing the contributor's username of the parsed
     * page
     */
    void addWord(map<string, int>& table, int& pg, string& title, string &date, string &user);

    /*!
     * \brief searchAvl searches the avl tree for the query keywords.
     * \param searchWords a vector of strings containing the query keywords
     * \return a reference to an Index pointer
     */
    Index*& searchAvl(vector<string>& searchWords);

    /*!
     * \brief searchHash searches the hash table for the query keywords.
     * \param searchWords a vector of strings containing the query keywords
     * \return a reference to an Index pointer
     */
    Index*& searchHash(vector<string>& searchWords);

    /*!
     * \brief clear clears the index structure.
     */
    void clear();

    /*!
     * \brief printSize prints the number of words indexed.
     */
    void printSize();

};

#endif // INDEXHANDLER_H

