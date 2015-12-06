// Owners: Wesley and Charlie
// file history:
// https://github.com/SMUCSE2341/BSSearch/commits/DocumentParser/userinterface.h

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>

#include "documentparser.h"
#include "indexhandler.h"

/*!
 * \class The UserInterface class
 *
 * Allows the user to choose maintenance mode or interactive mode.
 *
 * In maintenance the user can add a document to the index by supplying the
 * file path to a properly formatted xml document. The user can also clear the
 * index completely.
 *
 * In interactive mode the user indicate whether they want the index loaded into
 * the avl tree or hash table, allow the user to enter a properly formatted
 * query, and print out the total number of pages indexed, total number of
 * words indexed, and the top 50 words.
 */
class UserInterface
{
private:
    DocumentParser* docParser;
    IndexHandler* ih;
    int select;
    bool avlTree;
    std::string searchWords;
    char* xmlFile;

    /*!
     * \brief interactiveMode asks the user if they want to load the index into
     * the avl tree or hash table, and if they want to enter a query.
     */
    void interactiveMode();

    /*!
     * \brief maintenanceMode asks the user if they want to add a document to
     * the index or clear the index.
     */
    void maintenanceMode();

    void boolExpression();

public:
    /*!
     * \brief UserInterface default constructor
     */
    UserInterface();

    /*!
     * \brief UserInterface overloaded constructor
     * \param xmlFilename a character pointer that contains the xml filename
     */
    UserInterface(char*& xmlFilename);

    /*!
     * \brief UserInterface destructor
     */
    ~UserInterface();

    /*!
     * \brief startScreen asks the user if they want to enter Maintenance Mode,
     * Interactive Mode, or exit the program.
     */
    void startScreen();
};

#endif // USERINTERFACE_H