#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <iostream>
#include <string>

#include "documentparser.h"
#include "indexhandler.h"

using namespace std;

class UserInterface
{
private:
    DocumentParser* docParser;
    IndexHandler* ih;
    int select;
    bool avlTree;
    string searchWords;
    char* xmlFile;

    void interactiveMode();

public:
    UserInterface();
    UserInterface(char*& xmlFilename);
    void startScreen();
    void maintenanceMode();
    void boolExpression();

};

#endif // USERINTERFACE_H