#pragma once
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "Helper.hpp"
class User;

class Book{
    friend class BooksManager;
    static constexpr int NAME_WIDTH = 40;
    static constexpr int ID_WIDTH = 10;
    static constexpr int QTY_WIDTH = 15;
    static constexpr int BORROWED_WIDTH = 15;
    int id;
    std::string name;
    int quantity;
    int borrowed = 0;
    std::unordered_map<User*, int> borrowers;
    bool borrow(User* user);
    bool return_(User* user);
    Book(int id, std::string name, int quantity);
public:
    static void print_header(int tabs = 0);
    void print(int tabs = 0)const;
    void print_detailed(int tabs = 0)const;
    std::string get_name()const;
};
