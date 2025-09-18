#include <iomanip>
#include <sstream>
#include "Question.hpp"
#include "Helper.hpp"
#include "User.hpp"
#include "Question.hpp"

Question::Question(User* sender, User* receptor, int id, const std::string &question_text, bool is_anonymous, Question* parent)
    : sender(sender), receptor(receptor), id(id), question_text(question_text), is_anonymous(is_anonymous), parent(parent){}
Question::~Question(){
    if(answer)
        delete answer;
}
Answer::Answer(const std::string &answer_text): answer_text(answer_text){}
const std::string &Answer::get_answer_text()const{
    return answer_text;
}
void Answer::update(const std::string &new_answer_text){
    answer_text = new_answer_text;
}

int Question::get_id()const{
    return id;
}
void Question::print_to_whom(int indent)const{
    std::string tabs = indenter(indent);
    std::cout << tabs << "Question id   :  " << id << "\n";
    if(parent)
        std::cout << tabs << "\t-->From thread question id: " << parent->get_id() << "\n";
    std::cout << tabs << "Is anonymous? : " << is_anonymous << "\n";
    std::cout << tabs << "To User       : " << receptor->get_name() << "\n";
    std::cout << tabs << "\tQuestion text : " << question_text << "\n";
    if(answer)
        std::cout << tabs << "\tAnswer text   : " << answer->get_answer_text() << "\n";
    else
        std::cout << tabs << "\tNot Answered Yet!\n";
}
void Question::print_from_whom(int indent) const{
    std::string tabs = indenter(indent);
    std::cout << tabs << "Question id : " << id << "\n";
    if(is_anonymous)
        std::cout << tabs << "From an anonymous user!\n";
    else
        std::cout << tabs << "From User   : " << sender->get_name() << "\n";
    std::cout << tabs << "\tQuestion text : " << question_text << "\n";
    if(answer)
        std::cout << tabs << "\tAnswer text   : " << answer->get_answer_text() << "\n";
    else
        std::cout << tabs << "\tNot Answered Yet!\n";
}

void Question::print_feed(const User* const cur_user, int indent) const{
    std::string tabs = indenter(indent);
    std::cout << tabs << "Question id : " << id << "\n";
     if(is_anonymous)
        std::cout << tabs << "From an anonymous user!\n";
    else{
        std::cout << tabs << "From User   : " << sender->get_name();
        if(cur_user == sender)
            std::cout << "(You)";
        std::cout <<"\n";
    }
    std::cout << tabs << "To User     : " << receptor->get_name();
    if(cur_user == receptor)
        std::cout << "(You)";
    std::cout <<"\n";
    std::cout << tabs << "\tQuestion text : " << question_text << "\n";
    if(answer)
    std::cout << tabs << "\tAnswer text   : " << answer->get_answer_text() << "\n";
}

bool Question::can_edit(User* user) const{
    return receptor == user;
}

bool Question::can_see(User* user) const{
    bool res = (user == receptor || user == sender);
    if(!res && answer && (!parent || parent->can_see(user))){
        return true;
    }
    return res;
}

void Question::set_answer_text(const std::string &answer_text){
    if(!answer)
        answer = new Answer(answer_text);
    else
        answer->update(answer_text);
}

std::string Question::to_string()const{
    std::ostringstream oss;
    oss << id << DELIM << question_text << DELIM << (answer ? answer->get_answer_text() : "") << DELIM 
    << is_anonymous <<DELIM << (parent ? parent->get_id() : -1) << DELIM << sender->get_id() << DELIM
    << receptor->get_id() << DELIM;
    return oss.str();
}
Question::Question(const std::string &question_str){
    std::string temp;
    std::istringstream iss(question_str);

    getline(iss, temp, DELIM);
    id = stoi(temp);
    getline(iss, question_text, DELIM);
    getline(iss, temp, DELIM);
    if(!temp.empty())
        answer = new Answer(temp);
    getline(iss, temp, DELIM);
    is_anonymous = stoi(temp);
    getline(iss, temp, DELIM);
    temp_parent_id = stoi(temp);
    getline(iss, temp, DELIM);
    temp_sender_id = stoi(temp);
    getline(iss, temp, DELIM);
    temp_receptor_id = stoi(temp);
}
User* Question::get_sender()const{
    return sender;
}
User* Question::get_receptor() const{
    return receptor;
}
bool Question::is_answered()const{
    return answer != nullptr;
}
Question* Question::get_parent_question()const{
    return parent;
}
void Question::link_objects(const std::map<int, User*> &users_id_map, const std::map<int, Question*> &questions_id_map){
    if(temp_parent_id != -1)
        parent = questions_id_map.at(temp_parent_id);
    sender = users_id_map.at(temp_sender_id);
    receptor = users_id_map.at(temp_receptor_id);

    sender->push_sent_question(this);
    if(parent == nullptr)
        receptor->push_received_question(this);
}