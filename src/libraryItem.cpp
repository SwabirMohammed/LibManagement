#include "LibraryItem.h"

// Constructor definition
LibraryItem::LibraryItem(const std::string &id, const std::string &t, const std::string &a)
    : itemID(id), title(t), author(a) {}

// Method definitions
std::string LibraryItem::getID() const
{
    return itemID;
}

std::string LibraryItem::getTitle() const
{
    return title;
}

std::string LibraryItem::getAuthor() const
{
    return author;
}