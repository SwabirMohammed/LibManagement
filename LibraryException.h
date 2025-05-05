#ifndef LIBRARY_EXCEPTION_H
#define LIBRARY_EXCEPTION_H

#include <exception>
#include <string>

class LibraryException : public std::exception {
private:
    std::string message;

public:
    LibraryException(const std::string& msg);
    const char* what() const noexcept override;
};

#endif // LIBRARY_EXCEPTION_H
