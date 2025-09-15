#include "Helper.hpp"

std::string indenter(int n){
    std::string ret;
    while(n-- > 0){
        ret.push_back('\t');
    }
    return ret;
}

void show_menu(const std::vector<std::string> &options, const std::string &prompt, int tabs){
    std::string indent = indenter(tabs);
    if(!prompt.empty()){
        std::cout << indent << prompt << ":\n";
    }
    indent.push_back('\t');
    for(int i = 0; i < options.size(); ++i){
        std::cout << indent << i + 1 << ") " << options[i] << "\n";
    }
}
