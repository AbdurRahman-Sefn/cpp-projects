#pragma once
#include "UsersManager.hpp"
#include "StudentSession.hpp"
#include "DoctorSession.hpp"
#include "MenuHandler.hpp"

enum class SystemMainMenuChoice {
    InvalidChoice = 0,

    Login = 1,
    SignUp,
    Exit,

};

enum class EnterMenuChoice {
    InvalidChoice = 0,
    
    Student = 1,
    Doctor,
    Back,

};

class EducationalManagemenentSystem {
    UsersManager users_manager;
    CoursesManager courses_manager;
    Student* cur_student{};
    Doctor* cur_doctor{};

    // Menu handlers
    const MenuHandler<SystemMainMenuChoice> main_menu_handler;
    const MenuHandler<EnterMenuChoice> enter_menu_handler;

    SystemMainMenuChoice system_menu();
    bool enter();
    void login();
    void signup();
    void load_dummy_data();
public:
    EducationalManagemenentSystem();
    void run();
};