#include "LibrarySystem.h"
#include <fstream>
#include <chrono>
#include <iomanip>

LibrarySystem::~LibrarySystem()
{
    for (auto &pair : items)
    {
        delete pair.second;
    }
}

void LibrarySystem::addItem(LibraryItem *item)
{
    if (items.find(item->getID()) != items.end())
    {
        delete item;
        throw LibraryException("Item " + item->getID() + " already exists.");
    }
    items[item->getID()] = item;
    logTransaction("Added item", "SYSTEM", item->getID());
}

void LibrarySystem::addUser(const User &user)
{
    if (users.find(user.getID()) != users.end())
    {
        throw LibraryException("User " + user.getID() + " already exists.");
    }
    users.insert({user.getID(), user});
    logTransaction("Added user", user.getID(), "");
}

void LibrarySystem::borrowItem(const std::string &userID, const std::string &itemID)
{
    auto userIt = users.find(userID);
    if (userIt == users.end())
    {
        throw LibraryException("User " + userID + " does not exist.");
    }
    auto itemIt = items.find(itemID);
    if (itemIt == items.end())
    {
        throw LibraryException("Item " + itemID + " does not exist.");
    }
    Book *book = dynamic_cast<Book *>(itemIt->second);
    if (!book)
    {
        throw LibraryException("Item " + itemID + " is a magazine and cannot be borrowed.");
    }
    try
    {
        book->borrowItem();
        userIt->second.borrowItem(itemID);
        logTransaction("Borrowed", userID, itemID);
    }
    catch (const LibraryException &e)
    {
        logTransaction("Failed to borrow", userID, itemID);
        throw;
    }
}

void LibrarySystem::returnItem(const std::string &userID, const std::string &itemID)
{
    auto userIt = users.find(userID);
    if (userIt == users.end())
    {
        throw LibraryException("User " + userID + " does not exist.");
    }
    auto itemIt = items.find(itemID);
    if (itemIt == items.end())
    {
        throw LibraryException("Item " + itemID + " does not exist.");
    }
    Book *book = dynamic_cast<Book *>(itemIt->second);
    if (!book)
    {
        throw LibraryException("Item " + itemID + " is a magazine and cannot be returned.");
    }
    try
    {
        book->returnBack();
        userIt->second.returnItem(itemID);
        logTransaction("Returned", userID, itemID);
    }
    catch (const LibraryException &e)
    {
        logTransaction("Failed to return", userID, itemID);
        throw;
    }
}

void LibrarySystem::displayAllItems() const
{
    if (items.empty())
    {
        std::cout << "No items in the library." << std::endl;
    }
    else
    {
        for (const auto &pair : items)
        {
            pair.second->display();
        }
    }
    logTransaction("Viewed all items", "SYSTEM", "");
}

void LibrarySystem::displayAllUsers() const
{
    if (users.empty())
    {
        std::cout << "No users registered." << std::endl;
    }
    else
    {
        for (const auto &pair : users)
        {
            pair.second.listBorrowedItems();
        }
    }
    logTransaction("Viewed all users", "SYSTEM", "");
}

void LibrarySystem::logTransaction(const std::string &action, const std::string &userID, const std::string &itemID) const
{
    std::ofstream logFile("logs/transactions.txt", std::ios::app);
    if (!logFile.is_open())
    {
        throw LibraryException("Failed to open log file.");
    }
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    logFile << "[" << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << "] ";

    if (userID == "SYSTEM")
    {
        logFile << "System " << action;
    }
    else
    {
        auto userIt = users.find(userID);
        std::string userName = userIt != users.end() ? userIt->second.getID() : "Unknown";
        logFile << "User: " << userID << " (" << userName << ") " << action;
    }

    if (!itemID.empty())
    {
        auto itemIt = items.find(itemID);
        std::string itemTitle = itemIt != items.end() ? itemIt->second->getTitle() : "Unknown";
        logFile << " Item: " << itemID << " - \"" << itemTitle << "\"";
    }
    logFile << std::endl;
    logFile.close();
}