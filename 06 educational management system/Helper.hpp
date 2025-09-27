
#pragma once

#include <iostream>
#include <vector>
#include <input_utils.hpp>


std::string indenter(int tabs);
std::string to_string(int);
void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s);
std::basic_istream<char> &read_and_trim(std::istream &is, std::string &str);
bool is_in_range(int val, int min, int max);

template<typename T>
T select_from(const std::vector<T> &items, std::string item_type){
    int size = items.size();
     if(!size) {
        std::cout << "\nThere are no " << item_type << "s to display.\n";
        return nullptr;
    }
    int choice = read_validated_input<int>("\nwhich ith [1 - " + to_string(size) + "] " + item_type + " to view ?: ", 0);
    while(!is_in_range(choice, 1, size)){
        choice = read_validated_input<int>("\nYour choice must be between 1 and " + to_string(size) + ". Try again: ");
    }
    return items[choice - 1];
}

