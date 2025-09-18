#pragma once
#include "Question.hpp"
#include <unordered_map>
#include <map>

class QuestionsManager{
    std::map<int, Question*> id_question_map;
    std::unordered_map<Question*, std::vector<Question*> > parent_children_map;
    int last_id;
    void push_question(Question* question);
    void list_feed(User* user, Question* question, int indent)const;
    void print_questions_from_whom(Question* received_question, int indent) const;
    void remove_question_threaded(Question* question);
    void clear();
public:
    void link_objects(const std::map<int, User*> &users_id_map);
    void remove_question(Question* question);
    Question* add_question(User* sender, User* receptor, const std::string &question_text, bool is_anonymous = false, Question* parent = nullptr);
    Question* get_question_by_id(int id)const;
    void print_questions_from_whom(const std::vector<Question*> &received_questions)const;
    void print_questions_to_whom(const std::vector<Question*> &sent_questions)const;
    void list_feed(User* user, int indent = 1)const;
    void load_database();
    void update_database();
    ~QuestionsManager();
};