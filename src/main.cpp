#include "LibrarySystem.h"
#include <iostream>
#include <limits>

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    LibrarySystem library;
    int choice;
    
    while (true) {
        std::cout << "\nLibrary Management System\n"
                  << "1. Add Book\n"
                  << "2. Add Magazine\n"
                  << "3. Add User\n"
                  << "4. Borrow Book\n"
                  << "5. Return Book\n"
                  << "6. View All Items\n"
                  << "7. View All Users\n"
                  << "8. Exit\n"
                  << "Enter choice: ";
        
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInputBuffer();
            continue;
        }
        
        try {
            switch (choice) {
                case 1: {
                    std::string id, title, author, genre;
                    clearInputBuffer();
                    std::cout << "Enter Book ID: ";
                    std::getline(std::cin, id);
                    std::cout << "Enter Title: ";
                    std::getline(std::cin, title);
                    std::cout << "Enter Author: ";
                    std::getline(std::cin, author);
                    std::cout << "Enter Genre: ";
                    std::getline(std::cin, genre);
                    library.addItem(new Book(id, title, author, genre));
                    std::cout << "Book added successfully.\n";
                    break;
                }
                case 2: {
                    std::string id, title, author, month;
                    int issue;
                    clearInputBuffer();
                    std::cout << "Enter Magazine ID: ";
                    std::getline(std::cin, id);
                    std::cout << "Enter Title: ";
                    std::getline(std::cin, title);
                    std::cout << "Enter Author: ";
                    std::getline(std::cin, author);
                    std::cout << "Enter Issue Number: ";
                    if (!(std::cin >> issue)) {
                        throw LibraryException("Invalid issue number.");
                    }
                    clearInputBuffer();
                    std::cout << "Enter Month: ";
                    std::getline(std::cin, month);
                    library.addItem(new Magazine(id, title, author, issue, month));
                    std::cout << "Magazine added successfully.\n";
                    break;
                }
                case 3: {
                    std::string id, name;
                    clearInputBuffer();
                    std::cout << "Enter User ID: ";
                    std::getline(std::cin, id);
                    std::cout << "Enter Name: ";
                    std::getline(std::cin, name);
                    library.addUser(User(id, name));
                    std::cout << "User added successfully.\n";
                    break;
                }
                case 4: {
                    std::string userID, itemID;
                    clearInputBuffer();
                    std::cout << "Enter User ID: ";
                    std::getline(std::cin, userID);
                    std::cout << "Enter Book ID: ";
                    std::getline(std::cin, itemID);
                    library.borrowItem(userID, itemID);
                    std::cout << "Book borrowed successfully.\n";
                    break;
                }
                case 5: {
                    std::string userID, itemID;
                    clearInputBuffer();
                    std::cout << "Enter User ID: ";
                    std::getline(std::cin, userID);
                    std::cout << "Enter Book ID: ";
                    std::getline(std::cin, itemID);
                    library.returnItem(userID, itemID);
                    std::cout << "Book returned successfully.\n";
                    break;
                }
                case 6:
                    library.displayAllItems();
                    break;
                case 7:
                    library.displayAllUsers();
                    break;
                case 8:
                    std::cout << "Exiting...\n";
                    return 0;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        } catch (const LibraryException& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "An unexpected error occurred.\n";
        }
    }
    return 0;
}