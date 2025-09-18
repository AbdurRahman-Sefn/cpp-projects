#include "UsersManager.hpp"
#include <fstream>
User* UsersManager::get_user_by_id(int id)const{
    auto it = id_to_user_map.find(id);
    if(it == id_to_user_map.end())
        return nullptr;
    return it->second;
}
User* UsersManager::get_user_by_username(const std::string &username)const{
    auto it = username_to_user_map.find(username);
    if(it == username_to_user_map.end())
        return nullptr;
    return it->second;
}
User* UsersManager::log_in(const std::string &user_name, const std::string &password)const{
    auto it = username_to_user_map.find(user_name);
    if(it == username_to_user_map.end())
        return nullptr;
    if(it->second->verify(user_name, password)){
        return it->second;
    }
    return nullptr;
}
User* UsersManager::sign_up(const std::string &user_name, const std::string &password, const std::string &email, bool allow_anonymous){
    int id = ++last_id;
    User* user = new User(id, email, user_name, password, allow_anonymous);
    push_user(user);
    return user;
}
void UsersManager::list_system_users()const{
    User::print_header(1);
    for(auto &[id, user] : id_to_user_map){
        user->print(1);
    }
    std::cout << "\n";
}
void UsersManager::push_user(User* user){
    username_to_user_map[user->get_name()] = user;
    id_to_user_map[user->get_id()] = user;
}

void UsersManager::load_database(){
    clear();
    std::ifstream users_file("Users.txt");
    std::string user_str;
    while(getline(users_file, user_str)){
        User* user = new User(user_str);
        push_user(user);
        last_id = std::max(last_id, user->get_id());
    }
    users_file.close();
}
void UsersManager::clear(){
    for(auto &[id, user] : id_to_user_map){
        delete user;
    }
    username_to_user_map.clear();
    id_to_user_map.clear();
    last_id = -1;
}
void UsersManager::update_database(){
    std::ofstream users_file("Users.txt");
    for(auto &[id, user] : id_to_user_map){
        users_file << user->to_string() << "\n";
    }
    users_file.close();
}
const std::map<int, User*> &UsersManager::get_id_users_map()const{
    return id_to_user_map;
}
UsersManager::~UsersManager(){
    update_database();
    clear();
}