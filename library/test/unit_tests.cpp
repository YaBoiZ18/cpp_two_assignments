#include <gtest/gtest.h>
#include "Book.hpp"
#include "User.hpp"
#include "Library.hpp"
#include <filesystem>
#include <fstream>

// ---------- CORE FEATURE TESTS ----------

// Book Class Tests
TEST(BookTest, BorrowAndReturn) {
    Book book("1984", "Orwell", "123", 2);
    book.borrow();
    EXPECT_EQ(book.getQuantity(), 1);  // Should decrease by 1
    book.returnCopy();
    EXPECT_EQ(book.getQuantity(), 2);  // Should return to original
}

// User Class Tests
TEST(UserTest, BorrowReturnBookTracking) {
    User user("Alice", "U001");
    user.borrowBook("ISBN1");
    EXPECT_EQ(user.getBorrowedBooks().size(), 1);  // One book borrowed
    user.returnBook("ISBN1");
    EXPECT_TRUE(user.getBorrowedBooks().empty());  // List should be empty
}

// Library Book Management Tests
TEST(LibraryTest, AddRemoveBooks) {
    Library lib;
    Book book("Dune", "Frank Herbert", "B001", 5);
    EXPECT_TRUE(lib.addBook(book));   // First add should succeed
    EXPECT_FALSE(lib.addBook(book));  // Duplicate ISBN, should fail
    EXPECT_TRUE(lib.removeBook("B001"));    // Removal should succeed
    EXPECT_FALSE(lib.removeBook("B001"));   // Already removed, should fail
}

// Library User Management Tests
TEST(LibraryTest, AddRemoveUsers) {
    Library lib;
    User user("Bob", "U001");
    EXPECT_TRUE(lib.addUser(user));    // Should succeed
    EXPECT_FALSE(lib.addUser(user));   // Duplicate, should fail
    EXPECT_TRUE(lib.removeUser("U001"));   // Should succeed
    EXPECT_FALSE(lib.removeUser("U001"));  // Already removed, should fail
}

// Library Book Search Tests
TEST(LibraryTest, SearchBooks) {
    Library lib;
    lib.addBook(Book("Dune", "Frank Herbert", "B001", 5));
    lib.addBook(Book("Dune Messiah", "Frank Herbert", "B002", 2));
    lib.addBook(Book("Foundation", "Isaac Asimov", "B003", 3));

    auto results1 = lib.searchByTitle("Dune");
    EXPECT_EQ(results1.size(), 1);  // Only one book titled "Dune"

    auto results2 = lib.searchByAuthor("Frank Herbert");
    EXPECT_EQ(results2.size(), 2);  // Two books by Frank Herbert

    auto book = lib.searchByISBN("B003");
    ASSERT_NE(book, nullptr);  // Book must exist
    EXPECT_EQ(book->getTitle(), "Foundation");
}


// ---------- FILE IO TESTS ----------

TEST(LibraryTest, SaveAndLoadLibrary) {
    Library lib1;
    lib1.addBook(Book("Book A", "Author A", "A001", 4));
    lib1.addUser(User("Alice", "U001"));
    lib1.borrowBook("U001", "A001");  // Borrow reduces quantity by 1

    std::string booksFile = "test_books.txt";
    std::string usersFile = "test_users.txt";

    EXPECT_TRUE(lib1.saveToFiles(booksFile, usersFile));  // Save must succeed

    Library lib2;
    EXPECT_TRUE(lib2.loadFromFiles(booksFile, usersFile));  // Load must succeed

    auto b = lib2.searchByISBN("A001");
    ASSERT_NE(b, nullptr);  // Book should be loaded
    EXPECT_EQ(b->getQuantity(), 3);  // One copy borrowed, so quantity reduced

    std::filesystem::remove(booksFile);
    std::filesystem::remove(usersFile);  // Clean up
}

// ---------- EDGE CASE TESTS ----------

// No Copies Left
TEST(LibraryTest, BorrowUnavailableBook) {
    Library lib;
    lib.addBook(Book("Solo Copy", "Someone", "B001", 1));
    lib.addUser(User("Tom", "U100"));
    lib.borrowBook("U100", "B001");

    // Book quantity now 0, borrowing again should fail
    EXPECT_FALSE(lib.borrowBook("U100", "B001"));
}

// Invalid User or Book Borrowing Test
TEST(LibraryTest, BorrowWithInvalidUserOrBook) {
    Library lib;
    lib.addBook(Book("Book", "Author", "B001", 1));

    EXPECT_FALSE(lib.borrowBook("InvalidUser", "B001"));  // Invalid user
    EXPECT_FALSE(lib.borrowBook("U001", "InvalidBook"));  // Invalid book
}

// Invalid User or Book Returning Test
TEST(LibraryTest, ReturnWithInvalidUserOrBook) {
    Library lib;
    lib.addBook(Book("Book", "Author", "B001", 1));
    lib.addUser(User("Tom", "U100"));

    EXPECT_FALSE(lib.returnBook("U100", "InvalidBook"));  // Book doesn't exist
    EXPECT_FALSE(lib.returnBook("InvalidUser", "B001"));  // User doesn't exist
}

