#include "User.hpp"

constexpr int USER_NAME_WIDTH = 40;
constexpr int USER_ID_WIDTH = 10;

void User::borrow(Book* book){
    borrowed_books[book]++;
}
bool User::return_(Book* book){
    if(borrowed_books.find(book) == borrowed_books.end()){
        return false;
    }
    if(--borrowed_books[book] == 0){
        borrowed_books.erase(book);
    }
    return true;
}

User::User(int id, std::string name): id(id), name(name){}
std::string User::get_name() const{
    return name;
}


void User::print_header(int tabs) {
    std::string indent = indenter(tabs);
    

    int total_width = USER_NAME_WIDTH + USER_ID_WIDTH + 9; // +9 for separators and padding
    std::string decorator(total_width, '-');

    std::cout << indent << decorator << "\n";
    std::cout << indent
              << "| " << std::left << std::setw(USER_NAME_WIDTH) << "Name" << " |"
              << " "  << std::right << std::setw(USER_ID_WIDTH) << "ID" << " |\n";
    std::cout << indent << decorator << "\n";
}


void User::print(int tabs) const {
    std::string indent = indenter(tabs);
    std::cout << indent

              << "| " << std::left << std::setw(USER_NAME_WIDTH) << name << " |"

              << " "  << std::right << std::setw(USER_ID_WIDTH) << id << " |\n";
}



void User::print_borrowed_books(int tabs) const {
    std::string indent = indenter(tabs);
    
    if (borrowed_books.empty()) {
        return;
    }

    std::cout << indent << "--> Borrowed Books:\n";
    for (auto const& [book, freq] : borrowed_books) {

        std::cout << indent << "\t- " << freq << " book(s) of '" << book->get_name() << "'\n";
    }
}
