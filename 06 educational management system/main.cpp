#include "EducationalManageMentSystem.hpp"

int main(){
    EducationalManagemenentSystem system;
    system.run();
    return 0;
}

// indents are deep but i fixed it in the code

/*

Loading dummy data...
Dummy data loaded successfully.


Educational Management System:
                 1: Login
                 2: Sign up
                 3: Shutdown system
Enter your choice: 1
Enter username: mostafa
Enter password: 111

        Welcome Dr Mostafa Saad !

Main menu: for Doctor Mostafa Saad
                 1: list my courses
                 2: create a course
                 3: view a course
                 4: logout
Enter your choice: 3

*****************************************
        1- Course Programming 1        | Code CS101
        2- Course Data Structures      | Code CS213

*****************************************


which ith [1 - 2] course to view ?: 1

Course menu: Programming 1
                 1: list assignments
                 2: create an assignment
                 3: view an assignment
                 4: back
Enter your choice: 1     

*****************************************
        Assignment 1
        Assignment 2

*****************************************


Course menu: Programming 1
                 1: list assignments
                 2: create an assignment
                 3: view an assignment
                 4: back
Enter your choice: 3

*****************************************
        1- 
        Assignment 1
        2- 
        Assignment 2

*****************************************


which ith [1 - 2] Assignment to view ?: 1

Assignment menu: Assignment 1
                 1: print content
                 2: list grades report
                 3: view a solution from the queue
                 4: pop a solution from the queue
                 5: list solutions
                 6: view a solution
                 7: back
Enter your choice: 3

Solution menu: of Student Mona Youssef
                 1: print content
                 2: set grade
                 3: set comment
                 4: back
Enter your choice: 2
Enter the grade: 7

Assignment menu: Assignment 1
                 1: print content
                 2: list grades report
                 3: view a solution from the queue
                 4: pop a solution from the queue
                 5: list solutions
                 6: view a solution
                 7: back
Enter your choice: 3
        This queue is empty!

Assignment menu: Assignment 1
                 1: print content
                 2: list grades report
                 3: view a solution from the queue
                 4: pop a solution from the queue
                 5: list solutions
                 6: view a solution
                 7: back
Enter your choice: 7

Course menu: Programming 1
                 1: list assignments
                 2: create an assignment
                 3: view an assignment
                 4: back
Enter your choice: 4

Main menu: for Doctor Mostafa Saad
                 1: list my courses
                 2: create a course
                 3: view a course
                 4: logout
Enter your choice: 3

*****************************************
        1- Course Programming 1        | Code CS101
        2- Course Data Structures      | Code CS213

*****************************************


which ith [1 - 2] course to view ?: 2

Course menu: Data Structures
                 1: list assignments
                 2: create an assignment
                 3: view an assignment
                 4: back
Enter your choice: 2
Enter assignment title: stacks
Enter assignment content: implement a stack using arrays
Enter the full mark grade: 12
        Assignment stacks created successfully!

Course menu: Data Structures
                 1: list assignments
                 2: create an assignment
                 3: view an assignment
                 4: back
Enter your choice: 4

Main menu: for Doctor Mostafa Saad
                 1: list my courses
                 2: create a course
                 3: view a course
                 4: logout
Enter your choice: 4

Educational Management System:
                 1: Login
                 2: Sign up
                 3: Shutdown system
Enter your choice: 1
Enter username: ahmed
Enter password: 123

        Welcome Ahmed Ali !

Main menu: for Student Ahmed Ali
                 1: register in a course
                 2: list my courses
                 3: view a course
                 4: grades report
                 5: logout
Enter your choice: 4
Course code CS101     | Total submitted  1 assignment(s) | Grade   8 /  18
Course code MATH101   | Total submitted  1 assignment(s) | Grade   0 /  12

Main menu: for Student Ahmed Ali
                 1: register in a course
                 2: list my courses
                 3: view a course
                 4: grades report
                 5: logout
Enter your choice: 3

*****************************************
        1- Course Programming 1        | Code CS101
        2- Course Calculus 1           | Code MATH101

*****************************************


which ith [1 - 2] course to view ?: 1

*****************************************
        Assignment  1- Assignment 1         submitted        -  8 / 10
        Assignment  2- Assignment 2         NOT submitted    - NA /  8

*****************************************


Course menu: Programming 1
                 1: unregister from the course
                 2: submit a solution
                 3: back
Enter your choice: 2
Course Programming 1 with Code CS101 taught by Dr Mostafa Saad
Course has 2 assignments

*****************************************
        Assignment  1- Assignment 1         submitted        -  8 / 10
        Assignment  2- Assignment 2         NOT submitted    - NA /  8

*****************************************


which ith [1 - 2] assignment to view ?: 2
        Assignment 2
        Content: 
                --> Explain loops in C++.
Enter the solution: This is my detailed explanation of loops
        Successful submission!

Course menu: Programming 1
                 1: unregister from the course
                 2: submit a solution
                 3: back
Enter your choice: 3

Main menu: for Student Ahmed Ali
                 1: register in a course
                 2: list my courses
                 3: view a course
                 4: grades report
                 5: logout
Enter your choice: 5

Educational Management System:
                 1: Login
                 2: Sign up
                 3: Shutdown system
Enter your choice: 1
Enter username: hany
Enter password: wrong password
        Invalid format. Please try again.
wrong_password

        Invalid username or password!

Educational Management System:
                 1: Login
                 2: Sign up
                 3: Shutdown system
Enter your choice: 1
Enter username: omar
Enter password: 123

        Welcome Omar Khaled !

Main menu: for Student Omar Khaled
                 1: register in a course
                 2: list my courses
                 3: view a course
                 4: grades report
                 5: logout
Enter your choice: 2
        There is no courses to display!

Main menu: for Student Omar Khaled
                 1: register in a course
                 2: list my courses
                 3: view a course
                 4: grades report
                 5: logout
Enter your choice: 1

*****************************************
        1- Course Programming 1        | Code CS101
        2- Course Data Structures      | Code CS213
        3- Course Calculus 1           | Code MATH101
        4- Course Physics 1            | Code PHY101

*****************************************


which ith [1 - 4] course to view ?: 4

Main menu: for Student Omar Khaled
                 1: register in a course
                 2: list my courses
                 3: view a course
                 4: grades report
                 5: logout
Enter your choice: 2

*****************************************
        1- Course Physics 1            | Code PHY101

*****************************************


Main menu: for Student Omar Khaled
                 1: register in a course
                 2: list my courses
                 3: view a course
                 4: grades report
                 5: logout
Enter your choice: 5

Educational Management System:
                 1: Login
                 2: Sign up
                 3: Shutdown system
Enter your choice: 1
Enter username: hany
Enter password: 222

        Welcome Dr Hany Mohamed !

Main menu: for Doctor Hany Mohamed
                 1: list my courses
                 2: create a course
                 3: view a course
                 4: logout
Enter your choice: 3

*****************************************
        1- Course Calculus 1           | Code MATH101
        2- Course Physics 1            | Code PHY101

*****************************************


which ith [1 - 2] course to view ?: 2

Course menu: Physics 1
                 1: list assignments
                 2: create an assignment
                 3: view an assignment
                 4: back
Enter your choice: 1
        There is no assignment for now!

Course menu: Physics 1
                 1: list assignments
                 2: create an assignment
                 3: view an assignment
                 4: back
Enter your choice: 3

There are no Assignments to display.

Course menu: Physics 1
                 1: list assignments
                 2: create an assignment
                 3: view an assignment
                 4: back
Enter your choice: 4

Main menu: for Doctor Hany Mohamed
                 1: list my courses
                 2: create a course
                 3: view a course
                 4: logout
Enter your choice: 4

Educational Management System:
                 1: Login
                 2: Sign up
                 3: Shutdown system
Enter your choice: 3
[1] + Done   
*/
