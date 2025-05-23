#include "Magazine.h" // Include the header file for Magazine
#include <iostream> // Required for std::cout

// Constructor for the Magazine class.
// Initializes the base class LibraryItem with ID, title, and author.
// Also initializes issueNumber and month specific to Magazine.
Magazine::Magazine(const std::string& id, const std::string& t, const std::string& a, int issue, const std::string& m)
    : LibraryItem(id, t, a), issueNumber(issue), month(m) {}

// Override the display method from LibraryItem to show Magazine-specific details.
void Magazine::display() const {
    std::cout << "[Magazine] ID: " << itemID
              << ", Title: " << title
              << ", Author: " << author
              << ", Issue: " << issueNumber
              << ", Month: " << month << std::endl;
}

