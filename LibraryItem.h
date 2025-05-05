#ifndef LIBRARY_ITEM_H
#define LIBRARY_ITEM_H

#include <string>
#include <iostream>

class LibraryItem {
protected:
    std::string itemID;
    std::string title;
    std::string author;


public:
    LibraryItem(const std::string& id, const std::string& t, const std::string& a) : itemID(id), title(t), author(a) {}
    virtual ~LibraryItem(){}; // Virtual to support polymorphic deletion

    virtual void display() const = 0; // Polymorphic display function

    std::string getID() const {return itemID;}
    std::string getTitle() const {return title;}
    std::string getAuthor() const {return author;}


    friend std::ostream& operator<<(std::ostream& os, const LibraryItem& item) {
        item.display();
        return os;
    }
};

#endif // LIBRARY_ITEM_H
