#include "User.hpp"
#include <sstream>


User::User(int id, std::string name): id(id), name((trim(name), name)){
    std::ostringstream oss;
    oss << "\'" << std::left << std::setw(USER_NAME_WIDTH) << name << "\'";
    formatted_name = oss.str();
}
std::string User::get_name() const{
    return name;
}
const std::string &User::get_name_formatted() const{
    return formatted_name;
}
void User::print_header(int tabs) {
    std::string indent = indenter(tabs);
    
    int total_width = USER_NAME_WIDTH + USER_ID_WIDTH + 7; // +9 for separators and padding
    std::string decorator(total_width, '-');

    std::cout << indent << decorator << "\n";
    std::cout << indent
              << "| " << std::left << std::setw(USER_NAME_WIDTH) << "Name" << " |"
              << " "  << std::right << std::setw(USER_ID_WIDTH) << "ID" << " |\n";
    std::cout << indent << decorator << "\n";
}

void User::print(int tabs) const {
    std::string indent = indenter(tabs);
    std::cout << indent
              << "| " << std::left << std::setw(USER_NAME_WIDTH) << name << " |"
              << " "  << std::right << std::setw(USER_ID_WIDTH) << id << " |\n";
}

User::User(const std::string &user_str){
    std::istringstream iss(user_str);
    getline(iss, name, DELIM);
    iss >> id;
}

std::string User::to_string()const{
    std::ostringstream oss;
    oss << name << DELIM << id << DELIM;
    return oss.str();
}
int User::get_id() const{
    return id;
}