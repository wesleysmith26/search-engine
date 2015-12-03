#include <iostream>

#include "userinterface.h"
#include "documentparser.h"
#include "queryprocessor.h"

int main(int argc, char* argv[])
{   
    if (argc != 2)
        std::cerr << "Incorrect number of command line arguments" << std::endl;

    /*IndexHandler* myIndexHandler = new IndexHandler;
    DocumentParser* parser = new DocumentParser(myIndexHandler);
    parser->readDocument(argv[1]);
    myIndexHandler->printSize();

    delete parser;
    delete myIndexHandler;
    myIndexHandler = nullptr;
    parser = nullptr;*/

    //std::string searchPhrase = "AND computer Boston (NOT Seattle)";
    //QueryProcessor myQueryProcessor(argv[1], searchPhrase);

    UserInterface ui;
    ui.startScreen();

    //DocumentParser parser;
    //parser.getPageNumber(argv[1]);

    return 0;
}