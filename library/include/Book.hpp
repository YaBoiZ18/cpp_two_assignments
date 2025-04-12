#pragma once
#include <string>

class Book {
public:
    // Constructor to initialize a Book object with its title, author, ISBN, and available quantity.
    Book(std::string title, std::string author, std::string isbn, int quantity);

    // Returns the title of the book.
    const std::string& getTitle() const;

    // Returns the author of the book.
    const std::string& getAuthor() const;

    // Returns the ISBN of the book.
    const std::string& getISBN() const;

    // Returns the number of copies available for borrowing.
    int getQuantity() const;

    // Decreases the quantity by one when a book is borrowed.
    // Assumes the caller checks that at least one copy is available.
    void borrow();

    // Increases the quantity by one when a book is returned.
    void returnCopy();

private:
    std::string title_;   // The title of the book.
    std::string author_;  // The author of the book.
    std::string isbn_;    // The International Standard Book Number (ISBN) of the book.
    int quantity_;        // The number of available copies in the library.
};