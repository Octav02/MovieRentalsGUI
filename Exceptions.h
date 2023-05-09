#pragma once
#include <string>
#include <utility>

using namespace std;

class ValidationException {
private:
    std::string message;
public:
    ValidationException(std::string message) : message{std::move(message)} {}
    string what() const { return message; }
    friend std::ostream &operator<<(std::ostream &os, const ValidationException &exception);
};

class RepositoryException {
private:
    std::string message;
public:
    RepositoryException(std::string message) : message{std::move(message)} {}
    string what() const { return message; }
    friend std::ostream &operator<<(std::ostream &os, const RepositoryException &exception);

};