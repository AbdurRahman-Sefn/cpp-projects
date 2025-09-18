#pragma once
#include "Question.hpp"
#include <iostream>
#include <vector>
class User{
    static constexpr int USER_NAME_WIDTH = 40;
    static constexpr int USER_ID_WIDTH = 10;
    static const char DELIM = '|';
    int id{-1};
    std::string email;
    std::string password;
    std::string user_name;
    bool allow_anonymous = false;
    std::vector<Question*> questions_from_user;
    std::vector<Question*> questions_to_user;
public:
    std::string to_string()const;
    User(const std::string &user_str);
    void push_received_question(Question* question);
    void push_sent_question(Question* question);
    void pop_received_question(Question* question);
    void pop_sent_question(Question* question);
    User(int id, const std::string &email, const std::string &user_name, const std::string &password, bool allow_anonymous);
    bool verify(const std::string &user_name, const std::string &password)const;
    static void print_header(int tabs = 0);
    void print(int tabs = 0) const;
    std::string get_name()const;
    bool is_allowing_anonymous()const;
    int get_id()const;
    const std::vector<Question*> &get_questions_sent()const;
    const std::vector<Question*> &get_questions_received()const;
};