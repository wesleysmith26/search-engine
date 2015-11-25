#include "userinterface.h"
#include <sstream>
UserInterface::UserInterface()
{
    select = 0;
    avlTree = true;
    searchWords = " ";
}

void UserInterface::startScreen()
{
    cout<<"Please select the mode you would like to enter:\n1) Maintenance Mode\n2) Interactive Mode"<<endl;
    cin>>select;
    if(select == 1)
        maintenanceMode();
    else
        queryProcessor();
}

void UserInterface::maintenanceMode()
{
    cout<<"Please select the one of options:\n1) Add Document\n2) Clear Indexs\n3) Exit Maintence Mode"<<endl;
    cin>>select;
    if(select == 1)
        cout<<"add doc"<<endl;
    else if(select == 2)
        cout<<"clear"<<endl;
    else
        queryProcessor();
}

void UserInterface::queryProcessor()
{
    cout<<"Please select the index you would like to use:\n1) Avl Tree\n2) Hash Table"<<endl;
    cin>>select;
    if(select == 2)
        avlTree = false;
    else
        avlTree = true;

    cout<<"Please enter the words you would like to search for:"<<endl;
    //cin>>getline(searchWords);

    cout<<searchWords;
}
