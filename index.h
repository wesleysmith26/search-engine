#ifndef INDEX
#define INDEX
#include "linkedlist.h"
#include <string>

using namespace std;
class Index
{
public:
    virtual void clear()=0;
    virtual void insert(string& key, int& pg, double& freq, string& header, string& date, string& user)=0;
    virtual string& findKeyword(string& key)=0;
    virtual LinkedList*& findData(string& key)=0;
    virtual int& getSize()=0;
};
#endif // INDEX

