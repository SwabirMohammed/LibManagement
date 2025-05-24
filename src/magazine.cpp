#include "Magazine.h"

Magazine::Magazine(const std::string& id, const std::string& t, const std::string& a, int issue, const std::string& m)
    : LibraryItem(id, t, a), issueNumber(issue), month(m) {}

void Magazine::display() const {
    std::cout << "Magazine: " << itemID << " - \"" << title << "\" by " << author
              << ", Issue: " << issueNumber << ", Month: " << month << std::endl;
}

std::string Magazine::getTitle() const {
    return title;
}