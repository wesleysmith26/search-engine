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
public:
    UserInterface();
    void startScreen();
    void maintenanceMode();
    void queryProcessor();
    void boolExpression();

};

#endif // USERINTERFACE_H
