#pragma once
#include "Course.hpp"
#include "Student.hpp"
#include "Doctor.hpp"
#include <map>
#include <unordered_map>
#include <vector>


class CoursesManager{
    std::map<std::string, Course*> code_to_course_map;
    void push_course(Course* course);
public:
    void list_courses(const std::vector<const Course*> &courses, int tabs)const;
    const std::vector<const Course*> get_availabe_courses_to_student(const Student *s)const;
    Course* get_course_by_code(const std::string &code)const;
    Course* create_course(Doctor* doctor,const std::string &name,const std::string &code);
    ~CoursesManager();
};