#ifndef LINKEDLIST
#define LINKEDLIST
#include <iostream>

template <typename T>
class LinkedList
{
    struct Node
    {
        T data;
        Node *next;
    };

private:
    Node* head;
    Node* cur;
    Node* temp;
public:
    LinkedList()
    {
        head = nullptr;
        cur = nullptr;
        temp = nullptr;
    }

    ~LinkedList()
    {
        if(head != nullptr)
        {
            while(head->next != nullptr)
            {
                temp = head->next;
                delete head;
                head = temp;
            }
            delete head;
        }
    }

    bool empty()
    {
        if(head == nullptr)
            return true;
        else
            return false;
    }

    bool checkNext(int index)
    {
        cur = head;
        for(int counter = 0; counter < index; counter++)
            cur = cur->next;
        if(cur->next == nullptr)
            return false;
        else
            return true;
    }

    void push_back(T newData)
    {
        if(empty())
        {
            head = new Node();
            head->data = newData;
        }else
        {
            cur = head;
            while(cur->next != nullptr)
            {
                cur = cur->next;
            }
            temp = new Node();
            temp->data = newData;
            cur->next = temp;
        }
    }

    T& get_at(int index)
    {
        if(0 > index || size()-1 < index)
        {
            std::cout<<"index is out of bounds"<<std::endl;
            return cur->data;
        }else
        {
            cur = head;
            for(int counter = 0; counter < index; counter++)
                cur = cur->next;
            return cur->data;
        }
    }

    void set_at(int index, T val)
    {
        cur = head;
        for(int counter = 0; counter < index; counter++)
            cur = cur->next;
        cur->data = val;
    }

    int size()
    {
        if(empty())
            return 0;
        temp = head;
        int counter = 1;
        while(temp->next != nullptr)
        {
            temp = temp->next;
            counter++;
        }
        return counter;
    }

    void output()
    {
        if(empty())
            std::cout<<"Linked list is empty"<<std::endl;
        else
        {
           cur = head;
           int counter = 0;
           while(cur->next != nullptr)
           {
               std::cout<<"Index: "<<counter<<" Data: "<<cur->data<<std::endl;
               counter++;
               cur = cur->next;
           }
           std::cout<<"Index: "<<counter<<" Data: "<<cur->data<<std::endl;
        }
    }

};
#endif // LINKEDLIST

