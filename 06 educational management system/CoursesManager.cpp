#include "CoursesManager.hpp"
#include "Helper.hpp"

const std::vector<const Course*> CoursesManager::get_availabe_courses_to_student(const Student *s)const{
    std::vector<const Course*> ret;
    for(auto &[code, course] : code_to_course_map){
        if(!s->is_registered_in_course(course)){
            ret.push_back(course);
        }
    }
    return ret;
}
void CoursesManager::list_courses(const std::vector<const Course*> &courses, int tabs)const{
    if(courses.empty()){
        return;
    }
    std::cout << "\n*****************************************\n";
    std::string indent = indenter(tabs);
    int cnt = 1;
    for(auto &course : courses){
        std::cout << indent << cnt++ << "- "; course->print();
    }
    std::cout << "\n*****************************************\n\n";
}

Course* CoursesManager::get_course_by_code(const std::string &code)const{
    if(code_to_course_map.find(code) != code_to_course_map.end())
        return code_to_course_map.at(code);
    else
        return nullptr;
}
Course* CoursesManager::create_course(Doctor* doctor,const std::string &name,const std::string &code){
    if(get_course_by_code(code)){
        return nullptr;
    }
    Course* added = new Course(doctor, name, code);
    push_course(added);
    return added;
}
void CoursesManager::push_course(Course* course){
    code_to_course_map[course->get_course_code()] = course;
}
CoursesManager::~CoursesManager(){
    for(auto &[code, course] : code_to_course_map){
        delete course;
    }
}