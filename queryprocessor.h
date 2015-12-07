// Owners: Charlie, Wesley, Zach
// File History:
// https://github.com/SMUCSE2341/BSSearch/commits/DocumentParser/queryprocessor.cpp

#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <string>
#include <vector>

#include "indexhandler.h"

/*!
 * \brief QueryProcessor processes search queries entered by the user.
 */
class QueryProcessor
{
private:
    /*!
     * \var myIndexHandler a pointer to an IndexHandler object.
     */
    IndexHandler* myIndexHandler;

    /*!
     * \var queryWords a string containing the user's search query.
     */
    std::string queryWords;

    /*!
     * \var index a pointer to an Index object.
     */
    Index* index;

    /*!
     * \var outputLL a pointer to a LinkedList object
     */
    LinkedList* outputLL;

    /*!
     * \var parentheses a string containing words with closed or open
     * parentheses.
     */
    std::string parentheses;

    /*!
     * \var nestCounter an integer containing the number of open parentheses to
     * determine the depth of nesting.
     */
    int nestCounter;

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
     * \brief separateKeywordsBool creates a vector from the boolean expression.
     * \param searchQuery a string containing the user's query.
     */
    void separateKeywordsBool(std::string& searchQuery);

    /*!
     * \brief removeBraceFromWord removes parentheses from the beginning or end
     * of keywords.
     * \param word a string containing a keyword from the user's query.
     */
    void removeParenthesesFromWord(std::string& word);

    /*!
     * \brief seperateParenthesesFromWord removes parentheses from all words in
     * the query.
     * \param word a string containing the user's query
     */
    void seperateParenthesesFromWord(std::string& word);

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

    /*!
     * \brief noNest evaluates a query with no nesting and a query that is
     * reduced down to having no nesting.
     * \param phrase a vector of strings containing the user's query
     */
    void noNest(std::vector<std::string>& phrase);

    /*!
     * \brief singleNest evaluates query with single level of nesting and
     * queries that are reduced to a single level of nesting.
     * \param restOfPhrase a vector of strings containing the remaining query
     * \param phrase a vector of strings containing the user's query
     */
    void singleNest(std::vector<std::string>& restOfPhrase, std::vector<std::string>& phrase);

    /*!
     * \brief doubleNest evaluates a query with 2 levels of nesting, calls the
     * singleNest function, sending the new vector and the vector with the
     * remaining phrase.
     * \param restOfPhrase a vector of strings containing the remaining query
     * \param phrase a vector of strings containing the user's query
     */
    void doubleNest(std::vector<std::string>& restOfPhrase, std::vector<std::string>& phrase);

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
    QueryProcessor(IndexHandler*& ih ,std::string& searchText);

};

#endif // QUERYPROCESSOR_H
