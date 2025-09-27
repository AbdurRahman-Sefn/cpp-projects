#pragma once
#include <iostream>
#include <vector>
class Course;
class AssignmentSolution;
class Assignment{
    std::string content;
    std::string title;
    int full_mark;
    bool is_available_to_submit = true;
    const Course* const course;
public:
    void print_content(int tabs)const;
    void print(int tabs)const;
    void list_solutions(const std::vector<AssignmentSolution*> &solutions, int tabs, bool numbered)const;
    bool can_submit()const;
    Assignment(const Course* course, const std::string &title, const std::string &content, int full_mark);
    int get_full_mark()const;
    const std::string &get_title()const;
    const Course* get_parent_course()const;
};