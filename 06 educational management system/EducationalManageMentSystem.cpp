#include "EducationalManageMentSystem.hpp"
#include "Helper.hpp"

SystemMainMenuChoice EducationalManagemenentSystem::system_menu(){
    return main_menu_handler.show_and_get_choice();
}
bool EducationalManagemenentSystem::enter(){
    auto choice = system_menu();
    switch (choice)
    {
    case SystemMainMenuChoice::Exit:
        return false;
    case SystemMainMenuChoice::SignUp:
        signup();
        break;
    case SystemMainMenuChoice::Login:
        login();
        break;
    case SystemMainMenuChoice::InvalidChoice:
    default:
        std::cout << "\nInvalid choice!\n";
        break;
    }
    return true;
}
void EducationalManagemenentSystem::login(){
    std::string username = read_validated_input<std::string>("Enter username: ");
    std::string password = read_validated_input<std::string>("Enter password: ");
    cur_doctor = users_manager.doctor_login(username, password);
    if(cur_doctor){
        std::cout << "\n\tWelcome Dr " << cur_doctor->get_name() << " !\n";
        return;
    }
    cur_student = users_manager.student_login(username, password);
    if(cur_student){
        std::cout << "\n\tWelcome " << cur_student->get_name() << " !\n";
        return;
    }
    else{
        std::cout << "\n\tInvalid username or password!\n";
    }
}
void EducationalManagemenentSystem::signup(){
    auto type = enter_menu_handler.show_and_get_choice();
    if (type == EnterMenuChoice::Back || type == EnterMenuChoice::InvalidChoice) {
        return;
    }
    std::string name;
    std::cout << "Enter your name: ";
    getline(std::cin, name);
    std::string email = read_validated_input<std::string>("Enter your email: ");
    std::string username = read_validated_input<std::string>("Enter username: ");
    while(users_manager.is_username_existed(username)){
        username = read_validated_input<std::string>("\tThis username is already existed. Enter another username: ");
    }
    std::string password = read_validated_input<std::string>("Enter password: ");
    if(type == EnterMenuChoice::Student) {
        cur_student = users_manager.student_signup(username, password, name, email);
        if(cur_student)
            std::cout << "\n\tWelcome " << cur_student->get_name() << " !\n";
    }
    else if(type == EnterMenuChoice::Doctor) {
        cur_doctor = users_manager.doctor_signup(username, password, name, email);
        if(cur_doctor)
            std::cout << "\n\tWelcome Dr " << cur_doctor->get_name() << " !\n";
    }
}

void EducationalManagemenentSystem::run(){
    while(true){
        bool state = enter();
        if(!state){
            return;
        }
        if(cur_doctor){
            DoctorSession session(courses_manager, cur_doctor);
            session.run_main_menu();
        }
        else if(cur_student){
            StudentSession session(courses_manager, cur_student);
            session.run_main_menu();
        }
    }
}

EducationalManagemenentSystem::EducationalManagemenentSystem()
    : main_menu_handler(
        std::vector<std::string>{"Login", "Sign up", "Shutdown system"},
        "\nEducational Management System:\n",
        SystemMainMenuChoice::Login,
        SystemMainMenuChoice::Exit)
    , enter_menu_handler(
        std::vector<std::string>{"Student", "Doctor", "Back"},
        "\nSelect user type:\n",
        EnterMenuChoice::Student,
        EnterMenuChoice::Back)
    {
        load_dummy_data();
    }
void EducationalManagemenentSystem::load_dummy_data() {
    std::cout << "Loading dummy data...\n";

    // =================================================================
    // ١. إنشاء الأطباء والطلاب (Creating Doctors & Students)
    // =================================================================
    Doctor* doc1 = users_manager.doctor_signup("mostafa", "111", "Mostafa Saad", "mostafa@gmail.com");
    Doctor* doc2 = users_manager.doctor_signup("hany", "222", "Hany Mohamed", "hany@yahoo.com");

    Student* s1 = users_manager.student_signup("ahmed", "123", "Ahmed Ali", "ahmed@gmail.com");
    Student* s2 = users_manager.student_signup("ali", "123", "Ali Hassan", "ali@gmail.com");
    Student* s3 = users_manager.student_signup("salma", "123", "Salma Ibrahim", "salma@gmail.com");
    Student* s4 = users_manager.student_signup("mona", "123", "Mona Youssef", "mona@gmail.com");
    Student* s5 = users_manager.student_signup("omar", "123", "Omar Khaled", "omar@gmail.com"); // طالب لن يسجل في أي كورس

    // =================================================================
    // ٢. إنشاء المساقات الدراسية (Creating Courses)
    // =================================================================
    Course* course1 = courses_manager.create_course(doc1, "Programming 1", "CS101");
    doc1->register_in_course(course1);
    Course* course2 = courses_manager.create_course(doc1, "Data Structures", "CS213");
    doc1->register_in_course(course2);
    Course* course3 = courses_manager.create_course(doc2, "Calculus 1", "MATH101");
    doc2->register_in_course(course3);
    Course* course4 = courses_manager.create_course(doc2, "Physics 1", "PHY101"); // كورس لن يسجل فيه أي طالب
    doc2->register_in_course(course4);

    // =================================================================
    // ٣. تسجيل الطلاب في المساقات (Registering Students in Courses)
    // لاحظ أن التسجيل يتم في كلا الاتجاهين (الطالب يسجل، والكورس يسجل الطالب)
    // =================================================================
    // Ahmed -> CS101, MATH101
    s1->register_in_course(course1);
    course1->student_register(s1);
    s1->register_in_course(course3);
    course3->student_register(s1);

    // Ali -> CS101
    s2->register_in_course(course1);
    course1->student_register(s2);

    // Salma -> CS213, MATH101
    s3->register_in_course(course2);
    course2->student_register(s3);
    s3->register_in_course(course3);
    course3->student_register(s3);

    // Mona -> CS101, CS213
    s4->register_in_course(course1);
    course1->student_register(s4);
    s4->register_in_course(course2);
    course2->student_register(s4);
    
    // =================================================================
    // ٤. إنشاء الواجبات (Creating Assignments)
    // =================================================================
    Assignment* as1_c1 = course1->create_assignment("Assignment 1", "Implement a simple calculator.", 10);
    Assignment* as2_c1 = course1->create_assignment("Assignment 2", "Explain loops in C++.", 8);

    Assignment* as1_c2 = course2->create_assignment("Assignment 1", "Implement a linked list.", 15);

    Assignment* as1_c3 = course3->create_assignment("Homework 1", "Solve differentiation problems.", 12);
    
    // =================================================================
    // ٥. تسليم حلول الواجبات (Submitting Solutions)
    // =================================================================
    // CS101 Submissions
    course1->submit_assignment(s1, as1_c1, "Ahmed's answer for assignment 1.");
    course1->submit_assignment(s2, as1_c1, "Ali's answer for assignment 1.");
    course1->submit_assignment(s4, as1_c1, "Mona's answer for assignment 1.");
    course1->submit_assignment(s2, as2_c1, "Ali's answer for assignment 2."); // Ali submitted both

    // CS213 Submissions
    course2->submit_assignment(s3, as1_c2, "Salma's implementation of a linked list.");
    course2->submit_assignment(s4, as1_c2, "Mona's implementation of a linked list.");
    
    // MATH101 Submissions
    course3->submit_assignment(s1, as1_c3, "Ahmed's solutions for calculus homework.");
    
    // =================================================================
    // ٦. تقييم بعض الحلول (Grading some solutions)
    // هذه الخطوة تحاكي قيام الطبيب بتقييم الحلول الموجودة في قائمة الانتظار
    // =================================================================
    
    // Doctor Mostafa grades CS101, Assignment 1
    // Grade Ahmed's solution
    AssignmentSolution* sol1 = course1->get_que_front(as1_c1);
    course1->set_grade(sol1, 8); // Ahmed gets 8/10
    course1->pop_que_front(as1_c1);

    // Grade Ali's solution
    AssignmentSolution* sol2 = course1->get_que_front(as1_c1);
    course1->set_grade(sol2, 9); // Ali gets 9/10
    course1->pop_que_front(as1_c1);

    // Mona's solution for CS101-As1 remains ungraded.
    // Ali's solution for CS101-As2 remains ungraded.

    // Doctor Mostafa grades CS213, Assignment 1
    // Grade Salma's solution
    AssignmentSolution* sol3 = course2->get_que_front(as1_c2);
    course2->set_grade(sol3, 13); // Salma gets 13/15
    course2->pop_que_front(as1_c2);

    // Mona's solution for CS213-As1 remains ungraded.
    
    std::cout << "Dummy data loaded successfully.\n\n";
}