// Owner: Charlie
// file history:
// https://github.com/SMUCSE2341/BSSearch/commits/DocumentParser/linkedlist.h

#ifndef LINKEDLIST
#define LINKEDLIST
#include <iostream>
#include <string>

using namespace std;

/*!
 * \class The LinkedList class
 * \brief Singly linked list that has nodes that contain the page number,
 * term frequency, document title, document date, and contributor's username.
 */
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
    bool contain;
public:
    /*!
     * \brief LinkedList default constructor
     */
    LinkedList()
    {
        head = nullptr;
        cur = nullptr;
        temp = nullptr;
    }

    /*!
     * \brief LinkedList destructor
     */
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

    /*!
     * \brief LinkedList copy constructor
     * \param cp a constant LinkedList object
     */
    LinkedList(const LinkedList &cp)
    {
        if(cp.head == nullptr)
        {
            head = nullptr;
        } else
        {
            head = new Node();
            head = cp.head;
        }

        if(cp.cur == nullptr)
        {
            cur = nullptr;
        } else
        {
            cur = new Node();
            cur = cp.cur;
        }

        if(cp.temp == nullptr)
        {
            temp = nullptr;
        } else
        {
            temp = new Node();
            temp = cp.temp;
        }
    }

    void clear()
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
            head = nullptr;
        }
    }

    /*!
     * \brief overloaded assignment operator
     * \param cp a constant LinkedList object
     * \return a LinkedList object
     */
    LinkedList& operator=(const LinkedList &cp)
    {
        if(this == &cp)
            return *this;

        if(cp.head == nullptr)
            head = nullptr;
        else
            head = cp.head;

        if(cp.cur == nullptr)
            cur = nullptr;
        else
            cur = cp.cur;

        if(cp.temp == nullptr)
            temp = nullptr;
        else
            temp = cp.temp;

        return *this;

    }

    /*!
     * \brief empty checks if the linked list is empty.
     * \return true if the linked list is empty and false if it is not empty
     */
    bool empty()
    {
        if(head == nullptr)
            return true;
        else
            return false;
    }


    /*!
     * \brief checkNext checks if the next node is a nullptr.
     * \param index an integer representing the node number
     * \return true if next node isn't a nullptr and true if it is a nullptr
     */
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

    /*!
     * \brief push_back adds a node to the end of the linked list.
     * \param pg an integer containing the page number in the xml file
     * \param freq a double containing the term frequency for the document
     * \param docName a string containing the title of the page
     * \param dateMade a string containing the timestamp of the page
     * \param userName a string containing the page contributor's username
     */
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

    /*!
     * \brief getPageNumber gets the page number from a node in the linked list.
     * \param index an integer representing the node number in the linked list
     * \return an integer representing the page number from the specified node
     */
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

    /*!
     * \brief getFrequency gets the term frequency from a node in the linked
     * list.
     * \param index an integer representing the node number in the linked list
     * \return a double representing the term frequency from the specified node
     */
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

    /*!
     * \brief getTitle gets the page title from a node in the linked list.
     * \param index an integer representing the node number in the linked list
     * \return  a string representing the page title from the specified node
     */
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

    /*!
     * \brief getDate gets the page date from a node in the linked list.
     * \param index an integer representing the node number in the linked list
     * \return a string representing the page date from the specified node
     */
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

    /*!
     * \brief getUser gets the contributor's username from a node in the linked
     * list.
     * \param index an integer representing the node number in the linked list
     * \return a string representing the contributor's username from the
     * specified node.
     */
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

    void set_at(int index, double freq)
    {
        cur = head;
        for(int counter = 0; counter < index; counter++)
            cur = cur->next;
        cur->freqency += freq;
    }

    void set_at(int index, int pg ,double freq, string docName, string dateMade, string userName)
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

    void findSet(int pg, double freq)
    {
        cur = head;
        while(cur->pageNumber != pg)
            cur = cur->next;
        cur->freqency += freq;
    }

    /*!
     * \brief deleteAt deletes a specified node in the linked list.
     * \param index index an integer representing the node number in the linked
     * list
     */
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

    /*!
     * \brief size gets the size of the linked list.
     * \return an integer representing the size of the linked list
     */
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

    /*!
     * \brief sort sorts the linked list by term frequency in descending order.
     */
    void sort(int start, int end)
    {
        if(start < end)
        {
            int p = partition(start, end);
            sort(start, p-1);
            sort(p+1, end);
        }
    }

    int partition(int low, int high)
    {
        double pivot = getFrequency(high);
        int left = low-1;

        for(int right = low; right < high; right++)
        {
            if(getFrequency(right) > pivot)
            {
                left++;
                swap(left, right);
            }
        }

        swap(left+1, high);
        return left+1;

    }

    void swap(int a, int b)
    {
        int pgTemp;
        double freqTemp;
        string titleTemp;
        string dateTemp;
        string userTemp;

        pgTemp = getPageNumber(a);
        freqTemp = getFrequency(a);
        titleTemp = getTitle(a);
        dateTemp = getDate(a);
        userTemp = getUser(a);

        set_at(a, getPageNumber(b), getFrequency(b), getTitle(b), getDate(b), getUser(b));
        set_at(b, pgTemp, freqTemp, titleTemp, dateTemp, userTemp);
    }

    bool contains(int& pg)
    {
        cur = head;
        while(cur != nullptr)
        {
            if(cur->pageNumber == pg)
                return true;
            cur = cur->next;
        }
        return false;
    }

    int findIterator(int& pg)
    {
        cur = head;
        int it = 0;
        while(cur != nullptr)
        {
            if(cur->pageNumber == pg)
                return it;
            cur = cur->next;
            it++;
        }
        return 0;
    }

    void output()
    {
        if(empty())
            cout<<"Linked list is empty"<<endl;
        else
        {
           cur = head;
           int counter = 0;
           while(cur != nullptr && counter < 16)
           {
               cout<<"Index: "<<counter<<" Data: "<<cur->pageNumber<<", "<<cur->freqency<<", "<<cur->title<<", "<<cur->date<<", "<<cur->user<<endl;
               counter++;
               cur = cur->next;
           }
           cout<<"Total Number of Indexs: "<<size()<<endl;
        }
    }

};
#endif // LINKEDLIST
