#include "Course.hpp"
#include "Helper.hpp"
#include "Doctor.hpp"
#include <iomanip>
#include <algorithm>

Course::Course(const Doctor* doctor,const std::string &name, const std::string &code)
    : doctor(doctor), name(name), code(code){}
Assignment* Course::create_assignment(const std::string &title, const std::string &content, int full_mark){
    Assignment* added = new Assignment(this, title, content, full_mark);
    push_assignment(added);
    return added;
}
AssignmentSolution* Course::get_que_front(const Assignment* assignment)const{
    auto &que = ungraded_assignments_queues.at(assignment);
    AssignmentSolution* front{};
    if(!que.empty()){
        front = que.front();
    }
    return front;
}
void Course::pop_que_front(const Assignment* assignment){
    auto &que = ungraded_assignments_queues.at(assignment);
    if(!que.empty()){
        que.pop_front();
    }
}
void Course::set_grade(AssignmentSolution* sol, int grade){
    sol->set_grade(grade);
    const Student* s = sol->get_student();
    student_total_grade.at(s) += grade;
}

void Course::push_assignment(const Assignment* assignment){
    all_assignments.push_back(assignment);
    all_assignment_solutions[assignment];
    ungraded_assignments_queues[assignment];
    total_full_mark += assignment->get_full_mark();
}
void Course::push_solution(AssignmentSolution* sol){
    const Assignment* assignment = sol->get_assignment();
    auto student = sol->get_student();
    auto &mp = student_solutions_map.at(student);
    mp[assignment] = sol;
    all_assignment_solutions[assignment].push_back(sol);
    ungraded_assignments_queues[assignment].push_back(sol);
}
void Course::remove_solution(const AssignmentSolution* sol){
    const Assignment* assignment = sol->get_assignment();
    if(sol->is_graded()){
        auto &v = all_assignment_solutions.at(assignment);
        auto it = std::find(v.begin(), v.end(), sol);
        v.erase(it);
    }
    else{
        auto &que = ungraded_assignments_queues.at(assignment);
        auto it = std::find(que.begin(), que.end(), sol);
        que.erase(it);
    }
    delete sol;
}

bool Course::is_assignment_submitted(const Student* s, const Assignment* assignment)const{
    return student_solutions_map.at(s).find(assignment) != student_solutions_map.at(s).end();
}
bool Course::submit_assignment(const Student* s, const Assignment* assignment, const std::string &answer){
    if(!assignment->can_submit()){
        return false;
    }
    bool is_submitted_before = is_assignment_submitted(s, assignment);
    auto &mp = student_solutions_map.at(s);
    if(is_submitted_before){
        mp.at(assignment)->update_answer(answer);
    }
    else{
        AssignmentSolution* solution_to_add = new AssignmentSolution(assignment, s, answer);
        push_solution(solution_to_add);
    }
    return true;
}
void Course::list_student_assignments(const Student* s,const std::vector<const Assignment*> &assignments, int tabs)const{
    if(assignments.empty()){
        return;
    }
    std::cout << "\n*****************************************\n";
    std::string indent = indenter(tabs);
    auto &solutions_mp = student_solutions_map.at(s);
    for(int i = 0; i < assignments.size(); ++i){
        const Assignment* assignment = assignments[i];
        AssignmentSolution* sol {};
        std::cout << indent << "Assignment " << std::right << std::setw(2) << i + 1 << "- ";
        std::cout << std::left << std::setw(20) << assignment->get_title();
        if(solutions_mp.count(assignment)){
            std::cout << std::left << std::setw(17) << " submitted";
            if(solutions_mp.at(assignment)->is_graded()){
                sol = solutions_mp.at(assignment);
            }
        }
        else{
            std::cout << std::left << std::setw(17) << " NOT submitted";
        }
        std::cout << " - " << std::right << std::setw(2) << (sol ? to_string(sol->get_grade()) : "NA") << " / "
        << std::right << std::setw(2) << assignment->get_full_mark() << "\n";
        if(sol && !sol->get_comment().empty())
            std::cout << indent << "\t-->" << sol->get_comment() << "\n";
    }
    std::cout << "\n*****************************************\n\n";
}
void Course::student_unregister(const Student* s){
    for(auto &[assignmet, sol] : student_solutions_map.at(s)){
        remove_solution(sol);
    }
    student_solutions_map.erase(s);
    student_total_grade.erase(s);
}
void Course::student_register(const Student* s){
    student_total_grade[s];
    student_solutions_map[s];
}
void Course::show_student_grade(const Student* s)const{
    std::cout << "Course code " << std::left << std::setw(10) << code 
    << "| Total submitted " << std::right << std::setw(2) << student_solutions_map.at(s).size()
    << " assignment(s) | Grade " << std::right << std::setw(3) << student_total_grade.at(s)
    << " / " << std::right << std::setw(3) << total_full_mark << "\n";
}
void Course::print()const{
    std::cout << "Course " << std::left << std::setw(20) << name << " | Code " << code << "\n";
}
void Course::print_detailed()const{
    std::cout << "Course " << name << " with Code " << code << " taught by Dr " << doctor->get_name() << "\n";
}
std::vector<const Assignment*> Course::get_available_assignments()const{
    std::vector<const Assignment*> available_to_submit;
    for(auto assignment : all_assignments){
        if(assignment->can_submit()){
            available_to_submit.push_back(assignment);
        }
    }
    return available_to_submit;
}
const std::vector<const Assignment*> &Course::get_all_assignments()const{
    return all_assignments;
}

std::string Course::get_course_name()const{
    return name;
}
std::string Course::get_course_code()const{
    return code;
}
void Course::list_doctor_assignments(const std::vector<const Assignment*> &assignments, int tabs, bool numbered)const{
    if(assignments.empty()){
        return;
    }
    std::cout << "\n*****************************************\n";
    int cnt = 1;
    std::string indent = indenter(tabs);
    for(auto &assignment : assignments){
        if(numbered)
            std::cout << indent << cnt++ << "- ";
        assignment->print(tabs);
    }
    std::cout << "\n*****************************************\n\n";
}
void Course::list_assignment_grades_report(const Assignment* assignment, int tabs)const{
    for(auto &sol : all_assignment_solutions.at(assignment)){
        sol->print_student_grade(tabs);
    }
}
const std::vector<AssignmentSolution*> &Course::get_all_assignment_solutions(const Assignment* assignment)const{
    return all_assignment_solutions.at(assignment);
}
Course::~Course(){
    for(auto &[assignment, sols] : all_assignment_solutions){
        for(auto & sol : sols){
            delete sol;
        }
        delete assignment;
    }
}