#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

class QueryProcessor
{
private:
    char* filename;

public:
    /*!
     * \brief QueryProcessor default constructor
     */
    QueryProcessor();

    /*!
     * \brief QueryProcessor overloaded constructor
     *
     * takes a file character pointer that will be used to get documents from
     * the file
     * \param file a character pointer
     */
    QueryProcessor(char* file);

    /*!
     * \brief outputs the content of the document number passed as an argument
     * \param documentNumber an integer
     */
    void getDocumentContents(int documentNumber);

};

#endif // QUERYPROCESSOR_H
