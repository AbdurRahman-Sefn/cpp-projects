#pragma once
#include "UsersManager.hpp"
#include "QuestionsManager.hpp"

class AskMe{
    UsersManager users_manager;
    QuestionsManager questions_manager;
    int cur_user_id{-1};
    User *cur_user{};
    bool enter();
    bool read_question(Question* &question);
    void login();
    void signup();
    void logout();
    void link_objects();
    void load_database();
    void update_database();
    void ask_question();
    void answer_question();
    void delete_question();
public:
    void run();
};