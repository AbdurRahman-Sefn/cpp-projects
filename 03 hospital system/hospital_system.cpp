#include <iostream>
#include <iomanip>
#include <cassert>
#include <deque>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

int to_int(std::string str){
    std::istringstream iss(str);
    int num{};
    iss >> num;
    return num;
}
class HospitalSystem{
    const int MAX_SPEC = 20;
    struct Patient{
        bool status{false};
        std::string name;
        Patient(std::string name , bool status) : name(name), status(status){}
        Patient() = default;
        Patient(std::string str){
            if (str.length() < 2 || !is_valid_name(str.substr(1))) {
                // Handle the error gracefully. For now, let's create an invalid patient.
                name = "INVALID_DATA";
                status = false;
                std::cerr << "Warning: Corrupted patient data found in file: " << str << std::endl;
            } else {
                status = (str[0] == '1');
                name = str.substr(1);
            }
        }
        std::string to_str() const{
            std::ostringstream oss;
            oss << status << name;
            return oss.str();
        }
        void print()const{
            std::cout << "\t" << std::left << std::setw(25)<< name;
            std::cout << (status ? "\turgent\n" : "\tregular\n");
        }
    };
    struct HospitalQueue{
        int id{-1};
        const char DELIM = '|';
        const int MAX_QUEUE = 5;
        std::deque<Patient> patients;
        bool push(Patient &p){
            if(patients.size() >= MAX_QUEUE){
                return false;
            }
            if(p.status){
                patients.push_front(p);
            }
            else{
                patients.push_back(p);
            }
            return true;
        }
        std::pair<bool, Patient> pop(){
            Patient ret = Patient();
            if(patients.empty()){
                return {false, ret};
            }
            else{
                ret = patients.front();
                patients.pop_front();
                return {true, ret};
            }
        }
        void operator=(const HospitalQueue &other){
            id = other.id;
            patients = other.patients;
        }
        HospitalQueue(int id = -1) : id(id){}
        HospitalQueue(std::string str) {
            std::string part;
            std::istringstream iss(str);
            
            // Read specialization ID
            if (getline(iss, part, DELIM)) {
                try {
                    id = std::stoi(part); // Use std::stoi for safe conversion
                } catch (const std::exception& e) {
                    std::cerr << "Warning: Corrupted queue data in file. Invalid ID: " << part << std::endl;
                    id = -1; // Set to an invalid state
                    return;  // Stop parsing this corrupted line
                }
            }

            // Read patients
            while (getline(iss, part, DELIM)) {
                if (!part.empty()) // Avoid creating patients from empty parts
                    patients.push_back(Patient(part));
            }
        }
        bool is_empty()const{
            return patients.empty();
        }
        std::string to_str()const{
            std::ostringstream oss;
            oss << id << DELIM;
            for(auto &p : patients){
                oss << p.to_str() << DELIM;
            }
            return oss.str();
        }
        void print()const{
            if(patients.empty()){
                return;
            }
            std::cout << "There are " << patients.size() << " in specialization " << id + 1 << ": \n";
            for(auto &p : patients){
                p.print();
            }
        }
    };
    std::vector<HospitalQueue> specializations;
    static bool is_valid_name(std::string name){
        if(name.size() < 3){
            return false;
        }
        for(char c : name){
            if(!islower(c) && c != ' '){
                return false;
            }
        }
        return true;
    }
    static void remove_trailing_spaces(std::string &ret){
        while(!ret.empty() && ret.back() == ' '){
            ret.pop_back();
        }
        int start = 0;
        while(!ret.empty() && ret[start++] == ' ');
        ret = ret.substr(start - 1);
    }
    static std::string read_name(){
        std::string ret;
        std::cout << "\tEnter name: ";
        getline(std::cin, ret);
        remove_trailing_spaces(ret);
        while(!is_valid_name(ret)){
            std::cout << "\tInvlid name. Try again: ";
            getline(std::cin, ret);
        }
        return ret;
    }
    static int read_in_range(int start, int end){
        int ret;
        while (!(std::cin >> ret) || ret < start || ret > end) {
            std::cout << "\tWrong Input. Try again: ";
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input line
        }
        // ALWAYS clean up the buffer after a `>>` operation if a `getline` might follow.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return ret;
    }
    int read_specialization(){
        int ret = -1;
        std::cout << "\tEnter specialization[1 - " << MAX_SPEC << "]: ";
        ret = read_in_range(1, MAX_SPEC);
        return ret - 1;
    }
    static bool read_status(){
        std::cout << "\tEnter status(0 or 1): ";
        int status = read_in_range(0, 1);
        return status;
    }
    void add_patient(){
        int spec = read_specialization();
        specializations[spec].id = spec;
        Patient p = Patient(read_name(), read_status());
        if(!specializations[spec].push(p)){
            std::cout << "Sorry, we cannot add anymore patients at this specialization\n";
        }
    }
    void get_next_patient(){
        int spec = read_specialization();
        auto [success, p] = specializations[spec].pop();
        if(success){
            std::cout << "\t" << p.name << ", please go with the Dr\n";
        }
        else{
            std::cout << "\tNo patients at the moment. Have rest, Dr\n";
        }
    }
    void print_all_patients()const{
        std::cout << "\n***************\n";
        for(auto &spec : specializations){
            if(spec.id != -1){
                spec.print();
            }
        }
        std::cout << "\n***************\n";
    }
    void load_database(){
        std::ifstream database("patients.txt");
        std::string spec_str;
        specializations.clear();
        specializations.resize(MAX_SPEC);
        while(getline(database, spec_str)){
            HospitalQueue spec = HospitalQueue(spec_str);
            specializations[spec.id] = spec;
        }
        database.close();
    }
    void update_data_base(){
        std::ofstream database("patients.txt");
        for(auto &spec : specializations){
            if(!spec.is_empty())
            database << spec.to_str() << "\n";
        }
        database.close();
    }
public:
    void run(){
        std::cout << "\n**********Welcome**********\n";
        load_database();
        while(true){
            std::cout << "\nEnter your choice: \n";
            std::cout << "\t1) Add a new patient\n";
            std::cout << "\t2) Print all patients\n";
            std::cout << "\t3) Get next patient\n";
            std::cout << "\t4) Exit\n";
            int choice = read_in_range(1, 4);
            switch (choice)
            {
            case 1:
                add_patient();
                break;
            case 2:
                print_all_patients();
                break;
            case 3:
                get_next_patient();
                break;
            case 4:
                update_data_base();
                std::cout << "\n************Bye************\n";
                return;                
            }
        }
    }
};


int main(){
    HospitalSystem system;
    system.run();
    return 0;
}