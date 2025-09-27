#pragma once
#include "Assignment.hpp"

class Student;
class AssignmentSolution{
    const Assignment* const assignment;
    const Student* const student;
    std::string answer;
    std::string comment;
    int grade{-1};
public:
    void set_grade(int grade);
    void set_comment(std::string comment);
    void print_content(int tabs)const;
    void print_student_grade(int tabs)const;
    const Assignment* get_assignment()const;
    const Student* get_student()const;

    AssignmentSolution(const Assignment* assignment, const Student* student, std::string answer);
    bool is_graded()const;
    const std::string &get_comment()const;
    int get_grade()const;
    int get_full_mark()const;
    void update_answer(const std::string &new_answer);
};