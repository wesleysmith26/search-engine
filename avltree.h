// Owner: Charlie
// file history:
// https://github.com/SMUCSE2341/BSSearch/commits/DocumentParser/avltree.h

#ifndef AVLTREE
#define AVLTREE
#include <iostream>
#include <string>
#include <utility>
#include <map>
#include "index.h"
#include "linkedlist.h"

using namespace std;

/*!
 * \class AvlTree an Index subclass
 * \brief An Avl Tree with nodes that contain a word, page number, page title,
 * page date, page contributor's username, and a pointer to the next node.
 */
class AvlTree: public Index
{
private:
    /*!
     * \class AvlNode
     * \brief a node class for the avl tree that contains a query keyword, a
     * linked list of words, pages, frequencies, titles, dates, and usernames,
     * an AvlNode pointer to the left and one to the right, as well as the
     * height of the avl tree.
     */
    class AvlNode
    {
    public:
        /*!
         * \var keyword a string containing a query keyword
         */
        string keyword;

        /*!
         * \var data a linked list containing words, pages, frequencies,
         * titles, dates, and usernames
         */
        LinkedList* data = new LinkedList;

        /*!
         * \var left an AvlNode pointer that points to the next node to the
         * left in the tree.
         */
        AvlNode* left;

        /*!
         * \var right an AvlNode pointer that points to the next node to the
         * right in the tree.
         */
        AvlNode* right;

        /*!
         * \var height an integer containing the height of the tree.
         */
        int height;

        /*!
         * \brief AvlNode default constructor
         */
        AvlNode()
        {
            left = nullptr;
            right = nullptr;
            height = 0;
        }

        /*!
         * \brief AvlNode destructor
         */
        ~AvlNode()
        {
            if(left != nullptr)
            {
                delete left;
                left = nullptr;
            }
            if(right != nullptr)
            {
                delete right;
                right = nullptr;
            }
            delete this->data;
        }
    };

    /*!
     * \var error an AvlNode pointer that contains an error message if the
     * search keyword doesn't exist.
     */
    AvlNode* error;

    /*!
     * \var root an AvlNode pointer that contains the root node of the tree.
     */
    AvlNode* root;

    /*!
     * \brief size an integer containing how many words is in the tree.
     */
    int size;

public:
    /*!
     * \brief AvlTree default constructor
     */
    AvlTree()
    {
        error = new AvlNode();
        error->keyword = "error";
        root = nullptr;
        size = 0;
    }

    /*!
     * \brief ~AvlTree virtual destructor
     */
    virtual ~AvlTree()
    {
        delete root->left;
        root->left = nullptr;
        delete root->right;
        root->right = nullptr;
        delete root;
    }

    /*!
     * \brief AvlTree copy constructor.
     * \param cp a constant AvlTree object
     */
    AvlTree(const AvlTree &cp)
    {
        error = new AvlNode();
        error = cp.error;
        if(cp.root == nullptr)
        {
            root = nullptr;
        } else
        {
            root = new AvlNode();
            root = cp.root;
        }
        size = cp.size;
    }

    /*!
     * \brief operator = overloaded assignment operator.
     * \param cp a constant AvlTree object
     * \return an AvlTree reference
     */
    AvlTree& operator=(const AvlTree &cp)
    {
        if(this == &cp)
            return *this;

        error = cp.error;

        if(cp.root == nullptr)
            root = nullptr;
        else
            root = cp.root;

        size = cp.size;

        return *this;
    }

    /*!
     * \brief clear clears the avl tree.
     */
    void clear()
    {
        delete root->left;
        root->left = nullptr;
        delete root->right;
        root->right = nullptr;
        delete root;
        root = nullptr;
    }

    /*!
     * \brief insert inserts a node into the tree.
     * \param key a string containing a word from the page
     * \param pg an integer containing the page number
     * \param freq an integer containing the word frequency
     * \param header a string containing the page title
     * \param date a string containing the page date
     * \param user a string containing the page contributor's username
     */
    void insert(string& key, int& pg, double& freq, string& header, string& date, string& user)
    {
        insert(key, pg, freq, header, date, user, root);
    }

    /*!
     * \brief insertLL inserts a word and linked list into a linked list.
     * \param key a string containing a word
     * \param ll a linked list pointer containing the page number, frequency,
     * page title, page date, and page contributor's username for the word
     */
    void insertLL(string& key, LinkedList*& ll)
    {
        insertLL(key, ll, root);
    }

    /*!
     * \brief findKeyword finds a keyword in the tree.
     * \param key a string containing a keyword
     * \return a reference to a string
     */
    string& findKeyword(string& key)
    {
        return findKeyword(key, root);
    }

    /*!
     * \brief findData finds the data associated with a keyword in the linked
     * list.
     * \param key a string containing a keyword
     * \return a reference to a linked list pointer
     */
    LinkedList*& findData(string& key)
    {
        return findData(key,root);
    }

    /*!
     * \brief getSize returns the size of the tree.
     * \return a reference to an integer
     */
    int& getSize()
    {
        return size;
    }

private:

    /*!
     * \brief height returns the height of a node in the tree.
     * \param t an AvlNode pointer
     * \return an integer
     */
    int height(AvlNode*& t)
    {
        return t == nullptr ? -1 : t->height;
    }

    /*!
     * \brief max returns the maximum height of each side of the tree.
     * \param lhs an integer containing the height of the left side
     * \param rhs an integer containing the height of the right side
     * \return an integer
     */
    int max(int lhs, int rhs)
    {
        return lhs > rhs ? lhs : rhs;
    }

    /*!
     * \brief insert inserts a word, page number, frequency, page title,
     * page date, page contributor's username, and an AvlNode pointer to a
     * new node in the tree.
     * \param key a string containing a word from the page
     * \param pg an integer containing the page number
     * \param freq an integer containing the word frequency
     * \param header a string containing the page title
     * \param date a string containing the page date
     * \param user a string containing the page contributor's username
     * \param t an AvlNode pointer representing a node in the tree
     */
    void insert(string& key, int& pg, double& freq, string& header, string& date, string& title, AvlNode*& t)
    {
        if(t == nullptr)
        {
            t = new AvlNode();
            t->keyword = key;
            t->data->push_back(pg, freq, header, date, title);
            size++;
        } else if(key.compare(t->keyword) < 0) //insert left
        {
            insert(key, pg, freq, header, date, title, t->left);
            if(height(t->left) - height(t->right) == 2)
            {
                if(key.compare(t->left->keyword) < 0)
                    rotateWithLeftChild(t); // case 1
                else
                    doubleWithLeftChild(t); // case 2
            }
        } else if(key.compare(t->keyword) > 0) //insert right
        {
            insert(key, pg, freq, header, date, title, t->right);
            if(height(t->right) - height(t->left) == 2)
            {
                if(key.compare(t->right->keyword) > 0)
                    rotateWithRightChild(t); // case 4
                else
                    doubleWithRightChild(t);  // case 3
            }
        } else
        {
            t->keyword = key;
            t->data->push_back(pg, freq, header, date, title);
        }

        t->height = max(height(t->left), height(t->right)) + 1;
    }

    /*!
     * \brief insertLL inserts a word and a linked list into a node in the tree
     * \param key a string containing a word from the page.
     * \param ll a linked list pointer containing the information associated
     * with the word and the page it's on
     * \param t an AvlNode pointer representing a node in the tree
     */
    void insertLL(string& key, LinkedList*& ll, AvlNode*& t)
    {
        if(t == nullptr)
        {
            t = new AvlNode();
            t->keyword = key;
            t->data = ll;
            size++;
        } else if(key.compare(t->keyword) < 0) //insert left
        {
            insertLL(key, ll, t->left);
            if(height(t->left) - height(t->right) == 2)
            {
                if(key.compare(t->left->keyword) < 0)
                    rotateWithLeftChild(t); // case 1
                else
                    doubleWithLeftChild(t); // case 2
            }
        } else if(key.compare(t->keyword) > 0) //insert right
        {
            insertLL(key, ll, t->right);
            if(height(t->right) - height(t->left) == 2)
            {
                if(key.compare(t->right->keyword) > 0)
                    rotateWithRightChild(t); // case 4
                else
                    doubleWithRightChild(t);  // case 3
            }
        } else { }

        t->height = max(height(t->left), height(t->right)) + 1;
    }

    /*!
     * \brief rotateWithLeftChild case 1 rotation
     * \param k2 an AvlNode pointer
     */
    void rotateWithLeftChild(AvlNode*& k2)
    {
        AvlNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2 = k1;
    }

    /*!
     * \brief rotateWithRightChild case 4 rotation
     * \param k1 an AvlNode pointer
     */
    void rotateWithRightChild(AvlNode*& k1)
    {
        AvlNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->left), height(k1->right)) + 1;
        k1 = k2;
    }

    /*!
     * \brief doubleWithLeftChild case 2 rotation
     * \param k3 an AvlNode pointer
     */
    void doubleWithLeftChild(AvlNode*& k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /*!
     * \brief doubleWithRightChild case 3 rotation
     * \param k1 an AvlNode pointer
     */
    void doubleWithRightChild(AvlNode*& k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

    /*!
     * \brief makeEmpty makes each node in the tree empty
     * \param t
     */
    void makeEmpty(AvlNode*& t)
    {
        if(t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
    }

    /*!
     * \brief findKeyword finds a keyword in the tree
     * \param key a string containing a keyword
     * \param t an AvlNode pointer
     * \return a reference to a string
     */
    string& findKeyword(string& key, AvlNode*& t)
    {
        if(t == nullptr)
            return error->keyword;
        if(key == t->keyword)
            return t->keyword;
        else if(key.compare(t->keyword) < 0)
            return findKeyword(key, t->left);
        else
            return findKeyword(key, t->right);
    }

    /*!
     * \brief findData finds a node in the tree with the keyword and returns
     * the data associated with the keyword in a linked list.
     * \param key a string containing a keyword
     * \param t an AvlNode pointer
     * \return a pointer reference to a LinkedList
     */
    LinkedList*& findData(string &key, AvlNode *&t)
    {
        if(t == nullptr)
            return error->data;
        if(key == t->keyword)
            return t->data;
        else if(key.compare(t->keyword) < 0)
            return findData(key, t->left);
        else
            return findData(key, t->right);
    }

};
#endif // AVLTREE
