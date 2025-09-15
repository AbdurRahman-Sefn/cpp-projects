#include "UsersManager.hpp"
#include <algorithm>
#include <fstream>


std::pair<User*, std::string> UsersManager::enter_user(){
    std::string user_name;
    std::cout << "Enter user name: ";
    read_and_trim(std::cin, user_name);
    return {names_dictionary.word_exist(user_name), user_name};
}

void UsersManager::push_user(User *user){
    ids_dictionary[user->get_id()] = user;
    names_dictionary.insert(user, user->get_name());
}

void UsersManager::clear(){
    ids_dictionary.clear();
    names_dictionary.clear();
}

AddUserResult UsersManager::add_user(std::string &name_added_formatted){
    auto [usr_ptr, usr_name] = enter_user();
    if(usr_ptr){
        return AddUserResult::NAME_IS_EXISTED_BEFORE;
    }
    int id = read_validated_input<int>("Enter user id: ");
    if(ids_dictionary.find(id) != ids_dictionary.end()){
        return AddUserResult::ID_IS_EXISTED_BEFORE;
    }
    User *user = new User(id, usr_name);
    push_user(user);
    name_added_formatted = user->get_name_formatted();
    return AddUserResult::SUCCESS;
}

void UsersManager::print_users_by_id()const{
    std::cout << "\tUsers sorted by id: \n";
    User::print_header(2);
    for(auto &[id, user] : ids_dictionary){
        user->print(2);
    }
}

void UsersManager::print_users_by_name()const{
    std::cout << "\tUsers sorted by name: \n";
    User::print_header(2);
    names_dictionary.traverse([](User* user){
        user->print(2);
    });
}

void UsersManager::print_borrowers(const std::vector<BorrowOperation*> &operations)const{
    std::vector<std::string> borrowers_names;
    for(auto &operation : operations){
        borrowers_names.push_back(operation->user->get_name_formatted());
    }
    std::sort(borrowers_names.begin(), borrowers_names.end());
    for(int i = 0; i < borrowers_names.size(); ++i){
        std::string cur_name = borrowers_names[i];
        int freq = 1;
        while(i + 1 < borrowers_names.size() && cur_name == borrowers_names[i + 1]){
            ++i;
            ++freq;
        }
        if(freq > 1)
            --i;
        std::cout << "\tUser " <<  cur_name << " borrowed " << std::setw(2) << std::right << freq << " item(s) of this book\n";
    }
}

const User* UsersManager::get_user_by_id(int id) const{
    auto it = ids_dictionary.find(id);
    if(it == ids_dictionary.cend()){
        return nullptr;
    }
    return it->second;
}

UsersManager::~UsersManager(){
    update_database();
    for(auto &[id, user] : ids_dictionary){
        delete user;
    }
}
UsersManager::UsersManager(){
    load_database();
}

void UsersManager::load_database(){
    std::ifstream data("Users.txt");
    if(data.fail()){
        data.close();
        throw std::invalid_argument("CAN't open database of users --> \"Users.txt\"");
    }
    clear();
    std::string user_str;
    while (read_and_trim(data, user_str))
    {
        User *user = new User(user_str);
        push_user(user);
    }
    data.close();
}
void UsersManager::update_database(){
    std::ofstream data("Users.txt");
    if(data.fail()){
        data.close();
        throw std::invalid_argument("CAN't open database of users --> \"Users.txt\"");
    }
    for(auto &[id, user] : ids_dictionary){
        data << user->to_string() << "\n";
    }
    data.close();
}
