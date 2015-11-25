#include <iostream>

#include "queryprocessor.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"

QueryProcessor::QueryProcessor() {}

QueryProcessor::QueryProcessor(char* file)
{
    filename = file;
    //std::string filename = file;
}

void QueryProcessor::getDocumentContents(int documentNumber)
{
    rapidxml::file<> xmlFile(filename);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    rapidxml::xml_node<>* root = doc.first_node("mediawiki");
    rapidxml::xml_node<>* page = root->first_node("page");
    rapidxml::xml_node<>* revision = page->first_node("revision");
    rapidxml::xml_node<>* text = revision->first_node("text");
    int pageNumber = 1;

    while (pageNumber != documentNumber)
    {
        page = page->next_sibling("page");
        revision = page->first_node("revision");
        text = revision->first_node("text");
        pageNumber++;
    }

    std::cout << "Document " << documentNumber << " Contents:\n" <<
                    text->value() << std::endl;

    root = nullptr;
    page = nullptr;
    revision = nullptr;
    text = nullptr;
}