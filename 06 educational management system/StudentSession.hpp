#pragma once
#include "CoursesManager.hpp"
#include "MenuHandler.hpp"

enum class StudentMainMenuChoice {
    InvalidChoice = 0,

    RegisterInCourse = 1,
    ListMyCourses,
    ViewCourse,
    GradesReport,
    Logout,

};
enum class StudentViewCourseMenuChoice {
    InvalidChoice = 0,

    Unregister = 1,
    SubmitSolution,
    Back,

};

class StudentSession
{
private:
    Student* cur_student{};
    const CoursesManager &courses_manager;

    // Menu handlers
    const MenuHandler<StudentMainMenuChoice> main_menu_handler;
    const MenuHandler<StudentViewCourseMenuChoice> course_menu_handler;

    void list_registered_courses();
    void show_grades_report();
    StudentMainMenuChoice main_menu();
    void logout();
    void register_in_course();
    void unregister_from_course(Course* course);
    void submit_assignment(Course* course);
    StudentViewCourseMenuChoice view_course_menu(Course* course);
    void run_view_course_menu();
public:
    StudentSession(CoursesManager& courses_manager, Student* cur_student);
    void run_main_menu();
};
