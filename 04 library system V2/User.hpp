#pragma once
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "Helper.hpp"
#include "Book.hpp"

enum class AddUserResult{
    SUCCESS,
    ID_IS_EXISTED_BEFORE,
    NAME_IS_EXISTED_BEFORE
};

class User{
    static constexpr int USER_NAME_WIDTH = 40;
    static constexpr int USER_ID_WIDTH = 10;
    static const char DELIM = '|';
    int id;
    std::string name;
    std::string formatted_name;
    User(int id, std::string name);
    User(const std::string &user_str);
    std::string to_string()const;
    friend class UsersManager;
public:
    std::string get_name() const;
    const std::string &get_name_formatted() const;
    int get_id() const;
    static void print_header(int tabs = 0);
    void print(int tabs = 0) const;
};
