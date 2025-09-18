#include "User.hpp"
#include "Helper.hpp"
#include <iomanip>
#include <algorithm>
#include <sstream>

std::string User::get_name() const{
    return user_name;
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
              << "| " << std::left << std::setw(USER_NAME_WIDTH) << user_name << " |"
              << " "  << std::right << std::setw(USER_ID_WIDTH) << id << " |\n";
}

bool User::verify(const std::string &user_name, const std::string &password)const{
    return user_name == this->user_name && password == this->password;
}

int User::get_id()const{
    return id;
}
bool User::is_allowing_anonymous()const{
    return allow_anonymous;
}
const std::vector<Question*> &User::get_questions_sent()const{
    return questions_from_user;
}
const std::vector<Question*> &User::get_questions_received()const{
    return questions_to_user;
}
User::User(int id, const std::string &email, const std::string &user_name, const std::string &password, bool allow_anonymous)
:id(id), email(email), user_name(user_name), password(password), allow_anonymous(allow_anonymous){}
void User::push_received_question(Question* question){
    questions_to_user.push_back(question);
}
void User::push_sent_question(Question* question){
    questions_from_user.push_back(question);
}
void User::pop_received_question(Question* question){
    auto it = std::find(questions_to_user.begin(), questions_to_user.end(), question);
    questions_to_user.erase(it);
}
void User::pop_sent_question(Question* question){
    auto it = std::find(questions_from_user.begin(), questions_from_user.end(), question);
    questions_from_user.erase(it);
}

std::string User::to_string()const{
    std::ostringstream oss;
    oss << id << DELIM << email << DELIM << user_name << DELIM << password << DELIM << allow_anonymous <<DELIM;
    return oss.str();
}
User::User(const std::string &user_str){
    std::istringstream iss(user_str);
    std::string temp_int;
    getline(iss, temp_int, DELIM);
    id = std::stoi(temp_int);
    getline(iss, email, DELIM);
    getline(iss, user_name, DELIM);
    getline(iss, password, DELIM);
    getline(iss, temp_int, DELIM);
    allow_anonymous = std::stoi(temp_int);
}