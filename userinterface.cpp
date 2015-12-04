#include "userinterface.h"
#include "queryprocessor.h"

#include <sstream>
UserInterface::UserInterface()
{
    docParser = nullptr;
    ih = nullptr;
    select = 0;
    avlTree = true;
    searchWords = " ";
    xmlFile = nullptr;
}

UserInterface::UserInterface(char*& xmlFilename)
{
    ih = new IndexHandler;
    docParser = new DocumentParser(ih);
    select = 0;
    avlTree = true;
    searchWords = " ";
    xmlFile = xmlFilename;
    docParser->readDocument(xmlFile);
}

void UserInterface::startScreen()
{
    cout<<"Please select the mode you would like to enter:\n1) Maintenance Mode\n2) Interactive Mode"<<endl;
    cin>>select;
    if(select == 1)
        maintenanceMode();
    else if (select == 2)
        interactiveMode();
}

void UserInterface::maintenanceMode()
{
    cout<<"Please select the one of options:\n1) Add Document\n2) Clear Indexs\n3) Exit Maintence Mode"<<endl;
    cin>>select;
    if(select == 1)
        docParser->readDocument(xmlFile);
    else if(select == 2)
        cout<<"clear"<<endl;

    startScreen();
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
        QueryProcessor qp(ih, searchWords, avlTree);
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
