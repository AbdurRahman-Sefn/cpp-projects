#pragma once
#include <vector>
#include <iostream>
#include <map>

class User;
class Answer{
    std::string answer_text;
public:
    Answer(const std::string &answer_text);
    void update(const std::string &new_answer_text);
    const std::string &get_answer_text()const;
};
class Question{
    int id{-1};
    std::string question_text;

    Question *parent{};
    User* sender{};
    User* receptor{};
    Answer *answer{};
    
    static const char DELIM = '|';
    int temp_parent_id{-1};
    int temp_sender_id{-1};
    int temp_receptor_id{-1};

    bool is_anonymous = false;
public:
    std::string to_string()const;
    Question(const std::string &question_str);
    Question(User* sender, User* receptor, int id, const std::string &question_text, bool is_anonymous = false, Question* parent = nullptr);
    void link_objects(const std::map<int, User*> &users_id_map, const std::map<int, Question*> &questions_id_map);
    int get_id()const;
    Question* get_parent_question()const;
    bool is_answered()const;
    bool can_see(User* user) const;
    bool can_edit(User* user) const;
    void print_from_whom(int indent)const;
    void print_to_whom(int indent)const;
    void print_feed(const User* const cur_user, int indent) const;
    void set_answer_text(const std::string &answer_text);
    User* get_sender()const;
    User* get_receptor()const;
    ~Question();
};