#include "QuestionsManager.hpp"
#include "User.hpp"
#include <fstream>
#include <algorithm>

void QuestionsManager::print_questions_from_whom(const std::vector<Question*> &received_questions)const{
    std::cout << "\n*****************************************************\n";
    for(auto &question : received_questions){
        print_questions_from_whom(question, 1);
    }
    std::cout << "\n*****************************************************\n";
}
void QuestionsManager::print_questions_to_whom(const std::vector<Question*> &sent_questions)const{
    std::cout << "\n*****************************************************\n";
    for(auto &question : sent_questions){
        question->print_to_whom(1);
        std::cout << "\n";
    }
    std::cout << "\n*****************************************************\n";
}
void QuestionsManager::print_questions_from_whom(Question* received_question, int indent)const{
    received_question->print_from_whom(indent);
    std::cout << "\n";
    auto it = parent_children_map.find(received_question);
    if(it != parent_children_map.end()){
        for(auto &child : it->second){
            print_questions_from_whom(child, indent + 1);
        }
    }
}

void QuestionsManager::list_feed(User* cur_user, int indent)const{
    std::cout << "\n*****************************************************\n";
    for(auto &[parent, children] : parent_children_map){
        if(parent->get_parent_question() == nullptr && parent->can_see(cur_user) && parent->is_answered()){
            list_feed(cur_user, parent, indent);
        }
    }
    std::cout << "\n*****************************************************\n";
}

void QuestionsManager::list_feed(User* cur_user, Question* question, int indent)const{
    question->print_feed(cur_user, indent);
    std::cout << "\n";
    indent++;
    auto it = parent_children_map.find(question);
    if(it != parent_children_map.cend()){
        for(auto &child : it->second){
            if(child->can_see(cur_user) && child->is_answered())
                list_feed(cur_user, child, indent);
        }
    }
}
Question* QuestionsManager::add_question(User* sender, User* receptor, const std::string &question_text, bool is_anonymous, Question* parent){
    int question_id = ++last_id;
    Question *question = new Question(sender, receptor, question_id, question_text, is_anonymous, parent);
    push_question(question);
    if(!question->get_parent_question()){
        question->get_receptor()->push_received_question(question);
    }
    question->get_sender()->push_sent_question(question);
    return question;
}
void QuestionsManager::push_question(Question* question){
    id_question_map[question->get_id()] = question;
    if(question->get_parent_question()){
        parent_children_map[question->get_parent_question()].push_back(question);
    }
    else
    parent_children_map[question];
}
void QuestionsManager::remove_question(Question* question){
    if(!question->get_parent_question()){
        question->get_receptor()->pop_received_question(question);
    }
    else{
        auto &v = parent_children_map[question->get_parent_question()];
        auto it = std::find(v.begin(), v.end(), question);
        v.erase(it);
    }
    remove_question_threaded(question);
}
void QuestionsManager::remove_question_threaded(Question* question){
    question->get_sender()->pop_sent_question(question);
    id_question_map.erase(question->get_id());
    if(parent_children_map.count(question)){
        for(auto &child : parent_children_map[question]){
            remove_question_threaded(child);
        }
        parent_children_map.erase(question);
    }
    delete question;
}

void QuestionsManager::load_database(){
    clear();
    std::ifstream questions_file("Questions.txt");
    std::string question_str;
    while(getline(questions_file, question_str)){
        Question* question = new Question(question_str);
        push_question(question);
        last_id = std::max(last_id, question->get_id());
    }
    questions_file.close();
}

void QuestionsManager::update_database(){
    std::ofstream questions_file("Questions.txt");
    for(auto &[id, question] : id_question_map){
        questions_file << question->to_string() << "\n";
    }
    questions_file.close();
}
void QuestionsManager::link_objects(const std::map<int, User*> &users_id_map){
    for(auto &[id, question] : id_question_map){
        question->link_objects(users_id_map, id_question_map);
    }
}
void QuestionsManager::clear(){
    for(auto &[id, question] : id_question_map){
        delete question;
    }
    id_question_map.clear();
    parent_children_map.clear();
    last_id = -1;
}
QuestionsManager::~QuestionsManager(){
    update_database();
    clear();
}
Question* QuestionsManager::get_question_by_id(int id)const{
    auto it = id_question_map.find(id);
    if(it == id_question_map.end())
        return nullptr;
    return it->second;
}