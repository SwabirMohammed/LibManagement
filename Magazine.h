#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "LibraryItem.h"

class Magazine : public LibraryItem {
private:
    int issueNumber;
    std::string month;

public:
    Magazine(const std::string& id, const std::string& t, const std::string& a, int issue, const std::string& m);

    void display() const {
        std::cout << "[Magazine] ID: " << itemID
        << "Title: " << title 
        << "Author: " << author
        << "Issue: " << issueNumber 
        << "Month: " << month << std::endl;
    }
};

#endif // MAGAZINE_H
