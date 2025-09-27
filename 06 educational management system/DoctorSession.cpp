#include "DoctorSession.hpp"
#include <input_utils.hpp>
#include "Helper.hpp"

void DoctorSession::logout(){
    cur_doctor = nullptr;
}
DoctorMainMenuChoice DoctorSession::main_menu() {
    return main_menu_handler.show_and_get_choice("for Doctor " + cur_doctor->get_name());
}
DoctorViewCourseMenuChoice DoctorSession::view_course_menu(Course* course) {
    return course_menu_handler.show_and_get_choice(course->get_course_name());
}
DoctorViewAssignmentMenuChoice DoctorSession::view_assignment_menu(const Assignment* assignment) {
    return assignment_menu_handler.show_and_get_choice(assignment->get_title());
}
DoctorViewSolutionMenuChoice DoctorSession::view_solution_menu(AssignmentSolution* sol) {
    return solution_menu_handler.show_and_get_choice("of Student " + sol->get_student()->get_name());
}
void DoctorSession::list_courses(){
    auto &courses = cur_doctor->get_courses();
    if(courses.empty()){
        std::cout << "\tThere is no courses to display!\n";
        return;
    }
    courses_manager.list_courses(courses, 1);
}
void DoctorSession::create_course(){
    std::cout << "Enter course name: ";
    std::string course_name;
    getline(std::cin, course_name);
    std::string code = read_validated_input<std::string>("Enter course code (no spaces): ");
    while(courses_manager.get_course_by_code(code) != nullptr)
        code = read_validated_input<std::string>("This code is already existed. Try another one (no spaces): ");
    Course* course_added = courses_manager.create_course(cur_doctor, course_name, code);
    if(course_added){
        cur_doctor->register_in_course(course_added);
        std::cout << "\tCourse " << course_name << " created successfully!\n";
    }
    else{
        std::cout << "\tInvalid creation!\n";
    }
}

void DoctorSession::list_assignments(Course* course){
    std::vector<const Assignment*> all_assignments = course->get_all_assignments();
    if(all_assignments.empty()){
        std::cout << "\tThere is no assignment for now!\n";
    }
    else{
        course->list_doctor_assignments(all_assignments, 1, false);
    }
}
void DoctorSession::create_assignment(Course* course){
    std::cout << "Enter assignment title: ";
    std::string title;
    getline(std::cin, title);
    std::cout << "Enter assignment content: ";
    std::string content;
    std::getline(std::cin, content);
    int full_mark = read_validated_input<int>("Enter the full mark grade: ");
    Assignment* assignment_added = course->create_assignment(title, content, full_mark);
    if(assignment_added){
        std::cout << "\tAssignment " << title << " created successfully!\n";
    }
    else{
        std::cout << "\tInvalid creation!\n";
    }
}
    
void DoctorSession::run_view_solution_menu(Course* cur_course,const Assignment* assignment, AssignmentSolution* selected_before){
    AssignmentSolution* sol_to_view = selected_before;
    if(!selected_before){
        const Course* course = assignment->get_parent_course();
        const std::vector<AssignmentSolution*> &all_solutions = course->get_all_assignment_solutions(assignment);
        assignment->list_solutions(all_solutions, 1, true);
        sol_to_view = select_from(all_solutions, "Solution");
    }
    while(cur_doctor && assignment && sol_to_view){
        auto choice = view_solution_menu(sol_to_view);
        switch (choice)
        {
        case DoctorViewSolutionMenuChoice::Back:
            return;
        case DoctorViewSolutionMenuChoice::SetComment:
            make_comment(sol_to_view);
            break;
        case DoctorViewSolutionMenuChoice::SetGrade:
            make_grade(cur_course, sol_to_view);
            break;
        case DoctorViewSolutionMenuChoice::PrintContent:
            sol_to_view->print_content(1);
            break;
        case DoctorViewSolutionMenuChoice::InvalidChoice:
        default:
            std::cout << "Invalid choice!\n";
            break;
        }
        if(selected_before){
            return;
        }
    }
}
void DoctorSession::run_view_assignment_menu(Course* course){
    std::vector<const Assignment*> all_assignments = course->get_all_assignments();
    course->list_doctor_assignments(all_assignments, 1, true);
    const Assignment* assignment_to_view = select_from(all_assignments, "Assignment");
    while (cur_doctor && course && assignment_to_view)
    {
        auto choice = view_assignment_menu(assignment_to_view);
        switch (choice)
        {
        case DoctorViewAssignmentMenuChoice::Back:
            return;
        case DoctorViewAssignmentMenuChoice::ViewSolution:
            run_view_solution_menu(course, assignment_to_view);
            break;
        case DoctorViewAssignmentMenuChoice::ListSolutions:
            list_solutions(assignment_to_view);
            break;
        case DoctorViewAssignmentMenuChoice::PopSolutionFromQueue:
            course->pop_que_front(assignment_to_view);
            break;
        case DoctorViewAssignmentMenuChoice::ViewSolutionFromQueue:
            view_a_solution_from_queue(course , assignment_to_view);
            break;
        case DoctorViewAssignmentMenuChoice::ListGradesReport:
            course->list_assignment_grades_report(assignment_to_view, 1);
            break;
        case DoctorViewAssignmentMenuChoice::PrintContent:
            assignment_to_view->print_content(1);
            break;
        case DoctorViewAssignmentMenuChoice::InvalidChoice:
        default:
            std::cout << "Invalid choice!\n";
            break;
        }
    }
    
}
void DoctorSession::run_view_course_menu(){
    auto &registered_courses = cur_doctor->get_courses();
    courses_manager.list_courses(registered_courses, 1);
    const Course* chosen = select_from(registered_courses, "course");
    while(cur_doctor && chosen){
        Course* course_to_view = courses_manager.get_course_by_code(chosen->get_course_code());
        auto choice = view_course_menu(course_to_view);
        switch (choice)
        {
        case DoctorViewCourseMenuChoice::Back:
            return;
        case DoctorViewCourseMenuChoice::ViewAssignment:
            run_view_assignment_menu(course_to_view);
            break;
        case DoctorViewCourseMenuChoice::CreateAssignment:
            create_assignment(course_to_view);
            break;
        case DoctorViewCourseMenuChoice::ListAssignments:
            list_assignments(course_to_view);
            break;
        case DoctorViewCourseMenuChoice::InvalidChoice:
        default:
            std::cout << "Invalid choice!\n";
            break;
        }
    }
}
void DoctorSession::run_main_menu(){
    while(cur_doctor){
        auto choice = main_menu();
        switch (choice)
        {
        case DoctorMainMenuChoice::Logout:
            logout();
            return;
        case DoctorMainMenuChoice::ViewCourse:
            run_view_course_menu();
            break;
        case DoctorMainMenuChoice::CreateCourse:
            create_course();
            break;
        case DoctorMainMenuChoice::ListCourses:
            list_courses();
            break;
        case DoctorMainMenuChoice::InvalidChoice:
        default:
            std::cout << "Invalid choice!\n";
            break;
        }
    }
}
DoctorSession::DoctorSession(CoursesManager &courses_manager, Doctor* cur_doctor)
    : courses_manager(courses_manager)
    , cur_doctor(cur_doctor)
    , main_menu_handler(
        std::vector<std::string>{"list my courses", "create a course", "view a course", "logout"},
        "\nMain menu:\n",
        DoctorMainMenuChoice::ListCourses,
        DoctorMainMenuChoice::Logout)
    , course_menu_handler(
        std::vector<std::string>{"list assignments", "create an assignment", "view an assignment", "back"},
        "\nCourse menu:\n",
        DoctorViewCourseMenuChoice::ListAssignments,
        DoctorViewCourseMenuChoice::Back)
    , assignment_menu_handler(
        std::vector<std::string>{"print content", "list grades report",
         "view a solution from the queue", "pop a solution from the queue",
          "list solutions", "view a solution", "back"},
        "\nAssignment menu:\n",
        DoctorViewAssignmentMenuChoice::PrintContent,
        DoctorViewAssignmentMenuChoice::Back)
    , solution_menu_handler(
        std::vector<std::string>{"print content", "set grade", "set comment", "back"},
        "\nSolution menu:\n",
        DoctorViewSolutionMenuChoice::PrintContent,
        DoctorViewSolutionMenuChoice::Back)
    {}

void DoctorSession::make_grade(Course* course, AssignmentSolution* sol){
    int grade = read_validated_input<int>("Enter the grade: ");
    course->set_grade(sol, grade);
}
void DoctorSession::make_comment(AssignmentSolution* sol){
    std::cout << "Enter your comment: ";
    std::string comment;
    getline(std::cin, comment);
    sol->set_comment(comment);
}
void DoctorSession::view_a_solution_from_queue(Course* cur_course, const Assignment* assignment){
    auto sol = cur_course->get_que_front(assignment);
    if(!sol){
        std::cout << "\tThis queue is empty!\n";
        return;
    }
    run_view_solution_menu(cur_course, assignment, sol);
    if(sol->is_graded()){
        cur_course->pop_que_front(assignment);
    }
}
void DoctorSession::list_solutions(const Assignment* assignment){
    auto course = assignment->get_parent_course();
    auto &all_solutions = course->get_all_assignment_solutions(assignment);
    if(all_solutions.empty()){
        std::cout << "\tThere is no solutions submitted for now!\n";
    }
    assignment->list_solutions(all_solutions, 1, false);
}