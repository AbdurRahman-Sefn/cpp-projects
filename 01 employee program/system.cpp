#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cassert>
#include <vector>
int to_int(std::string str){
    int num = 0;
    std::istringstream iss(str);
    iss>>num;
    return num;
}

class EmployeeSystem
{
    static const int MIN_SALARY = 2000;
    static const int MAX_SALARY = 1e5;
    static const int MIN_AGE = 16;
    static const int MAX_AGE = 60;
    //add print delete update
    struct Employee
    {
        static const char DELIM = '|';
        static bool is_valid_salary(int salary){
            return salary >= MIN_SALARY && salary <= MAX_SALARY;
        }
        static bool is_valid_name(std::string name){
            for(char c : name){
                if(!islower(c) && c != ' '){
                    return false;
                }
            }
            return !name.empty() && name[0] != ' ' && name.size() > 2;
        }
        static bool is_valid_age(int age){
            return age >= MIN_AGE && age <= MAX_AGE;
        }
        static bool is_valid_gender(char gender){
            return gender == 'M' || gender == 'F';
        }
        /**
         * returns 1 for invalid name
         *         2 for invalid age
         *         3 for invalid salary
         *         4 for invalid fender
         * 
         * returns 0 for valid data
         */
        int check_correctness() const{
            if(!is_valid_name(name)){
                return 1;
            }
            else if(!is_valid_age(age)){
                return 2;
            }
            else if(!is_valid_salary(salary)){
                return 3;
            }
            else if(!is_valid_gender(gender)){
                return 4;
            }
            return 0;
        }
        void print() const{
            std::cout << "Name: " << name << "\n";
            std::cout << "Age: " << age << "\n";
            std::cout << "Salary: " << salary << "\n";
            std::cout << "Gender: " << gender << "\n";
        }
        std::string name;
        int age{-1};
        int salary{-1};
        char gender{'N'};
        Employee(std::string name, int age, int salary, char gender)
        : name(name), salary(salary), age(age), gender(gender){}
        Employee(std::string emp_str){
            std::istringstream iss(emp_str);
            //std::string temp;
            getline(iss, name, DELIM);
            iss >> age;
            iss.ignore();
            iss >> salary;
            iss.ignore();
            iss >> gender;
        }
        Employee() = default;
        std::string to_str(){
            std::ostringstream oss;
            oss << name << DELIM << age << DELIM << salary << DELIM << gender;
            return oss.str();
        }
    };
    std::map <std::string, Employee> employees;
    std::string read_employee_name(){
        std::string ret;
        std::cout << "Enter employee name: ";
        getline(std::cin, ret);
        if(ret == "")
        getline(std::cin, ret);
        while(ret.size() && ret.back() == ' ')
            ret.pop_back();
        if(ret.empty()){
            return "";
        }
        int start = 0;
        while(start < ret.size() && ret[start++] == ' ');
        return ret.substr(start - 1);
    }
    std::string read_name(){
        std::string ret;
        while(ret == ""){
            ret = read_employee_name();
            if(employees.find(ret) != employees.end()){
                std::cout << "\n this name already exists, try another one\n";
                ret = "";
            }
            else if(! Employee::is_valid_name(ret)){
                std::cout << "\nInvalid name. Try again\n";
                ret = "";
            }
        }
        return ret;
    }
    int read_salary(){
        int salary = -1;
        std::cout << "Enter employee salary: ";
        std::cin >> salary;
        while(!Employee::is_valid_salary(salary)){
            std::cout << "\nInvalid salary. Try again\n";
            std::cin >> salary;
        }
        return salary;
    }
    int read_age(){
        int age = -1;
        std::cout << "Enter employee age: ";
        std::cin >> age;
        while(!Employee::is_valid_age(age)){
            std::cout << "\nInvalid age. Try again\n";
            std::cin >> age;
        }
        return age;
    }
    char read_gender(){
        char gender = -1;
        std::cout << "Enter employee gender: ";
        std::cin >> gender;
        while(!Employee::is_valid_gender(gender)){
            std::cout << "\nInvalid gender. Try again\n";
            std::cin >> gender;
        }
        return gender;
    }
    void add_employee(){
        std::string name = read_name();
        employees[name] = Employee(name, read_age(), read_salary(), read_gender());
    }
    void print_employees(){
        std::cout << "\n******************\n";
        for(const auto &[name, emp] : employees){
            emp.print();
            std::cout << "\n";
        }
        std::cout << "******************";
    }
    void erase(std::string name){
        auto it = employees.find(name);
        if(it == employees.end()){
            std::cout << "\nThis name does not exist!\n";
            return;
        }
        employees.erase(it);
    }
    void delete_by_age(){
        int start = -1, end = -1;
        std::cout << "Enter limits of age to be deleted: ";
        std::cin >> start >> end;
        if(end < start)
            std::swap(start, end);
        if(start > MAX_AGE || end < MIN_AGE){
            return;
        }
        std::vector<std::string> removed;
        for(auto &[name, emp] : employees){
            if(emp.age >= start && emp.age <= end){
                removed.push_back(name);
            }
        }
        for(auto &key : removed){
            employees.erase(key);
        }
        std::cout << removed.size() << " employee(s) removed\n";
    }
    void update_salary(std::string name){
        auto it = employees.find(name);
        if(it == employees.end()){
            std::cout << "\nThis name does not exist!\n";
            return;
        }
        employees[name].salary = read_salary();
    }
    void load_database(){
        std::ifstream data("data.txt");
        if(data.fail()){
            throw  "\ncan't open file!\n";
        }
        std::string emp_str;
        employees.clear();
        while(getline(data, emp_str) && emp_str.size()){
            Employee emp(emp_str);
            employees[emp.name] = emp;
        }
        data.close();
    }
    void update_database(){
        std::ofstream data("data.txt");
        if(data.fail()){
            throw  "\ncan't open file!\n";
        }
        for(auto &[name, emp] : employees){
            data << emp.to_str() << "\n";
        }
        data.close();
    }
public:
    EmployeeSystem(){
        std::cout << "\n*******Welcome!*******\n";
    }
    void run(){
        while(true){
            load_database();
            int choice{-1};
            std::cout << "\n\nEnter Your choice: \n";
            std::cout << "\t1) Add new employee\n";
            std::cout << "\t2) print all employees\n";
            std::cout << "\t3) delete by age\n";
            std::cout << "\t4) update salary by name\n";
            std::cout << "\t5) delete an employee\n";
            std::cout << "\t6) Exit\n";
            std::cin >> choice;
            if(choice == 1){
                add_employee();
            }
            else if(choice == 2){
                print_employees();
            }
            else if(choice == 3){
                delete_by_age();
            }
            else if(choice == 4){
                std::string name = read_employee_name();
                update_salary(name);
            }
            else if(choice == 5){
                std::string name = read_employee_name();
                erase(name);
            }
            else if(choice == 6){
                std::cout << "\n*******Bye!*******\n";
                break;
            }
            update_database();
        }
        update_database();
    }
};

int main(){
    EmployeeSystem system;
    system.run();
    return 0;
}
