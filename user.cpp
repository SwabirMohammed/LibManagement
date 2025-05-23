#include <iostream>
#include "User.h" 
#include "LibraryException.h" // Error handling header
#include <algorithm> // Required for std::remove

// Constructor for the User class.
// Initializes userID and name. The borrowedItems vector is initially empty.
User::User(const std::string& id, const std::string& n) : userID(id), name(n) {}

// Method to add an itemID to the user's list of borrowed items.
// Throws LibraryException if the item is already in the borrowed list.
void User::borrowItem(const std::string& itemID) {
    // Check if the item is already borrowed by this user
    for (const std::string& id : borrowedItems) {
        if (id == itemID) {
            throw LibraryException("User has already borrowed this item.");
        }
    }
    borrowedItems.push_back(itemID); // Add the item to the list
}

// Method to remove an itemID from the user's list of borrowed items.
// Throws LibraryException if the item was not found in the borrowed list.
void User::returnItem(const std::string& itemID) {
    // Find the item in the borrowedItems vector
    auto it = std::remove(borrowedItems.begin(), borrowedItems.end(), itemID);
    if (it == borrowedItems.end()) {
        // If the item was not found, throw an exception
        throw LibraryException("User did not borrow this item.");
    }
    borrowedItems.erase(it, borrowedItems.end()); // Remove the item from the vector
}

// Displays all items currently borrowed by the user.
void User::listBorrowedItems() const {
    if (borrowedItems.empty()) {
        std::cout << "  No items borrowed." << std::endl;
        return;
    }
    std::cout << "  Borrowed Items:" << std::endl;
    for (const std::string& id : borrowedItems) {
        std::cout << "    - " << id << std::endl;
    }
}

// Returns the user's ID.
std::string User::getID() const {
    return userID;
}

// Overloaded equality operator to compare two User objects based on their userID
bool User::operator==(const User& other) const {
    return userID == other.userID;
}

// Returning the user's name
std::string User::getName() const {
    return name;
}