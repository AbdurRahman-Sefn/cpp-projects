#pragma once
#include "Course.hpp"
#include <unordered_set>


class Student{
    std::string name;
    std::string email;
    std::string username;
    std::string password;
    std::unordered_set<const Course*> courses_set;
    std::vector<const Course*> registered_courses;
    void push_course(const Course* course);
    void remove_course(const Course* course);
public:
    Student(std::string usrname, std::string password, std::string name, std::string email);
    bool verify(const std::string &usrname, const std::string &password)const;
    const std::string &get_name()const;
    const std::string &get_usrname()const;
    bool is_registered_in_course(const Course* course)const;
    const std::vector<const Course*> &get_courses()const;
    void register_in_course(const Course* course);
    void unregister_from_course(const Course* course);
    void show_total_grades_report(int tabs)const;
};