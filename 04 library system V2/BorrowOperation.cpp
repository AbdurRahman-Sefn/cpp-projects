#include "BorrowOperation.hpp"
#include <sstream>

BorrowOperation::BorrowOperation(const User* user,const Book* book) : user(user), book(book){}

std::string BorrowOperation::to_str()const{
    std::ostringstream oss;
    oss << user->get_id() << DELIM << book->get_id() << DELIM;
    return oss.str();
}

void BorrowOperation::deserialize(const std::string &borrow_str, int &user_id, int &book_id){
    std::istringstream iss(borrow_str);
    iss >> user_id;
    iss.ignore();
    iss >> book_id;
}