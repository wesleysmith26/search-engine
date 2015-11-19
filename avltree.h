#ifndef AVLTREE
#define AVLTREE
#include <iostream>
#include <string>
#include "linkedlist.h"

using namespace std;

class AvlTree
{
private:
    class AvlNode
    {
    public:
        string keyword;
        LinkedList<int>* pageNumbers = new LinkedList<int>;
        LinkedList<double>* freqency = new LinkedList<double>;
        LinkedList<string>* title = new LinkedList<string>;
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
            }
            if(right != nullptr)
            {
                delete right;
            }
            //what ever else you need to delete here
        }
    };

    AvlNode* root;
    AvlNode* error;
    AvlNode* temp;
    int size;

public:
    AvlTree()
    {
        root = nullptr;
        temp = nullptr;
        error = new AvlNode();
        error->keyword = "error";
    }

    ~AvlTree()
    {
        delete root->left;
        delete root->right;
        delete root;
    }

    AvlTree(const AvlTree&cp)
    {
        root = nullptr;
        *this = cp;
    }

    void makeEmpty()
    {
        makeEmpty(root);
        root = nullptr;
    }

    void insert(string& key, int& pg, double& freq, string& header)
    {
        insert(key, pg, freq, header,root);
    }

    string& findKeyword(string& key)
    {
        return findKeyword(key, root);
    }

    LinkedList<int>*& findPageNumber(string& key)
    {
        return findPageNumber(key,root);
    }

    LinkedList<double>*& findFrequency(string& key)
    {
        return findFrequency(key, root);
    }

    LinkedList<string>*& findTitle(string& key)
    {
        return findTitle(key, root);
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

    void insert(string& key, int& pg, double& freq, string& header, AvlNode*& t)
    {
        if(t == nullptr)
        {
            t = new AvlNode();
            t->keyword = key;
            t->pageNumbers->push_back(pg);
            t->freqency->push_back(freq);
            t->title->push_back(header);
            size++;
        } else if(key.compare(t->keyword) < 0) //insert left
        {
            insert(key, pg, freq, header, t->left);
            if(height(t->left) - height(t->right) == 2)
            {
                if(key.compare(t->left->keyword) < 0)
                    rotateWithLeftChild(t); // case 1
                else
                    doubleWithLeftChild(t); // case 2
            }
        } else if(key.compare(t->keyword) > 0) //insert right
        {
            insert(key, pg, freq, header, t->right);
            if(height(t->right) - height(t->left) == 2)
            {
                if(key.compare(t->right->keyword) > 0)
                    rotateWithRightChild(t); // case 4
                else
                    doubleWithRightChild(t);  // case 3
            }
        } else
        {
            t->pageNumbers->push_back(pg);
            t->freqency->push_back(freq);
        }

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

    LinkedList<int>*& findPageNumber(string &key, AvlNode *&t)
    {
        if(t == nullptr)
            return error->pageNumbers;
        if(key == t->keyword)
            return t->pageNumbers;
        else if(key.compare(t->keyword) < 0)
            return findPageNumber(key, t->left);
        else
            return findPageNumber(key, t->right);
    }

    LinkedList<double>*& findFrequency(string& key, AvlNode*& t)
    {
        if(t == nullptr)
            return error->freqency;
        else if(key == t->keyword)
            return t->freqency;
        else if(key.compare(t->keyword) < 0)
            return findFrequency(key, t->left);
        else
            return findFrequency(key, t->right);
    }

    LinkedList<string>*& findTitle(string& key, AvlNode*& t)
    {
        if(t == nullptr)
            return error->title;
        else if(key == t->keyword)
            return t->title;
        else if(key.compare(t->keyword) < 0)
            return findTitle(key, t->left);
        else
            return findTitle(key, t->right);
    }
};
#endif // AVLTREE

