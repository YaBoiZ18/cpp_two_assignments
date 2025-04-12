#pragma once
#include "Book.hpp"
#include "User.hpp"
#include <unordered_map>
#include <vector>

class Library {
public:
    // Adds a new book to the library collection.
    // Returns true if the book was successfully added, false if a book with the same ISBN already exists.
    bool addBook(const Book& book);

    // Removes a book from the library collection by its ISBN.
    // Returns true if the book was found and removed, false otherwise.
    bool removeBook(const std::string& isbn);

    // Searches for books by their title.
    // Returns a vector of books that match the given title.
    std::vector<Book> searchByTitle(const std::string& title) const;

    // Searches for books by their author.
    // Returns a vector of books that match the given author.
    std::vector<Book> searchByAuthor(const std::string& author) const;

    // Searches for a book by its ISBN.
    // Returns a pointer to the Book if found, or nullptr if not found.
    Book* searchByISBN(const std::string& isbn);

    // Displays all books in the library collection to the console or log.
    void displayBooks() const;

    // Adds a new user to the library system.
    // Returns true if the user was successfully added, false if a user with the same ID already exists.
    bool addUser(const User& user);

    // Removes a user from the library system by their ID.
    // Returns true if the user was found and removed, false otherwise.
    bool removeUser(const std::string& id);

    // Allows a user to borrow a book by ISBN.
    // Returns true if both user and book exist and the operation is successful.
    bool borrowBook(const std::string& userId, const std::string& isbn);

    // Allows a user to return a previously borrowed book by ISBN.
    // Returns true if the operation is successful.
    bool returnBook(const std::string& userId, const std::string& isbn);

    // Loads books and users from specified files.
    // Returns true if both files were loaded successfully.
    bool loadFromFiles(const std::string& bookFile, const std::string& userFile);

    // Saves books and users to specified files.
    // Returns true if both files were saved successfully.
    bool saveToFiles(const std::string& bookFile, const std::string& userFile) const;

private:
    std::unordered_map<std::string, Book> books_;  // Maps ISBN to Book objects.
    std::unordered_map<std::string, User> users_;  // Maps user ID to User objects.
};