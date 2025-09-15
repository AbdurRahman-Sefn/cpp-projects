#include "Book.hpp"
#include "User.hpp"
#include <sstream>


Book::Book(int id, std::string name, int quantity): id(id), name((trim(name), name)), quantity(quantity){
    std::ostringstream oss;
    oss << "\'" << std::left << std::setw(BOOK_NAME_WIDTH) << name << "\'";
    formatted_name = oss.str();
}

const std::string &Book::get_name_formatted()const{
    return formatted_name;
}

void Book::print_header(int tabs) {
    std::string indent = indenter(tabs);
    
    int total_width = BOOK_NAME_WIDTH + ID_WIDTH + QTY_WIDTH + BORROWED_WIDTH + 13; // +13 for separators and padding
    std::string decorator(total_width, '-');

    std::cout << indent << decorator << "\n";
    std::cout << indent
              << "| " << std::left << std::setw(BOOK_NAME_WIDTH) << "Name" << " |"
              << " "  << std::right << std::setw(ID_WIDTH) << "ID" << " |"
              << " "  << std::right << std::setw(QTY_WIDTH) << "Total Quantity" << " |"
              << " "  << std::right << std::setw(BORROWED_WIDTH) << "Total Borrowed" << " |\n";
    std::cout << indent << decorator << "\n";
}

void Book::print(int tabs) const {
    std::string indent = indenter(tabs);
    std::cout << indent
              << "| " << std::left << std::setw(BOOK_NAME_WIDTH) << name << " |"
              << " "  << std::right << std::setw(ID_WIDTH) << id << " |"
              << " "  << std::right << std::setw(QTY_WIDTH) << quantity << " |"
              << " "  << std::right << std::setw(BORROWED_WIDTH) << borrowed << " |\n";
}

std::string Book::get_name()const{
    return name;
}

int Book::get_id()const{
    return id;
}
bool Book::is_available()const{
    return quantity > 0 && borrowed < quantity;
}

Book::Book(const std::string &book_str){
    std::istringstream iss(book_str);
    std::string int_temp{-1};
    getline(iss, name, DELIM);
    getline(iss, int_temp, DELIM);
    id = std::stoi(int_temp);
    getline(iss, int_temp, DELIM);
    quantity = std::stoi(int_temp);
    getline(iss, int_temp, DELIM);
    borrowed = std::stoi(int_temp);
}

std::string Book::to_string() const{
    std::ostringstream oss;
    oss << name << DELIM << id << DELIM << quantity << DELIM << borrowed << DELIM;
    return oss.str();
}