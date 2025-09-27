#pragma once
#include <vector>
#include <string>
#include <iomanip>
#include <input_utils.hpp>

#include "Helper.hpp"

template<typename MenuEnum>
class MenuHandler {
private:
    const std::vector<std::string> options;
    const std::string base_title;
    const MenuEnum min_choice;
    const MenuEnum max_choice;
    void show_menu(const std::string &prompt, int tabs = 0) const {
    std::string indent = indenter(tabs);
    if(!prompt.empty()){
        std::cout << indent << prompt;
    }
    indent.push_back('\t');
    for(int i = 0; i < options.size(); ++i){
        std::cout << indent  << std::right << std::setw(2) << i + 1 << ": " << options[i] << "\n";
    }
}

public:
    MenuHandler(const std::vector<std::string>& options, 
              const std::string& base_title,
              MenuEnum min_choice,
              MenuEnum max_choice)
        : options(options)
        , base_title(base_title)
        , min_choice(min_choice)
        , max_choice(max_choice) {}

    MenuEnum show_and_get_choice() const {
        return show_and_get_choice("");
    }

    MenuEnum show_and_get_choice(const std::string& dynamic_title) const {
        std::string full_title = base_title;
        if (!dynamic_title.empty()) {
            if (base_title.back() == '\n') {
                full_title.pop_back();  // Remove trailing newline
            }
            full_title += " " + dynamic_title + "\n";
        }
        
        show_menu(full_title);
        int choice = read_validated_input<int>("Enter your choice: ", 0);
        
        if (choice >= static_cast<int>(min_choice) && 
            choice <= static_cast<int>(max_choice)) {
            return static_cast<MenuEnum>(choice);
        }
        
        return static_cast<MenuEnum>(0);  // InvalidChoice
    }
};