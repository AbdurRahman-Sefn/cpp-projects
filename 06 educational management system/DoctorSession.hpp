#pragma once
#include "CoursesManager.hpp"
#include "MenuHandler.hpp"

enum class DoctorMainMenuChoice {
    InvalidChoice = 0,

    ListCourses = 1,
    CreateCourse,
    ViewCourse,
    Logout,

};
enum class DoctorViewCourseMenuChoice {
    InvalidChoice = 0,

    ListAssignments = 1,
    CreateAssignment,
    ViewAssignment,
    Back,

};
enum class DoctorViewAssignmentMenuChoice {
    InvalidChoice = 0,

    PrintContent = 1,
    ListGradesReport,
    ViewSolutionFromQueue,
    PopSolutionFromQueue,
    ListSolutions,
    ViewSolution,
    Back,

};
enum class DoctorViewSolutionMenuChoice {
    InvalidChoice = 0,

    PrintContent = 1,
    SetGrade,
    SetComment,
    Back,

};
class DoctorSession
{

private:
    Doctor* cur_doctor{};
    CoursesManager &courses_manager;

    // Menu handlers
    const MenuHandler<DoctorMainMenuChoice> main_menu_handler;
    const MenuHandler<DoctorViewCourseMenuChoice> course_menu_handler;
    const MenuHandler<DoctorViewAssignmentMenuChoice> assignment_menu_handler;
    const MenuHandler<DoctorViewSolutionMenuChoice> solution_menu_handler;

    DoctorMainMenuChoice main_menu();
    DoctorViewCourseMenuChoice view_course_menu(Course* course);
    DoctorViewAssignmentMenuChoice view_assignment_menu(const Assignment* assignment);
    DoctorViewSolutionMenuChoice view_solution_menu(AssignmentSolution* sol);

    void logout();
    void list_courses();
    void create_course();
    void make_grade(Course* course, AssignmentSolution* sol);
    void make_comment(AssignmentSolution* sol);
    void view_a_solution_from_queue(Course* cur_course, const Assignment* assignment);
    void list_solutions(const Assignment* assignment);

    void list_assignments(Course* course);
    void create_assignment(Course* course);

    void run_view_course_menu();
    void run_view_assignment_menu(Course* course);
    void run_view_solution_menu(Course* cur_course, const Assignment* assignment,  AssignmentSolution* selected_before = nullptr);
public:
    void run_main_menu();
    DoctorSession(CoursesManager &courses_manager, Doctor* cur_doctor);
};

