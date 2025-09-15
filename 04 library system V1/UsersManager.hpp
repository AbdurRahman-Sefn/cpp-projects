#pragma once
#include "Dictionary.hpp"
#include "User.hpp"
#include "Book.hpp"
#include <input_utils.hpp>

class UsersManager{
    std::map<int, User*> ids_dictionary;
    Dictionary <User> names_dictionary;
public:
    std::pair<const User*, std::string> enter_user()const;
    bool add_user();
    void user_borrow_book(User *usr, Book *book);
    bool user_return_book(User *usr, Book *book);
    void print_users()const;
    ~UsersManager();
};