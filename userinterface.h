#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <iostream>
#include <string>

using namespace std;

class UserInterface
{
private:
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
    void queryProcessor();
    void boolExpression();

};

#endif // USERINTERFACE_H