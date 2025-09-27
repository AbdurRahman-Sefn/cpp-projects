#pragma once
#include "Student.hpp"
#include "Doctor.hpp"
#include "Course.hpp"

class UsersManager
{
private:
    std::unordered_map<std::string, Student*> usrname_student_mp;
    std::unordered_map<std::string, Doctor*> usrname_doctor_mp;
    void push_student(Student* student);
    void push_doctor(Doctor* doctor);
public:
    Student* get_student_by_usrname(std::string usrname)const;
    Doctor* get_doctor_by_usrname(std::string usrname)const;
    bool is_username_existed(std::string usrname)const;
    Student* student_login(std::string usrname, std::string password)const;
    Doctor* doctor_login(std::string usrname, std::string password)const;
    Student* student_signup(std::string usrname, std::string password, std::string name, std::string email);
    Doctor* doctor_signup(std::string usrname, std::string password, std::string name, std::string email);
    ~UsersManager();
};

