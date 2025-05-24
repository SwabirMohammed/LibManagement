#include "User.h"
#include "LibraryException.h"
#include <iostream>
#include <algorithm>

User::User(const std::string& id, const std::string& n) : userID(id), name(n) {}

void User::borrowItem(const std::string& itemID) {
    for (const auto& item : borrowedItems) {
        if (item == itemID) {
            throw LibraryException("User " + userID + " has already borrowed item " + itemID + ".");
        }
    }
    borrowedItems.push_back(itemID);
}

void User::returnItem(const std::string& itemID) {
    auto it = std::find(borrowedItems.begin(), borrowedItems.end(), itemID);
    if (it == borrowedItems.end()) {
        throw LibraryException("User " + userID + " has not borrowed item " + itemID + ".");
    }
    borrowedItems.erase(it);
}

void User::listBorrowedItems() const {
    std::cout << "Borrowed items for " << name << " (" << userID << "): ";
    if (borrowedItems.empty()) {
        std::cout << "None" << std::endl;
    } else {
        for (const auto& item : borrowedItems) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
}

std::string User::getID() const {
    return userID;
}

bool User::operator==(const User& other) const {
    return userID == other.userID;
}