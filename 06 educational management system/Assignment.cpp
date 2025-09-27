#include "Assignment.hpp"
#include "AssignmentSolution.hpp"
#include "Helper.hpp"


Assignment::Assignment(const Course* const course, const std::string &title, const std::string &content, int full_mark) 
: course(course), title(title), content(content), full_mark(full_mark){}
int Assignment::get_full_mark()const{
    return full_mark;
}
void Assignment::print_content(int tabs)const{
    std::string indent = indenter(tabs);
    std::cout << indent << title << "\n";
    std::cout << indent << "Content: \n";
    std::cout << indent << "\t--> " << content << "\n";
}
const std::string &Assignment::get_title()const{
    return title;
}
const Course* Assignment::get_parent_course()const{
    return course;
}
bool Assignment::can_submit()const{
    return is_available_to_submit;
}
void Assignment::print(int tabs)const{
    std::string indent = indenter(tabs);
    std::cout << indent << title << "\n";
}
void Assignment::list_solutions(const std::vector<AssignmentSolution*> &solutions, int tabs, bool numbered)const{
    if(solutions.empty()){
        return;
    }
    int cnt = 1;
    std::string indent = indenter(tabs);
    std::cout << "\n*****************************************\n";
    for(auto &sol : solutions){
        if(numbered)
            std::cout << indent << cnt++ << "- \n";
        sol->print_content(tabs);
    }
    std::cout << "\n*****************************************\n\n";
}