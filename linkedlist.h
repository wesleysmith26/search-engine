#ifndef LINKEDLIST
#define LINKEDLIST
#include <iostream>
#include <string>

using namespace std;

class LinkedList
{
    struct Node
    {
        int pageNumber;
        double freqency;
        string title;
        string date;
        string user;
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

    void push_back(int pg, double freq, string docName, string dateMade, string userName)
    {
        if(empty())
        {
            head = new Node();
            head->pageNumber = pg;
            head->freqency = freq;
            head->title = docName;
            head->date = dateMade;
            head->user = userName;
        }else
        {
            cur = head;
            while(cur->next != nullptr)
            {
                cur = cur->next;
            }
            temp = new Node();
            temp->pageNumber = pg;
            temp->freqency = freq;
            temp->title = docName;
            temp->date = dateMade;
            temp->user = userName;
            cur->next = temp;
        }
    }

    int& getPageNumber(int index)
    {
        if(0 > index || size()-1 < index)
        {
            std::cout<<"index is out of bounds"<<std::endl;
            return cur->pageNumber;
        }else
        {
            cur = head;
            for(int counter = 0; counter < index; counter++)
                cur = cur->next;
            return cur->pageNumber;
        }
    }

    double& getFrequency(int index)
    {
        if(0 > index || size()-1 < index)
        {
            std::cout<<"index is out of bounds"<<std::endl;
            return cur->freqency;
        }else
        {
            cur = head;
            for(int counter = 0; counter < index; counter++)
                cur = cur->next;
            return cur->freqency;
        }
    }

    string& getTitle(int index)
    {
        if(0 > index || size()-1 < index)
        {
            std::cout<<"index is out of bounds"<<std::endl;
            return cur->title;
        }else
        {
            cur = head;
            for(int counter = 0; counter < index; counter++)
                cur = cur->next;
            return cur->title;
        }
    }

    string& getDate(int index)
    {
        if(0 > index || size()-1 < index)
        {
            std::cout<<"index is out of bounds"<<std::endl;
            return cur->date;
        }else
        {
            cur = head;
            for(int counter = 0; counter < index; counter++)
                cur = cur->next;
            return cur->date;
        }
    }

    string& getUser(int index)
    {
        if(0 > index || size()-1 < index)
        {
            std::cout<<"index is out of bounds"<<std::endl;
            return cur->user;
        }else
        {
            cur = head;
            for(int counter = 0; counter < index; counter++)
                cur = cur->next;
            return cur->user;
        }
    }

    void set_at(int index, int pg, double freq, string docName, string dateMade, string userName)
    {
        cur = head;
        for(int counter = 0; counter < index; counter++)
            cur = cur->next;
        cur->pageNumber = pg;
        cur->freqency = freq;
        cur->title = docName;
        cur->date = dateMade;
        cur->user = userName;
    }

    void deleteAt(int index)
    {
        if(index == 0)
        {
            temp = head->next;
            delete head;
            head = temp;
        }
        else
        {
            cur = head;
            for(int counter = 0; counter < index-1; counter++)
                cur = cur->next;
            temp = cur->next->next;
            delete cur->next;
            cur->next = temp;
        }
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
            cout<<"Linked list is empty"<<endl;
        else
        {
           cur = head;
           int counter = 0;
           while(cur->next != nullptr)
           {
               cout<<"Index: "<<counter<<" Data: "<<cur->pageNumber<<", "<<cur->freqency<<", "<<cur->title<<", "<<cur->date<<", "<<cur->user<<endl;
               counter++;
               cur = cur->next;
           }
           cout<<"Index: "<<counter<<" Data: "<<cur->pageNumber<<", "<<cur->freqency<<", "<<cur->title<<", "<<cur->date<<", "<<cur->user<<endl;
        }
    }

};
#endif // LINKEDLIST

