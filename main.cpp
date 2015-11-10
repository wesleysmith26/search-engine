#include <iostream>

#include "documentparser.h"

int main(int argc, char* argv[])
{   
    if (argc != 2)
        std::cerr << "Incorrect number of command line arguments" << std::endl;

    DocumentParser parser;
    parser.readDocument(argv[1]);

    return 0;
}