#include "Library.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

// Adds a book to the library if the ISBN doesn't already exist.
// Returns true if added successfully, false if the book already exists.
bool Library::addBook(const Book& book) {
    if (books_.count(book.getISBN()) > 0)
        return false;
    books_.emplace(book.getISBN(), book);
    return true;
}

// Removes a book from the library by ISBN.
// Returns true if the book was found and removed.
bool Library::removeBook(const std::string& isbn) {
    return books_.erase(isbn) > 0;
}

// Searches for books matching the given title.
// Returns a vector of matching Book objects.
std::vector<Book> Library::searchByTitle(const std::string& title) const {
    std::vector<Book> results;
    for (const auto& [isbn, book] : books_) {
        if (book.getTitle() == title) {
            results.push_back(book);
        }
    }
    return results;
}

// Searches for books matching the given author.
// Returns a vector of matching Book objects.
std::vector<Book> Library::searchByAuthor(const std::string& author) const {
    std::vector<Book> results;
    for (const auto& [isbn, book] : books_) {
        if (book.getAuthor() == author) {
            results.push_back(book);
        }
    }
    return results;
}

// Searches for a book by its ISBN.
// Returns a pointer to the Book if found, or nullptr if not.
Book* Library::searchByISBN(const std::string& isbn) {
    auto it = books_.find(isbn);
    return (it != books_.end()) ? &it->second : nullptr;
}

// Prints the list of all books in the library to standard output.
void Library::displayBooks() const {
    for (const auto& [isbn, book] : books_) {
        std::cout << "Title: " << book.getTitle()
            << ", Author: " << book.getAuthor()
            << ", ISBN: " << book.getISBN()
            << ", Quantity: " << book.getQuantity()
            << "\n";
    }
}

// Adds a user to the library system if their ID doesn't already exist.
// Returns true if added successfully, false if the user already exists.
bool Library::addUser(const User& user) {
    if (users_.count(user.getId()) > 0)
        return false;
    users_.emplace(user.getId(), user);
    return true;
}

// Removes a user from the library system by ID.
// Returns true if the user was found and removed.
bool Library::removeUser(const std::string& id) {
    return users_.erase(id) > 0;
}

// Allows a user to borrow a book by ISBN if both exist and a copy is available.
// Returns true if the operation succeeds, false otherwise.
bool Library::borrowBook(const std::string& userId, const std::string& isbn) {
    auto userIt = users_.find(userId);
    auto bookIt = books_.find(isbn);
    if (userIt == users_.end() || bookIt == books_.end()) {
        return false;
    }

    try {
        bookIt->second.borrow();
        userIt->second.borrowBook(isbn);
        return true;
    }
    catch (const std::runtime_error&) {
        return false;
    }
}

// Allows a user to return a previously borrowed book by ISBN.
// Returns true if the operation succeeds, false if the user or book wasn't found.
bool Library::returnBook(const std::string& userId, const std::string& isbn) {
    auto userIt = users_.find(userId);
    auto bookIt = books_.find(isbn);
    if (userIt == users_.end() || bookIt == books_.end()) {
        return false;
    }

    userIt->second.returnBook(isbn);
    bookIt->second.returnCopy();
    return true;
}

// Loads books and users from the given files.
// Books and users must follow the expected format:
// Books: title;author;isbn;quantity
// Users: name;id;isbn1,isbn2,...
// Returns true if both files were loaded successfully.
bool Library::loadFromFiles(const std::string& bookFile, const std::string& userFile) {
    std::ifstream bf(bookFile);
    std::ifstream uf(userFile);
    if (!bf.is_open() || !uf.is_open())
        return false;

    books_.clear();
    users_.clear();

    std::string line;

    // Load books from file.
    while (std::getline(bf, line)) {
        std::stringstream ss(line);
        std::string title, author, isbn;
        int quantity;
        if (std::getline(ss, title, ';') &&
            std::getline(ss, author, ';') &&
            std::getline(ss, isbn, ';') &&
            (ss >> quantity)) {
            books_.emplace(isbn, Book(title, author, isbn, quantity));
        }
    }

    // Load users from file.
    while (std::getline(uf, line)) {
        std::stringstream ss(line);
        std::string name, id, borrowedLine;
        if (std::getline(ss, name, ';') &&
            std::getline(ss, id, ';') &&
            std::getline(ss, borrowedLine)) {
            User user(name, id);
            std::stringstream bs(borrowedLine);
            std::string isbn;
            while (std::getline(bs, isbn, ',')) {
                user.borrowBook(isbn);
            }
            users_.emplace(id, user);
        }
    }

    return true;
}

// Saves books and users to the specified files in the expected format.
// Returns true if both files were saved successfully.
bool Library::saveToFiles(const std::string& bookFile, const std::string& userFile) const {
    std::ofstream bf(bookFile);
    std::ofstream uf(userFile);
    if (!bf.is_open() || !uf.is_open())
        return false;

    // Save books to file.
    for (const auto& [isbn, book] : books_) {
        bf << book.getTitle() << ';'
            << book.getAuthor() << ';'
            << book.getISBN() << ';'
            << book.getQuantity() << '\n';
    }

    // Save users to file.
    for (const auto& [id, user] : users_) {
        uf << user.getName() << ';' << user.getId() << ';';
        const auto& borrowed = user.getBorrowedBooks();
        for (size_t i = 0; i < borrowed.size(); ++i) {
            uf << borrowed[i];
            if (i + 1 < borrowed.size()) uf << ',';
        }
        uf << '\n';
    }

    return true;
}

