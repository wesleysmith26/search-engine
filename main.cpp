// File History:
// https://github.com/SMUCSE2341/BSSearch/commits/DocumentParser/main.cpp
#include <iostream>

#include "userinterface.h"
#include "documentparser.h"
#include "queryprocessor.h"

int main(int argc, char* argv[])
{   
    if (argc != 2)
        std::cerr << "Incorrect number of command line arguments" << std::endl;

    UserInterface* ui = new UserInterface(argv[1]);
    ui->startScreen();
    ui = nullptr;

    return 0;
}