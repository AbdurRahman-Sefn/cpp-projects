#pragma once
#include "Assignment.hpp"
#include "AssignmentSolution.hpp"
#include <deque>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Doctor;
class Student;

class Course{
    std::vector<const Assignment*> all_assignments;
    std::unordered_map<const Assignment*, std::vector<AssignmentSolution*>> all_assignment_solutions;
    std::unordered_map<const Assignment*, std::deque<AssignmentSolution*>> ungraded_assignments_queues;
    std::unordered_map<const Student*, std::unordered_map<const Assignment*, AssignmentSolution*>> student_solutions_map;
    std::unordered_map<const Student*, int> student_total_grade;
    const Doctor* const doctor;
    std::string code;
    std::string name;
    int total_full_mark{};
    void push_assignment(const Assignment* assignment);
    void push_solution(AssignmentSolution* sol);
    void remove_solution(const AssignmentSolution* sol);
public:
    void set_grade(AssignmentSolution* sol, int grade);
    Course(const Doctor* doctor,const std::string &name, const std::string &code);
    Assignment* create_assignment(const std::string &title, const std::string &content, int full_mark);
    AssignmentSolution* get_que_front(const Assignment* assignment)const;
    void pop_que_front(const Assignment* assignment);

    bool is_assignment_submitted(const Student* s,const Assignment* assignment)const;
    bool submit_assignment(const Student* s, const Assignment* assignment, const std::string &answer);
    void list_student_assignments(const Student* s,const std::vector<const Assignment*> &assignments, int tabs)const;
    void student_unregister(const Student* s);
    void student_register(const Student* s);
    void show_student_grade(const Student* s)const;
    void print()const;
    void print_detailed()const;
    std::vector<const Assignment*> get_available_assignments()const;
    const std::vector<const Assignment*> &get_all_assignments()const;
    
    std::string get_course_name()const;
    std::string get_course_code()const;
    void list_doctor_assignments(const std::vector<const Assignment*> &assignments, int tabs, bool numbered)const;
    void list_assignment_grades_report(const Assignment* assignment, int tabs)const;
    const std::vector<AssignmentSolution*> &get_all_assignment_solutions(const Assignment*)const;
    ~Course();
};