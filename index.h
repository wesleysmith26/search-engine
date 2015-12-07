// Owner: Charlie
// File History:
// https://github.com/SMUCSE2341/BSSearch/commits/DocumentParser/index.h
#ifndef INDEX
#define INDEX
#include "linkedlist.h"
#include <string>
#include <map>

using namespace std;

/*!
 * \class Index
 * \brief an interface used for the AVL Tree and Hash Table
 */
class Index
{
public:
    /*!
     * \brief see documentation for AVL Tree or Hash Table
     */
    virtual void clear()=0;

    /*!
     * \brief see documentation for AVL Tree or Hash Table
     */
    virtual void insert(string& key, int& pg, double& freq, string& header, string& date, string& user)=0;

    /*!
     * \brief see documentation for AVL Tree or Hash Table
     */
    virtual void insertLL(string& key, LinkedList*& ll)=0;

    /*!
     * \brief see documentation for AVL Tree or Hash Table
     */
    virtual string& findKeyword(string& key)=0;

    /*!
     * \brief see documentation for AVL Tree or Hash Table
     */
    virtual LinkedList*& findData(string& key)=0;

    /*!
     * \brief see documentation for AVL Tree or Hash Table
     */
    virtual int& getSize()=0;
};
#endif // INDEX

