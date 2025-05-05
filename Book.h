#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include "LibraryItem.h"

class Book : public LibraryItem {
private:
    std::string genre;
    bool isBorrowed;

public:
    Book(const std::string& id, const std::string& t, const std::string& a, const std::string& g, bool borrowed = false) : LibraryItem(id, t, a), isBorrowed(false) {}

    void display() const override;

    bool getStatus() const{
        return isBorrowed;
    }

    void borrowItem() override{

        if (isBorrowed)
        {
            throw std::runtime_error("Book has already been borrowed");
        }
        isBorrowed = true;
    }

    void returnBack() {

        if (!isBorrowed)
        {
            throw std::runtime_error("Book was not borrowed!");
        }
        isBorrowed = false;
    }
};

#endif // BOOK_H
