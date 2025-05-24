#ifndef LIBRARY_ITEM_H
#define LIBRARY_ITEM_H

#include <string>
#include <iostream>

class LibraryItem
{
protected:
    std::string itemID;
    std::string title;
    std::string author;

public:
    LibraryItem(const std::string &id, const std::string &t, const std::string &a);
    virtual ~LibraryItem() = default; // Explicitly defaulted in header, no .cpp definition needed

    virtual void display() const = 0; // Pure virtual

    // Make these methods virtual so derived classes can override them if needed,
    // and to satisfy the 'override' keyword usage in derived classes like Magazine.
    virtual std::string getID() const;
    virtual std::string getTitle() const;
    virtual std::string getAuthor() const;

    friend std::ostream &operator<<(std::ostream &os, const LibraryItem &item)
    {
        item.display();
        return os;
    }
};

#endif // LIBRARY_ITEM_H