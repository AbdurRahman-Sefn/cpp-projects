#include "UsersManager.hpp"



std::pair<const User*, std::string> UsersManager::enter_user()const{
    std::string user_name;
    std::cout << "Enter user name: ";
    getline(std::cin, user_name);
    return {names_dictionary.word_exist(user_name), user_name};
}
bool UsersManager::add_user(){
    auto [usr_ptr, usr_name] = enter_user();
    if(usr_ptr){
        std::cout << "This name is already existed!\n";
        return false;
    }
    int id = read_validated_input<int>("Enter user id: ");
    if(ids_dictionary.find(id) != ids_dictionary.end()){
        std::cout << "This id is already existed!\n";
        return false;
    }
    User *user = new User(id, usr_name);
    ids_dictionary[id] = user;
    names_dictionary.insert(user, usr_name);
    return true;
}
void UsersManager::user_borrow_book(User *usr, Book *book){
    return usr->borrow(book);
}
bool UsersManager::user_return_book(User *usr, Book *book){
    return usr->return_(book);
}
void UsersManager::print_users()const{
    std::cout << "Users sorted by ids: \n";
    User::print_header(1);
    for(auto &[id, usr] : ids_dictionary){
        usr->print(1);
        usr->print_borrowed_books(2);
    }
}
UsersManager::~UsersManager(){
    for(auto &[id, user] : ids_dictionary){
        delete user;
    }
}
