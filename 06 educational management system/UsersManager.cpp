#include "UsersManager.hpp"

void UsersManager::push_doctor(Doctor* doctor){
    usrname_doctor_mp[doctor->get_usrname()] = doctor;
}
void UsersManager::push_student(Student* student){
    usrname_student_mp[student->get_usrname()] = student;
}

Student* UsersManager::get_student_by_usrname(std::string usrname)const{
    if(usrname_student_mp.count(usrname)){
        return usrname_student_mp.at(usrname);
    }
    return nullptr;
}
Doctor* UsersManager::get_doctor_by_usrname(std::string usrname)const{
    if(usrname_doctor_mp.count(usrname)){
        return usrname_doctor_mp.at(usrname);
    }
    return nullptr;
}
bool UsersManager::is_username_existed(std::string usrname)const{
    return get_doctor_by_usrname(usrname) || get_student_by_usrname(usrname);
}
Student* UsersManager::student_login(std::string usrname, std::string password)const{
    Student* s = get_student_by_usrname(usrname);
    if(s && s->verify(usrname, password)){
        return s;
    }
    return nullptr;
}
Doctor* UsersManager::doctor_login(std::string usrname, std::string password)const{
    Doctor* d = get_doctor_by_usrname(usrname);
    if(d && d->verify(usrname, password)){
        return d;
    }
    return nullptr;
}
Student* UsersManager::student_signup(std::string usrname, std::string password, std::string name, std::string email){
    if(is_username_existed(usrname))
        return nullptr;
    Student *s = new Student(usrname, password, name, email);
    push_student(s);
    return s;
}
Doctor* UsersManager::doctor_signup(std::string usrname, std::string password, std::string name, std::string email){
    if(is_username_existed(usrname))
        return nullptr;
    Doctor *d = new Doctor(usrname, password, name, email);
    push_doctor(d);
    return d;
}
UsersManager::~UsersManager(){
    for(auto &[usrname, doctor] : usrname_doctor_mp)
        delete doctor;
    for(auto &[usrname, student] : usrname_student_mp)
        delete student;
}