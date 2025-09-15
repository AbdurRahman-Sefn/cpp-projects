#pragma once
#include "UsersManager.hpp"
#include "BooksManager.hpp"
#include "BorrowsManager.hpp"

class LibrarySystem{
    UsersManager users_manager;
    BooksManager books_manager;
    BorrowsManager borrows_manager;

    struct VerificationResult{
        bool success = false;
        User* user = nullptr;
        Book *book = nullptr;
    };
    VerificationResult verify();
    void borrow_book();
    void return_book();
    void print_who_borrowed_book_by_name();
    void print_user_borrowed_books();
    void add_user();
    void add_book();
    void load_borrows_database();
public:
    LibrarySystem();
    void run();
};
