#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <string>
#include <vector>
#include <map>

#include "indexhandler.h"

/*!
 * \class DocumentParser
 * \brief Parses XML Document
 *
 * Parses the WikiBooks XML document using rapidxml libraries, collecting the
 * document title, date, contributor's username, and contents. The document
 * contents are then split up into individual strings for each word. Words that
 * are stop words are removed, and the leftover words have their stems removed.
 * Then frequency of duplicate words is calculated, and the document title,
 * date, contributor's username, and words are sent to the Index Handler.
 */
class DocumentParser
{
private:
    IndexHandler* myIndexHandler;

    void removeStopwords(std::string& pageText, int docNumber,
                         std::string& pageTitle, std::string& pageDate,
                         std::string& pageContributor);

    void splitString(std::string& text, std::vector<std::string>& pageText);

    void toLower(std::vector<std::string>& pageWords);

    void removeStems(std::vector<std::string>& words);

    void calculateTermFrequency(std::vector<std::string>& terms,
                                int& pageNumber, std::string& docTitle);

    void checkForDuplicateTerm(std::string& word, std::map<std::string,
                               int>& terms);

public:
    DocumentParser();

    DocumentParser(IndexHandler*& ih);

    void readDocument(char* filename);

};

#endif // DOCUMENTPARSER_H
