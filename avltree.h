#ifndef AVLTREE
#define AVLTREE
#include <iostream>
#include <string>
#include "index.h"
#include "linkedlist.h"

using namespace std;

class AvlTree: public Index
{
private:
    class AvlNode
    {
    public:
        string keyword;
        LinkedList* data = new LinkedList;
        AvlNode* left;
        AvlNode* right;
        int height;
        AvlNode()
        {
            left = nullptr;
            right = nullptr;
            height = 0;
        }
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
    AvlNode* error;
    AvlNode* root;
    int size;

public:
    AvlTree()
    {
        error = new AvlNode();
        error->keyword = "error";
        root = nullptr;
        size = 0;
    }

    virtual ~AvlTree()
    {
        delete root->left;
        root->left = nullptr;
        delete root->right;
        root->right = nullptr;
        delete root;
    }

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

    void clear()
    {
        delete root->left;
        root->left = nullptr;
        delete root->right;
        root->right = nullptr;
        delete root;
        root = nullptr;
    }

    void insert(string& key, int& pg, double& freq, string& header, string& date, string& user)
    {
        insert(key, pg, freq, header, date, user, root);
    }

    void insertLL(string& key, LinkedList*& ll)
    {
        insertLL(key, ll, root);
    }

    string& findKeyword(string& key)
    {
        return findKeyword(key, root);
    }

    LinkedList*& findData(string& key)
    {
        return findData(key,root);
    }

    int& getSize()
    {
        return size;
    }

private:

    int height(AvlNode*& t)
    {
        return t == nullptr ? -1 : t->height;
    }

    int max(int lhs, int rhs)
    {
        return lhs > rhs ? lhs : rhs;
    }

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

    void rotateWithLeftChild(AvlNode*& k2)
    {
        AvlNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2 = k1;
    }

    void rotateWithRightChild(AvlNode*& k1)
    {
        AvlNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->left), height(k1->right)) + 1;
        k1 = k2;
    }

    void doubleWithLeftChild(AvlNode*& k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(AvlNode*& k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

    void makeEmpty(AvlNode*& t)
    {
        if(t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
    }

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
