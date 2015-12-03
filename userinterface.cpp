#include "userinterface.h"
#include "queryprocessor.h"
#include "documentparser.h"

#include <sstream>
UserInterface::UserInterface()
{
    select = 0;
    avlTree = true;
    searchWords = " ";
    xmlFile = nullptr;
}

UserInterface::UserInterface(char*& xmlFilename)
{
    select = 0;
    avlTree = true;
    searchWords = " ";
    xmlFile = xmlFilename;
}

void UserInterface::startScreen()
{
    cout<<"Please select the mode you would like to enter:\n1) Maintenance Mode\n2) Interactive Mode"<<endl;
    cin>>select;
    if(select == 1)
        maintenanceMode();
    else if (select == 2)
        interactiveMode();
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

void UserInterface::interactiveMode()
{
    cout << "Please select one of the options:\n1) Load Index into AVL Tree\n"
         << "2) Load Index into Hash Table\n3) Enter a Query" << endl;
    cin >> select;
    cin.ignore();

    if (select == 3)
    {
        cout << "Please enter a properly formatted query: ";
        getline(cin, searchWords);
        QueryProcessor qp(searchWords);
    }

    string answer = "";
    cout << "Do you want to view the contents of a page in the results? y/n? ";
    cin >> answer;

    if (answer == "y" || answer == "Y")
    {
        DocumentParser docParser;
        docParser.getPageNumber(xmlFile);
    }
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
