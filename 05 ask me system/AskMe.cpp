#include "AskMe.hpp"
#include "Helper.hpp"
#include <input_utils.hpp>

bool AskMe::enter(){
    const static std::vector<std::string> options{"Log in:", "Sign up", "Close system"};
    show_menu(options, "\nMenu: ", 0);
    int choice = read_validated_input<int>("\nEnter your choice[1 - 3]: ", 0);
    while(!is_in_range(choice, 1, 3)){
        std::cout << "\tWrong input!.\n";
        choice = read_validated_input<int>("Enter your choice[1 - 3]: ", 0);
    }
    if(choice == 3)
        return false;
    else if(choice == 1)
        login();
    else if(choice == 2)
        signup();
    return true;
}
void AskMe::logout(){
    cur_user_id = -1;
    cur_user = nullptr;
}
void AskMe::login(){
    std::string user_name, password;
    std::cout << "Enter your username: ";
    read_and_trim(std::cin, user_name);
    std::cout << "Enter your password: ";
    getline(std::cin, password);
    cur_user = users_manager.log_in(user_name, password);
    if(cur_user)
        cur_user_id = cur_user->get_id();
    if(!cur_user)
        std::cout << "\tInvalid username or password!\n";
}

void AskMe::signup(){
    std::string user_name, password, email;
    std::cout << "Enter your email: ";
    read_and_trim(std::cin, email);
    std::cout << "Enter your username: ";
    read_and_trim(std::cin, user_name);
    while(users_manager.get_user_by_username(user_name)){
        std::cout << "\tThis username is already taken. Try another one: \n";
        read_and_trim(std::cin, user_name);
    }
    std::cout << "Enter your password: ";
    getline(std::cin, password);
    bool allow_anonymous = read_validated_input<bool>("Do you allow anonymous questions?(0 or 1): ");
    cur_user = users_manager.sign_up(user_name, password, email, allow_anonymous);
    if(cur_user)
        cur_user_id = cur_user->get_id();
}
void AskMe::ask_question(){
    int user_id = read_validated_input<int>("Enter user id or -1 to cancel: ");
    User* user_to_ask = users_manager.get_user_by_id(user_id);
    if(!user_to_ask){
        std::cout << "\tThere is no user with such id...Try to list system users\n";
        return;
    }
    bool is_anonymous = false;
    if(user_to_ask->is_allowing_anonymous()){
        is_anonymous = read_validated_input<bool>("Ask as anonymous?(0 or 1): ");
    }
    else{
        std::cout << "Note: \'" << user_to_ask->get_name() << "\' is not allowing anonymous questions\n";
    }
    int thread_id = read_validated_input<int>("for thread question, enter question id or -1 for a new one: ");
    Question* thread = questions_manager.get_question_by_id(thread_id);
    if(thread_id != -1){
        if(!thread || !thread->can_see(cur_user)){
            std::cout << "\tThere is no question with such id...Try to list feed questions\n";
        }
    }
    std::string question_text;
    std::cout << "Enter question text: ";
    getline(std::cin, question_text);
    Question* question = questions_manager.add_question(cur_user, user_to_ask, question_text, is_anonymous, thread);
}
bool AskMe::read_question(Question* &question){
    int question_id = read_validated_input<int>("Enter question id or -1 to cancel: ");
    if(question_id == -1)
        return false;
    question = questions_manager.get_question_by_id(question_id);
    return true;
}
void AskMe::answer_question(){
    Question* question;
    bool status = read_question(question);
    if(!status)
        return;
    if(!question || !question->can_edit(cur_user)){
        std::cout << "\tThere is no such an id in your questions' ids...Try print questions asked to you\n";
        return;
    }
    questions_manager.print_questions_from_whom({question});
    if(question->is_answered()){
        std::cout << "\tWarning: already answered!-->answer will be updated\n";
    }
    std::string answer_text;
    std::cout << "Enter answer text: ";
    getline(std::cin, answer_text);
    question->set_answer_text(answer_text);
}
void AskMe::delete_question(){
    Question* question;
    bool status = read_question(question);
    if(!status)
        return;
    if(!question || !question->can_edit(cur_user)){
        std::cout << "\tThere is no such an id in your questions' ids...Try print questions asked to you\n";
        return;
    }
    questions_manager.print_questions_from_whom({question});
    bool is_sure = read_validated_input<bool>("\tAre you sure to delete question?(0 or 1): ");
    if(!is_sure)
        return;
    questions_manager.remove_question(question);
}

void AskMe::run(){
    const static std::vector<std::string> options{"print questions to me", "print questions from me",
    "answer question", "delete question", "ask question", "list system users", "feed", "logout"};
    while(true){
        if(!cur_user){
            load_database();
            bool state = enter();
            if(!state)
                break;
            else{
                update_database();
                continue;
            }
        }
        show_menu(options, "\nMenu: ", 0);
        int choice = read_validated_input<int>("\nEnter your choice[1 - 8]: ", 0);
        if(!is_in_range(choice, 1, 8)){
            std::cout << "\tInvalid choice...Try again\n";
            continue;
        }
        switch (choice)
        {
        case 1:{
            load_database();
            auto &questions_recieved = cur_user->get_questions_received();
            questions_manager.print_questions_from_whom(questions_recieved);
            break;
        }
        case 2: {
            auto &questions_sent = cur_user->get_questions_sent();
            questions_manager.print_questions_to_whom(questions_sent);
            break;
        }
        case 3:
            load_database();
            answer_question();
            update_database();
            break;
        case 4:
            load_database();
            delete_question();
            update_database();
            break;
        case 5:
            load_database();
            ask_question();
            update_database();
            break;
        case 6:
            load_database();
            users_manager.list_system_users();
            break;
        case 7:
            load_database();
            questions_manager.list_feed(cur_user);
            break;
        case 8:
            update_database();
            logout();
            break;
        }
    }
}
void AskMe::link_objects(){
    auto &users_id_map = users_manager.get_id_users_map();
    questions_manager.link_objects(users_id_map);
}
void AskMe::load_database(){
    users_manager.load_database();
    questions_manager.load_database();
    link_objects();
    cur_user = users_manager.get_user_by_id(cur_user_id);
}
void AskMe::update_database(){
    users_manager.update_database();
    questions_manager.update_database();
}