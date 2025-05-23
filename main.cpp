#include <iostream> 
#include <limits>   
#include <string>   
#include "LibrarySystem.h" 
#include "Book.h"          
#include "Magazine.h"     
#include "User.h"          
#include "LibraryException.h" 

// Function to clear the input buffer.
// This is necessary after reading numbers with cin to prevent issues with subsequent getline calls.
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    LibrarySystem myLibrary; // Create an instance of the LibrarySystem

    int choice; // Variable to store user's menu choice

    // Initial data setup (optional, for testing purposes)
    try {
        myLibrary.addItem(new Book("B001", "The Great Gatsby", "F. Scott Fitzgerald", "Classic"));
        myLibrary.addItem(new Magazine("M001", "National Geographic", "Various", 123, "May"));
        myLibrary.addUser(User("U001", "Alice Smith"));
        myLibrary.addUser(User("U002", "Bob Johnson"));
    } catch (const LibraryException& e) {
        std::cerr << "Initialization Error: " << e.what() << std::endl;
    }


    do {
        // Display the main menu to the user
        std::cout << "\n--- Library Management System ---" << std::endl;
        std::cout << "1: Add Book" << std::endl;
        std::cout << "2: Add Magazine" << std::endl;
        std::cout << "3: Add User" << std::endl;
        std::cout << "4: Borrow Book" << std::endl;
        std::cout << "5: Return Book" << std::endl;
        std::cout << "6: View All Items" << std::endl;
        std::cout << "7: View All Users" << std::endl;
        std::cout << "8: Exit" << std::endl;
        std::cout << "Enter your choice: ";

        // Read user's choice
        std::cin >> choice;

        // Check for invalid input (non-integer)
        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // Clear error flags
            clearInputBuffer(); // Clear the invalid input from the buffer
            continue; // Go back to the beginning of the loop
        }
        clearInputBuffer(); // Clear the newline character after reading the integer

        // Process user's choice using a switch statement
        switch (choice) {
            case 1: { // Add Book
                std::string id, title, author, genre;
                std::cout << "Enter Book ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter Title: ";
                std::getline(std::cin, title);
                std::cout << "Enter Author: ";
                std::getline(std::cin, author);
                std::cout << "Enter Genre: ";
                std::getline(std::cin, genre);
                try {
                    myLibrary.addItem(new Book(id, title, author, genre));
                } catch (const LibraryException& e) {
                    std::cerr << "Error adding book: " << e.what() << std::endl;
                }
                break;
            }
            case 2: { // Add Magazine
                std::string id, title, author, month;
                int issueNumber;
                std::cout << "Enter Magazine ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter Title: ";
                std::getline(std::cin, title);
                std::cout << "Enter Author: ";
                std::getline(std::cin, author);
                std::cout << "Enter Issue Number: ";
                std::cin >> issueNumber;
                if (std::cin.fail()) {
                    std::cout << "Invalid input for issue number." << std::endl;
                    std::cin.clear();
                    clearInputBuffer();
                    break; // Exit this case
                }
                clearInputBuffer();
                std::cout << "Enter Month: ";
                std::getline(std::cin, month);
                try {
                    myLibrary.addItem(new Magazine(id, title, author, issueNumber, month));
                } catch (const LibraryException& e) {
                    std::cerr << "Error adding magazine: " << e.what() << std::endl;
                }
                break;
            }
            case 3: { // Add User
                std::string id, name;
                std::cout << "Enter User ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter User Name: ";
                std::getline(std::cin, name);
                try {
                    myLibrary.addUser(User(id, name));
                } catch (const LibraryException& e) {
                    std::cerr << "Error adding user: " << e.what() << std::endl;
                }
                break;
            }
            case 4: { // Borrow Book
                std::string userID, itemID;
                std::cout << "Enter User ID: ";
                std::getline(std::cin, userID);
                std::cout << "Enter Item ID to borrow: ";
                std::getline(std::cin, itemID);
                try {
                    myLibrary.borrowItem(userID, itemID);
                } catch (const LibraryException& e) {
                    std::cerr << "Error borrowing item: " << e.what() << std::endl;
                }
                break;
            }
            case 5: { // Return Book
                std::string userID, itemID;
                std::cout << "Enter User ID: ";
                std::getline(std::cin, userID);
                std::cout << "Enter Item ID to return: ";
                std::getline(std::cin, itemID);
                try {
                    myLibrary.returnItem(userID, itemID);
                } catch (const LibraryException& e) {
                    std::cerr << "Error returning item: " << e.what() << std::endl;
                }
                break;
            }
            case 6: { // View All Items
                myLibrary.displayAllItems();
                break;
            }
            case 7: { // View All Users
                myLibrary.displayAllUsers();
                break;
            }
            case 8: { // Exit
                std::cout << "Exiting Library Management System. Goodbye!" << std::endl;
                break;
            }
            default: { // Invalid Option
                std::cout << "You have selected an invalid option. Please try again." << std::endl;
                break;
            }
        }
    } while (choice != 8); // Loop until user chooses to exit

    return 0; // Indicate successful execution
}