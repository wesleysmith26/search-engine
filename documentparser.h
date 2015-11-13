#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <string>
#include <vector>

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"

/*!
 * \brief Parses XML Document
 *
 * Parses the WikiBooks XML document using rapidxml libraries.
 */
class DocumentParser
{
private:
    /*!
     * \brief removes stopwords from a string
     * \param pageText a string
     * \param docNumber an integer
     */
    void removeStopwords(std::string& pageText, int docNumber);

    /*!
     * \brief splits a string into separate strings for each word
     * \param text a string
     * \return a vector of strings
     */
    std::vector<std::string> splitString(std::string& text);

    /*!
     * \brief removes stems from strings
     *
     * removes stems from strings using the Oleander Stemming Library, which
     * uses the Porter Stemming Algorithms to remove stems.
     * \param words a vector of strings
     */
    void removeStems(std::vector<std::string>& words);

public:
    /*!
     * \brief DocumentParser default constructor
     */
    DocumentParser();

    /*!
     * \brief reads/parses the xml document
     * \param filename a character pointer
     */
    void readDocument(char* filename);

};

#endif // DOCUMENTPARSER_H
