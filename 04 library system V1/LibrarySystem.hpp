#pragma once
#include "UsersManager.hpp"
#include "BooksManager.hpp"

class LibrarySystem{
    UsersManager users_manager;
    BooksManager books_manager;
    struct VerificationResult{
        bool success = false;
        User* user = nullptr;
        Book *book = nullptr;
    };
    VerificationResult verify();
    void borrow_book();
    void return_book();
    void load_data_base();
    void update_data_base();
public:
    void run();
};
