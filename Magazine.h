#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "LibraryItem.h"

class Magazine : public LibraryItem {
private:
    int issueNumber;
    std::string month;

public:
    Magazine(const std::string& id, const std::string& t, const std::string& a, int issue, const std::string& m);

    void display() const override;
};

#endif // MAGAZINE_H
