#pragma once
#include <Dictionary.hpp>
#include "User.hpp"
#include "Book.hpp"
#include "BorrowOperation.hpp"
#include <input_utils.hpp>

class UsersManager{
    std::map<int, User*> ids_dictionary;
    Dictionary <User> names_dictionary;
    void load_database();
    void update_database();
    void push_user(User *user);
    void clear();
public:
    UsersManager();
    UsersManager(const UsersManager&) = delete;
    UsersManager& operator=(const UsersManager&) = delete;
    std::pair<User*, std::string> enter_user();
    AddUserResult add_user(std::string &name_added_formatted);
    const User* get_user_by_id(int id) const;
    void print_users_by_name()const;
    void print_users_by_id()const;
    void print_borrowers(const std::vector<BorrowOperation*> &operations)const;
    ~UsersManager();
};