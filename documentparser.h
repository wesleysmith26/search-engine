#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <string>
#include <vector>
#include <map>

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "indexhandler.h"

/*!
 * \brief Parses XML Document
 *
 * Parses the WikiBooks XML document using rapidxml libraries.
 */
class DocumentParser
{
private:
    // figure out what to do w/ this
    std::map<std::string, int> totalTermFrequency;
    IndexHandler* myIndexHandler;

    /*!
     * \brief removes stopwords from a string
     * \param pageText a string
     * \param docNumber an integer
     * \param pageTitle a string
     */
    void removeStopwords(std::string& pageText, int docNumber,
                         std::string& pageTitle);

    /*!
     * \brief splits a string into separate strings for each word
     * \param text a string
     * \param pageText a vector of strings
     */
    void splitString(std::string& text, std::vector<std::string>& pageText);

    /*!
     * \brief converts std::string to lowercase
     * \param pageWords a vector of strings
     */
    void toLower(std::vector<std::string>& pageWords);

    /*!
     * \brief removes stems from strings
     *
     * removes stems from strings using the Oleander Stemming Library, which
     * uses the Porter Stemming Algorithms to remove stems.
     * \param words a vector of strings
     */
    void removeStems(std::vector<std::string>& words);

    /*!
     * \brief calculates how often a word appears
     *
     * calculates the number of times a word appears in a particular page and
     * the entire corpus. Passes a map of strings and an integer representing
     * the page number to the index handler.
     * \param terms a vector of strings
     * \param pageNumber an integer
     * \param docTitle a string
     */
    void calculateTermFrequency(std::vector<std::string>& terms,
                                int& pageNumber, std::string& docTitle);

    /*!
     * \brief checks if a duplicate term will be added to the map
     *
     * checks if a  duplicate term is going to be added to the page map or the
     * corpus map. Adds the word to the respective map if it isn't a duplicate
     * \param word a string
     * \param terms a map with a string key and int value
     */
    void checkForDuplicateTerm(std::string& word, std::map<std::string,
                               int>& terms);

public:
    /*!
     * \brief DocumentParser constructor
     */
    DocumentParser(IndexHandler*& ih);

    /*!
     * \brief reads/parses the xml document
     * \param filename a character pointer
     */
    void readDocument(char* filename);

};

#endif // DOCUMENTPARSER_H
