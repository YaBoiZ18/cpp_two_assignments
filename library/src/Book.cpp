#include "Book.hpp"
#include <stdexcept>

// Constructor initializes a Book with the given title, author, ISBN, and quantity.
Book::Book(std::string title, std::string author, std::string isbn, int quantity)
    : title_(std::move(title)), author_(std::move(author)), isbn_(std::move(isbn)), quantity_(quantity) {}

// Returns the title of the book.
const std::string& Book::getTitle() const { return title_; }

// Returns the author of the book.
const std::string& Book::getAuthor() const { return author_; }

// Returns the ISBN of the book.
const std::string& Book::getISBN() const { return isbn_; }

// Returns the current number of available copies.
int Book::getQuantity() const { return quantity_; }

// Attempts to borrow a copy of the book.
// Throws a runtime_error if no copies are available.
void Book::borrow() {
    if (quantity_ <= 0) throw std::runtime_error("Book not available");
    --quantity_;
}

// Returns a borrowed copy to the library by increasing the available quantity.
void Book::returnCopy() {
    ++quantity_;
}