#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
private:
    std::string userID;
    std::string name;
    std::vector<std::string> borrowedItems;

public:
    User(const std::string& id, const std::string& n);

    void borrowItem(const std::string& itemID);
    void returnItem(const std::string& itemID);
    void listBorrowedItems() const;

    std::string getID() const;
    std::string getName() const;

    bool operator==(const User& other) const;
};

#endif // USER_H
