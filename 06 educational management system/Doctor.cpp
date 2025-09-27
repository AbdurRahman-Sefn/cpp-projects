#include "Doctor.hpp"

Doctor::Doctor(std::string usrname, std::string password, std::string name, std::string email)
: username(usrname), password(password), name(name), email(email) {}

bool Doctor::verify(const std::string &usrname, const std::string &password)const{
    return this->username == usrname && this->password == password;
}

const std::string &Doctor::get_name()const{
    return name;
}
const std::string &Doctor::get_usrname()const{
    return username;
}
const std::vector<const Course*> &Doctor::get_courses()const{
    return registered_courses;
}
void Doctor::push_course(const Course* course){
    courses_set.insert(course);
    registered_courses.push_back(course);
}
void Doctor::register_in_course(const Course* course){
    if(!is_registered_in_course(course))
        push_course(course);
}
bool Doctor::is_registered_in_course(const Course* course)const{
    return courses_set.find(course) != courses_set.end();
}