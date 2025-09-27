#include "AssignmentSolution.hpp"
#include "Helper.hpp"
#include "Student.hpp"
#include <iomanip>

AssignmentSolution::AssignmentSolution(const Assignment* assignment, const Student* student, std::string answer):
 assignment(assignment), student(student), answer(answer){}
bool AssignmentSolution::is_graded()const{
    return grade >= 0;
}
const std::string &AssignmentSolution::get_comment()const{
    return comment;
}
int AssignmentSolution::get_grade()const{
    return grade;
}
int AssignmentSolution::get_full_mark()const{
    return assignment->get_full_mark();
}
void AssignmentSolution::update_answer(const std::string &new_answer){
    answer = new_answer;
}
void AssignmentSolution::set_grade(int grade){
    this->grade = grade;
}
void AssignmentSolution::set_comment(std::string comment){
    this->comment = comment;
}
void AssignmentSolution::print_content(int tabs)const{
    std::string indent = indenter(tabs);
    std::cout << indent << "Assignment : " << assignment->get_title() << "\n";
    std::cout << indent << "Course     : " << assignment->get_parent_course()->get_course_name() << "\n";
    std::cout << indent << "Student    : " << student->get_name() << "\n";
    std::cout << indent << "Answer     : " << answer << "\n";
    if(!comment.empty())
        std::cout << indent << "Comment   : " << comment << "\n";
    std::cout << "\n";
}
void AssignmentSolution::print_student_grade(int tabs)const{
    std::string indent = indenter(tabs);
    std::cout << indent << std::left << std::setw(30) << student->get_name();
    std::cout << " | " << std::right << std::setw(3) << grade << "\n";
}
const Assignment* AssignmentSolution::get_assignment()const{
    return assignment;
}
const Student* AssignmentSolution::get_student()const{
    return student;
}