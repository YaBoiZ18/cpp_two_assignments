#include "User.hpp"
#include <algorithm>

// Constructor initializes a User with the given name and ID.
User::User(std::string name, std::string id)
    : name_(std::move(name)), id_(std::move(id)) {}

// Returns the name of the user.
const std::string& User::getName() const { return name_; }

// Returns the unique ID of the user.
const std::string& User::getId() const { return id_; }

// Returns a reference to the list of ISBNs for books currently borrowed by the user.
const std::vector<std::string>& User::getBorrowedBooks() const { return borrowedBooks_; }

// Adds the given ISBN to the list of borrowed books.
void User::borrowBook(const std::string& isbn) {
    borrowedBooks_.push_back(isbn);
}

// Removes the given ISBN from the list of borrowed books if present.
// Uses std::remove and vector::erase to safely remove all matching entries.
void User::returnBook(const std::string& isbn) {
    borrowedBooks_.erase(
        std::remove(borrowedBooks_.begin(), borrowedBooks_.end(), isbn),
        borrowedBooks_.end()
    );
}