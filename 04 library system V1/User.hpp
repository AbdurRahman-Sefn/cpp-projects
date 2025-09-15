#pragma once
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "Helper.hpp"
#include "Book.hpp"

class User{
    static constexpr int USER_NAME_WIDTH = 40;
    static constexpr int USER_ID_WIDTH = 10;
    int id;
    std::string name;
    std::unordered_map<Book*, int>borrowed_books;
    void borrow(Book* book);
    bool return_(Book* book);
    User(int id, std::string name);
    friend class UsersManager;
public:
    std::string get_name() const;
    void print_borrowed_books(int tabs = 0)const;
    static void print_header(int tabs = 0);
    void print(int tabs = 0) const;
};
