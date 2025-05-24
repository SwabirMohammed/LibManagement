#include "Book.h"   // Include its own header
#include <iostream> // For std::cout

// Constructor definition
Book::Book(const std::string &id, const std::string &t, const std::string &a, const std::string &g, bool borrowed)
    : LibraryItem(id, t, a), genre(g), isBorrowed(borrowed) {}

// Method definitions
void Book::display() const
{
  std::cout << "[Book] ID: " << itemID << std::endl;
  std::cout << ", Title: " << title << std::endl;
  std::cout << ", Author: " << author << std::endl;
  std::cout << ", Genre: " << genre << std::endl;
  std::cout << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << std::endl;
}

bool Book::getStatus() const
{
  return isBorrowed;
}

void Book::borrowItem()
{
  if (isBorrowed)
  {
    throw std::runtime_error("Book has already been borrowed");
  }
  isBorrowed = true;
}

void Book::returnBack()
{
  if (!isBorrowed)
  {
    throw std::runtime_error("Book was not borrowed!");
  }
  isBorrowed = false;
}