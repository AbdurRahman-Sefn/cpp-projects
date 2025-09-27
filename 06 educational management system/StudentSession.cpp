#include "StudentSession.hpp"
#include "Helper.hpp"

StudentSession::StudentSession(CoursesManager& courses_manager, Student* cur_student)
    : courses_manager(courses_manager)
    , cur_student(cur_student)
    , main_menu_handler(
        std::vector<std::string>{"register in a course", "list my courses",
        "view a course", "grades report", "logout"},
        "\nMain menu:\n",
        StudentMainMenuChoice::RegisterInCourse,
        StudentMainMenuChoice::Logout)
    , course_menu_handler(
        std::vector<std::string>{"unregister from the course", "submit a solution", "back"},
        "\nCourse menu:\n",
        StudentViewCourseMenuChoice::Unregister,
        StudentViewCourseMenuChoice::Back)
    {}

void StudentSession::logout(){
    cur_student = nullptr;
}
StudentMainMenuChoice StudentSession::main_menu() {
    return main_menu_handler.show_and_get_choice("for Student " + cur_student->get_name());
}
StudentViewCourseMenuChoice StudentSession::view_course_menu(Course *course) {
    return course_menu_handler.show_and_get_choice(course->get_course_name());
}

void StudentSession::submit_assignment(Course* course){
    std::vector<const Assignment*> available_assignments = course->get_available_assignments();
    course->print_detailed();
    int size = available_assignments.size();
    if(!size){
        std::cout << "There is no assignments to submit. Take rest\n";
        return;
    }
    else{
        std::cout << "Course has " << size << " assignments\n";
    }
    if(available_assignments.empty()){
        std::cout << "\tThere is no assignment for now!\n";
        return;
    }
    course->list_student_assignments(cur_student, available_assignments, 1);
    const Assignment* assignment_to_submit = select_from(available_assignments, "assignment");
    assignment_to_submit->print_content(1);
    std::string answer;
    std::cout << "Enter the solution: ";
    getline(std::cin, answer);
    bool success = course->submit_assignment(cur_student, assignment_to_submit, answer);
    if(success)
        std::cout << "\tSuccessful submission!\n";
    else
        std::cout << "\tSubmission failed!\n";
}
void StudentSession::register_in_course(){
    std::vector<const Course*> available_to_register = courses_manager.get_availabe_courses_to_student(cur_student);
    courses_manager.list_courses(available_to_register, 1);
    const Course* chosen = select_from(available_to_register, "course");
    if(!chosen){
        return;
    }
    Course* course_to_register = courses_manager.get_course_by_code(chosen->get_course_code());
    course_to_register->student_register(cur_student);
    cur_student->register_in_course(course_to_register);
}
void StudentSession::unregister_from_course(Course* course){
    course->student_unregister(cur_student);
    cur_student->unregister_from_course(course);
}
void StudentSession::run_view_course_menu(){
    auto &registered_courses = cur_student->get_courses();
    courses_manager.list_courses(registered_courses, 1);
    const Course* chosen = select_from(registered_courses, "course");
    if(!chosen){
        return;
    }
    Course* course_to_view = courses_manager.get_course_by_code(chosen->get_course_code());
    auto &assignments_to_view = course_to_view->get_all_assignments();
    if(assignments_to_view.empty()){
        std::cout << "\tThere is no assignments for now!\n";
    }
    else{
        course_to_view->list_student_assignments(cur_student, assignments_to_view, 1);
    }
    while(cur_student){
        auto choice = view_course_menu(course_to_view);
        switch (choice)
        {
        case StudentViewCourseMenuChoice::Back:
            return;
        case StudentViewCourseMenuChoice::SubmitSolution:
            submit_assignment(course_to_view);
            break;
        case StudentViewCourseMenuChoice::Unregister:
            unregister_from_course(course_to_view);
            break;
        case StudentViewCourseMenuChoice::InvalidChoice:
        default:
            std::cout << "Invalid choice!\n";
            break;
        }
    }
}
void StudentSession::show_grades_report(){
    cur_student->show_total_grades_report(1);
}
void StudentSession::list_registered_courses(){
    auto courses_to_list = cur_student->get_courses();
    if(courses_to_list.empty()){
        std::cout << "\tThere is no courses to display!\n";
        return;
    }
    courses_manager.list_courses(courses_to_list, 1);
}
void StudentSession::run_main_menu(){
    while(cur_student){
        auto choice = main_menu();
        switch (choice)
        {
        case StudentMainMenuChoice::Logout:
            logout();
            return;
        case StudentMainMenuChoice::GradesReport:
            show_grades_report();
            break;
        case StudentMainMenuChoice::ViewCourse:
            run_view_course_menu();
            break;
        case StudentMainMenuChoice::ListMyCourses:
            list_registered_courses();
            break;
        case StudentMainMenuChoice::RegisterInCourse:
            register_in_course();
            break;
        case StudentMainMenuChoice::InvalidChoice:
        default:
            std::cout << "Invalid choice!\n";
            break;
        }
    }
}