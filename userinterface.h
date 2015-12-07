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
 * In interactive mode the user indicates whether they want to enter a properly
 * formatted query, and print out the total number of pages indexed and total
 * number of words indexed.
 */
class UserInterface
{
private:
    /*!
     * \var docParser a pointer to a DocumentParser object.
     */
    DocumentParser* docParser;

    /*!
     * \var ih a pointer to an IndexHandler object.
     */
    IndexHandler* ih;

    /*!
     * \var select an integer containing the user choices from the menu.
     */
    int select;

    /*!
     * \var searchWords a string containing the user's search query.
     */
    std::string searchWords;

    /*!
     * \var xmlFile a character pointer containing an xml filename.
     */
    char* xmlFile;

    /*!
     * \brief interactiveMode asks the user if they want to enter a query or
     * print the search engine statistics.
     */
    void interactiveMode();

    /*!
     * \brief maintenanceMode asks the user if they want to add a document to
     * the index or clear the index.
     */
    void maintenanceMode();

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