#include "Helper.hpp"
#include <iomanip>

static const std::string WHITESPACE = " \n\r\t\f\v";

std::string indenter(int n){
    if(n < 0)
        n = 0;
    return std::string (n, '\t');
}
std::string to_string(int num){
    std::ostringstream oss;
    oss << num;
    return oss.str();
}

void ltrim(std::string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    if (start == std::string::npos) {
        s.clear();
    } else {
        s.erase(0, start);
    }
}


void rtrim(std::string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    if (end == std::string::npos) {
        s.clear();
    } else {
        s.erase(end + 1);
    }
}


void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}
std::basic_istream<char> &read_and_trim(std::istream &is, std::string &str){
    auto &ret = getline(is, str);
    trim(str);
    return ret;
}

bool is_in_range(int val, int min, int max){
    return val >= min && val <= max;
}
