#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <string>
#include <vector>

#include "indexhandler.h"

class QueryProcessor
{
private:
    IndexHandler* myIndexHandler;
    std::string queryWords;
    bool useAvl;
    Index* index;
    LinkedList* outputLL;
    //std::string temp;

    /*!
     * \brief toLower converts query keywords to lowercase.
     */
    void toLower();

    /*!
     * \brief separateKeywords separates query keywords into separate strings.
     * \param searchQuery a string containing the user's query.
     */
    void separateKeywords(std::string& searchQuery);

    /*!
     * \brief removeBraceFromWord removes parentheses from the beginning or end
     * of keywords.
     * \param word a string containing a keyword from the user's query.
     */
    void removeParenthesesFromWord(std::string& word);

    /*!
     * \brief removeStopWords removes stopwords from the user's query.
     *
     * Removes stopwords from the user's query and adds them to a vector
     * containing the keywords as strings.
     * \param words a vector of strings containing the keywords from the user's
     * query.
     */
    void removeStopWords(std::vector<std::string>& words);

    /*!
     * \brief removeStems removes stems from the query keywords.
     * \param queryKeywords a vector of strings containing the keywords from the user's
     * query.
     */
    void removeStems(std::vector<std::string>& queryKeywords);

public:
    /*!
     * \brief QueryProcessor default constructor.
     */
    QueryProcessor();

    /*!
     * \brief QueryProcessor overloaded constructor.
     * \param ih an IndexHandler object.
     * \param searchText a string containing the user's query.
     */
    QueryProcessor(IndexHandler*& ih ,std::string& searchText, bool& avlTree);

};

#endif // QUERYPROCESSOR_H
