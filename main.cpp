#include <iostream>

#include "documentparser.h"

int main(int argc, char* argv[])
{   
    if (argc != 2)
        std::cerr << "Incorrect number of command line arguments" << std::endl;

    IndexHandler* myIndexHandler = new IndexHandler;
    DocumentParser* parser = new DocumentParser(myIndexHandler);
    parser->readDocument(argv[1]);
    myIndexHandler->printSize();

    myIndexHandler = nullptr;
    parser = nullptr;

    return 0;
}