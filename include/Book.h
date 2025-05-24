#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include "LibraryItem.h"

class Book : public LibraryItem
{
private:
    std::string genre;
    bool isBorrowed;

public:
    Book(const std::string &id, const std::string &t, const std::string &a, const std::string &g, bool borrowed = false);

    void display() const override;

    bool getStatus() const;

    void borrowItem();

    void returnBack();
};

#endif // BOOK_H