#pragma once
#include "User.hpp"
#include <unordered_map>
#include <map>
#include <vector>

class UsersManager{
    std::unordered_map<std::string, User*> username_to_user_map;
    std::map<int, User*> id_to_user_map;
    int last_id;
    void push_user(User* user);
    void clear();
public:
    const std::map<int, User*> &get_id_users_map()const;
    User* get_user_by_id(int id)const;
    User* get_user_by_username(const std::string &username)const;
    User* log_in(const std::string &user_name, const std::string &password)const;
    User* sign_up(const std::string &user_name, const std::string &password, const std::string &email, bool allow_anonymous);
    void list_system_users()const;
    void load_database();
    void update_database();
    ~UsersManager();
};