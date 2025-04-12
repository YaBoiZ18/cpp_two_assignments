#pragma once
#include <string>
#include <vector>

class User {
public:
    // Constructor to initialize a User with a name and unique ID.
    User(std::string name, std::string id);

    // Returns the name of the user.
    const std::string& getName() const;

    // Returns the unique ID of the user.
    const std::string& getId() const;

    // Records that the user has borrowed a book identified by its ISBN.
    void borrowBook(const std::string& isbn);

    // Records that the user has returned a book identified by its ISBN.
    void returnBook(const std::string& isbn);

    // Returns a list of ISBNs for books currently borrowed by the user.
    const std::vector<std::string>& getBorrowedBooks() const;

private:
    std::string name_;                   // The name of the user.
    std::string id_;                     // The unique identifier for the user.
    std::vector<std::string> borrowedBooks_;  // A list of ISBNs representing the books borrowed by the user.
};