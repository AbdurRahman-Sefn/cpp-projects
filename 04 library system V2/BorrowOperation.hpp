#pragma once
#include "User.hpp"
#include "Book.hpp"

enum class BorrowResult {
    SUCCESS,
    BOOK_NOT_AVAILABLE,
    USER_REACHED_MAX_BORROWED_BOOKS,
    USER_REACHED_MAX_REPETITIONS
};

class BorrowOperation{
public:
    friend class BorrowsManager;
    const User * const user;
    const Book *const book;
private:
    static void deserialize(const std::string &borrow_str, int &user_id, int &book_id); 
    const static char DELIM = '|';
    BorrowOperation(const User* user,const Book* book);
    std::string to_str()const;
};
