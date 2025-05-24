#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include "LibraryItem.h"
#include "Book.h"
#include "Magazine.h"
#include "User.h"
#include "LibraryException.h"

#include <map>
#include <string>

class LibrarySystem {
private:
    std::map<std::string, LibraryItem*> items;
    std::map<std::string, User> users;

public:
    ~LibrarySystem();

    void addItem(LibraryItem* item);
    void addUser(const User& user);

    void borrowItem(const std::string& userID, const std::string& itemID);
    void returnItem(const std::string& userID, const std::string& itemID);

    void displayAllItems() const;
    void displayAllUsers() const;

    void logTransaction(const std::string& action, const std::string& userID, const std::string& itemID) const; // Restored const
};

#endif // LIBRARY_SYSTEM_H