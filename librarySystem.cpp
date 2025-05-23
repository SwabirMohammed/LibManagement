#include <iostream>
#include "LibrarySystem.h" 
#include <fstream> 
#include <chrono> // Required for getting current time for logging
#include <iomanip>

// Destructor for LibrarySystem
LibrarySystem::~LibrarySystem() {
    for (auto const& [key, val] : items) {
        delete val; // Delete the dynamically allocated LibraryItem
    }
}

void LibrarySystem::addItem(LibraryItem* item) {
    if (items.count(item->getID())) {
        delete item; // Prevent memory leak if item already exists
        throw LibraryException("Item with this ID already exists.");
    }
    items[item->getID()] = item; // Add the item to the map
    std::cout << "Item '" << item->getTitle() << "' (ID: " << item->getID() << ") added successfully." << std::endl;
}

// Adds a new User to the system.
// Throws LibraryException if a user with the same ID already exists.
void LibrarySystem::addUser(const User& user) {
    if (users.count(user.getID())) {
        throw LibraryException("User with this ID already exists.");
    }
    users[user.getID()] = user; // Add the user to the map
    std::cout << "User '" << user.getName() << "' (ID: " << user.getID() << ") added successfully." << std::endl;
}

// Handles the borrowing of an item by a user.
// Validates user and item existence, checks if the item is a Book,
// and updates statuses. Logs the transaction.
void LibrarySystem::borrowItem(const std::string& userID, const std::string& itemID) {
    // Check if user exists
    if (users.find(userID) == users.end()) {
        logTransaction("Borrow", userID, itemID, "FAILED (User not found)");
        throw LibraryException("User not found.");
    }
    User& user = users.at(userID); // Get reference to the user

    // Check if item exists
    if (items.find(itemID) == items.end()) {
        logTransaction("Borrow", userID, itemID, "FAILED (Item not found)");
        throw LibraryException("Item not found.");
    }
    LibraryItem* item = items.at(itemID); // Get pointer to the item

    // Attempt to dynamically cast to Book. Only books can be borrowed.
    Book* book = dynamic_cast<Book*>(item);
    if (!book) {
        logTransaction("Borrow", userID, itemID, "FAILED (Not a borrowable item)");
        throw LibraryException("Only books can be borrowed.");
    }

    try {
        book->borrowItem(); // Mark book as borrowed (throws if already borrowed)
        user.borrowItem(itemID); // Add item to user's borrowed list (throws if already borrowed by user)
        logTransaction("Borrow", userID, itemID, "SUCCESS");
        std::cout << "User '" << user.getName() << "' borrowed Book '" << book->getTitle() << "' successfully." << std::endl;
    } catch (const LibraryException& e) {
        logTransaction("Borrow", userID, itemID, std::string("FAILED (") + e.what() + ")");
        throw; // Re-throw the exception after logging
    }
}

// Handles the returning of an item by a user.
// Validates user and item existence, checks if the item is a Book,
// and updates statuses. Logs the transaction.
void LibrarySystem::returnItem(const std::string& userID, const std::string& itemID) {
    // Check if user exists
    if (users.find(userID) == users.end()) {
        logTransaction("Return", userID, itemID, "FAILED (User not found)");
        throw LibraryException("User not found.");
    }
    User& user = users.at(userID); // Get reference to the user

    // Check if item exists
    if (items.find(itemID) == items.end()) {
        logTransaction("Return", userID, itemID, "FAILED (Item not found)");
        throw LibraryException("Item not found.");
    }
    LibraryItem* item = items.at(itemID); // Get pointer to the item

    // Attempt to dynamically cast to Book. Only books can be returned.
    Book* book = dynamic_cast<Book*>(item);
    if (!book) {
        logTransaction("Return", userID, itemID, "FAILED (Not a borrowable item)");
        throw LibraryException("Only books can be returned.");
    }

    try {
        book->returnBack(); // Mark book as returned (throws if not borrowed)
        user.returnItem(itemID); // Remove item from user's borrowed list (throws if not borrowed by user)
        logTransaction("Return", userID, itemID, "SUCCESS");
        std::cout << "User '" << user.getName() << "' returned Book '" << book->getTitle() << "' successfully." << std::endl;
    } catch (const LibraryException& e) {
        logTransaction("Return", userID, itemID, std::string("FAILED (") + e.what() + ")");
        throw; // Re-throw the exception after logging
    }
}

// Displays details of all items currently in the library system.
void LibrarySystem::displayAllItems() const {
    if (items.empty()) {
        std::cout << "No items in the library." << std::endl;
        return;
    }
    std::cout << "\n--- All Library Items ---" << std::endl;
    for (auto const& [id, item] : items) {
        item->display(); // Polymorphic call to display
    }
    std::cout << "-------------------------" << std::endl;
}

// Displays details of all registered users in the system, including their borrowed items.
void LibrarySystem::displayAllUsers() const {
    if (users.empty()) {
        std::cout << "No users registered in the system." << std::endl;
        return;
    }
    std::cout << "\n--- All Registered Users ---" << std::endl;
    for (auto const& [id, user] : users) {
        std::cout << "User ID: " << user.getID() << ", Name: " << user.getName() << std::endl;
        user.listBorrowedItems(); // Display items borrowed by this user
    }
    std::cout << "----------------------------" << std::endl;
}

// Logs a transaction to the "logs/transactions.txt" file.
// Includes timestamp, action, user details, item details, and status.
void LibrarySystem::logTransaction(const std::string& action, const std::string& userID, const std::string& itemID, const std::string& status) const {
    std::ofstream logFile("logs/transactions.txt", std::ios_base::app); // Open in append mode
    if (!logFile.is_open()) {
        std::cerr << "Error: Could not open transactions log file." << std::endl;
        return;
    }

    // Get current time
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // Format time
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");

    std::string userName = "N/A";
    if (users.count(userID)) {
        userName = users.at(userID).getName();
    }

    std::string itemTitle = "N/A";
    if (items.count(itemID)) {
        itemTitle = items.at(itemID)->getTitle();
    }

    // Write to log file
    logFile << "[" << ss.str() << "] User: " << userID << " (" << userName << ") "
            << action << " Item: " << itemID << " - \"" << itemTitle << "\" - " << status << std::endl;
    logFile.close();
}
