#include"Student.hpp"
#include <algorithm>

Student::Student(std::string usrname, std::string password, std::string name, std::string email)
: username(usrname), password(password), name(name), email(email) {}

bool Student::verify(const std::string &usrname, const std::string &password)const{
    return this->username == usrname && this->password == password;
}

const std::vector<const Course*> &Student::get_courses()const{
    return registered_courses;
}
bool Student::is_registered_in_course(const Course* course)const{
    return courses_set.find(course) != courses_set.end();
}
void Student::push_course(const Course* course){
    courses_set.insert(course);
    registered_courses.push_back(course);
}
void Student::remove_course(const Course* course){
    courses_set.erase(course);
    auto it = std::find(registered_courses.begin(), registered_courses.end(), course);
    if(it != registered_courses.end()){
        registered_courses.erase(it);
    }
}
void Student::register_in_course(const Course* course){
    if(!is_registered_in_course(course))
        push_course(course);
}
void Student::unregister_from_course(const Course* course){
    if(is_registered_in_course(course))
        remove_course(course);
}
void Student::show_total_grades_report(int tabs)const{
    std::cout << "\n";
    for(auto &course : registered_courses){
        course->show_student_grade(this);
    }
}
const std::string &Student::get_name()const{
    return name;
}
const std::string &Student::get_usrname()const{
    return username;
}