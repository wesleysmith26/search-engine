// Owners: Wesley and Charlie
// file history:
// https://github.com/SMUCSE2341/BSSearch/commits/DocumentParser/userinterface.cpp

#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "userinterface.h"
#include "queryprocessor.h"

UserInterface::UserInterface()
{
    docParser = nullptr;
    ih = nullptr;
    select = 0;
    searchWords = " ";
    xmlFile = nullptr;
}

UserInterface::UserInterface(char*& xmlFilename)
{
    ih = new IndexHandler;
    docParser = new DocumentParser(ih);
    select = 0;
    searchWords = " ";
    xmlFile = xmlFilename;
    docParser->readDocument(xmlFile);
}

UserInterface::~UserInterface()
{
    if (docParser != nullptr && ih != nullptr)
    {
        delete docParser;
        delete ih;
    }

    docParser = nullptr;
    ih = nullptr;
}

void UserInterface::startScreen()
{
    std::cout << "Please select the mode you would like to enter:\n1)"
              << " Maintenance Mode\n2) Interactive Mode\n3) Exit Program"
              << std::endl;
    std::cin >> select;

    if(select == 1)
        maintenanceMode();
    else if (select == 2)
        interactiveMode();
    else if (select == 3)
        exit(EXIT_SUCCESS);
}

void UserInterface::maintenanceMode()
{
    std::cout << "\nPlease select the one of options:\n1) Add Document\n2) "
              << "Clear Index\n3) Exit Maintence Mode" << std::endl;
    std::cin >> select;

    if(select == 1)
    {
        std::string temp = "";
        std::cout << "Please enter the name of the file to add to the index: ";
        std::cin.ignore();
        std::getline(cin, temp);
        char* filename = new char[temp.size() + 1];
        temp.copy(filename, temp.size());
        filename[temp.size()] = '\0';
        docParser->readDocument(filename);
        filename = nullptr;
    }
    else if(select == 2)
        ih->clear();

    std::cout << std::endl;
    startScreen();
}

void UserInterface::interactiveMode()
{
    std::cout << "\nPlease select one of the options:\n1) Enter a Query"
              << "\n2) Print Statistics" << std::endl;
    std::cin >> select;
    std::cin.ignore();

    if (select == 1)
    {
        std::cout << "Please enter a properly formatted query: ";
        std::getline(cin, searchWords);
        QueryProcessor qp(ih, searchWords);
        std::string answer = "";
        std::cout << "Do you want to view the contents of a page from the "
                  << "results? y/n? ";
        std::cin >> answer;

        if (answer == "y" || answer == "Y")
        {
            DocumentParser docParser;
            docParser.getPageNumber(xmlFile);
        }

        std::cout << std::endl;
    }
    else if (select == 2)
    {
        docParser->printNumberOfPagesIndexed();
        ih->printSize();
    }

    startScreen();
}
