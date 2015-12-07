// Owner: Wesley
// File History:
// https://github.com/SMUCSE2341/BSSearch/commits/DocumentParser/documentparser.h

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
 *
 * Can also display the contents of a page in the xml file.
 */
class DocumentParser
{
private:
    /*!
     * \var myIndexHandler an IndexHandler pointer used to add words to the AVL
     * tree or the Hash table.
     */
    IndexHandler* myIndexHandler;
    /*!
     * \var documentNumber an integer that contains the number of documents
     * parsed
     */
    int documentNumber;

    /*!
     * \brief removeStopwords removes stopwords from the words in each document.
     *
     * Compares each word in the docWords vector with the stopwords array. If
     * there is a stopword in the vector it will be removed.
     * \param pageText a string containing the text in the particular page
     * \param pageTitle a string containing the title of the page
     * \param pageDate a string containing the timestamp of the page
     * \param pageContributor a string containing the page contributor's username
     */
    void removeStopwords(std::string& pageText, std::string& pageTitle,
                         std::string& pageDate, std::string& pageContributor);

    /*!
     * \brief splitString splits the text for a page into individual words and
     * adds it to a vector of strings.
     * \param text a string containing the text for the particular page
     * \param pageText a string vector that will contain the words for the page
     */
    void splitString(std::string& text, std::vector<std::string>& pageText);

    /*!
     * \brief toLower converts strings to lowercase
     *
     * Converts the strings to lowercase using the transform function included
     * in the algorithm library, since there isn't a lowercase function in the
     * std string library.
     * \param pageWords a vector of strings containing the words for the page
     */
    void toLower(std::vector<std::string>& pageWords);

    /*!
     * \brief removeStems removes stems from words using the Oleander stemming
     * library
     *
     * \param words a vector of strings containing the words for the page
     */
    void removeStems(std::vector<std::string>& words);

    /*!
     * \brief calculateTermFrequency calculates the number of times a word
     * appears on the page.
     *
     * Stores the word and frequency in a map and sends the map along with the
     * title, date, and contributor's username for the page.
     * \param terms a vector of strings containing the words for the page
     * \param docTitle a string containing the title of the page in the xml file
     * \param date a string containing the article date
     * \param contributor a string containing the article contributor's username
     */
    void calculateTermFrequency(std::vector<std::string>& terms,
                                std::string& docTitle, std::string& date,
                                std::string& contributor);

    /*!
     * \brief checkForDuplicateTerm checks for duplicate terms in the map.
     *
     * Removes duplicate terms in the map if they exist and updates the
     * frequency of the word. If the word isn't a duplicate it is added to the
     * map.
     * \param word a string containing the word that is being checked
     * \param terms a map with a string key and integer value containing each
     * word and the term frequency for each word
     */
    void checkForDuplicateTerm(std::string& word, std::map<std::string,
                               int>& terms);

    /*!
     * \brief getDocumentContents parses the xml file until the specified page
     * is found and outputs the contents of the page.
     * \param docFilename a character pointer containing the xml filename
     * \param documentNumber an integer containing the page number of the user
     * requested page
     */
    void getDocumentContents(char*& docFilename, int& docNum);

public:
    /*!
     * \brief DocumentParser default constructor
     */
    DocumentParser();

    /*!
     * \brief DocumentParser overloaded constructor
     * \param ih a pointer to an Index Handler object
     */
    DocumentParser(IndexHandler*& ih);

    /*!
     * \brief readDocument parses the xml file
     * \param filename a character pointer that contains the xml filename
     */
    void readDocument(char*& filename);

    /*!
     * \brief getPageNumber asks the user which page number they want to view
     * the contents of from the search results.
     * \param file a character pointer that contains the xml filename
     */
    void getPageNumber(char*& file);

    /*!
     * \brief printNumberOfPagesIndexed prints the number of pages indexed by
     * the index handler.
     */
    void printNumberOfPagesIndexed();
};

#endif // DOCUMENTPARSER_H
