#pragma once
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "Helper.hpp"
class User;

enum class AddBookResult{
    SUCCESS,
    ID_IS_EXISTED_BEFORE,
    NAME_IS_EXISTED_BEFORE,
    INVALID_QUANTITY,
};

class Book{
    friend class BooksManager;
    static constexpr int BOOK_NAME_WIDTH = 40;
    static constexpr int ID_WIDTH = 10;
    static constexpr int QTY_WIDTH = 15;
    static constexpr int BORROWED_WIDTH = 15;
    static const char DELIM = '|';
    int id;
    std::string name;
    std::string formatted_name;
    int quantity;
    int borrowed = 0;
    Book(int id, std::string name, int quantity);
    Book(const std::string &book_str);
    std::string to_string()const;
    
public:
    static void print_header(int tabs = 0);
    void print(int tabs = 0)const;
    std::string get_name()const;
    int get_id()const;
    bool is_available()const;
    const std::string &get_name_formatted()const;
};
