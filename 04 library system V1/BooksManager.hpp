#pragma once
#include "Book.hpp"
#include "User.hpp"
#include "Dictionary.hpp"
#include <input_utils.hpp>

class BooksManager{
    std::map<int, Book*> ids_dictionary;
    Dictionary <Book>names_dictionary;
public:
    std::pair<const Book*, std::string> enter_a_book()const;
    bool add_book();
    void search_books_by_prefix();
    void print_who_borrowed_book_by_name()const;
    void print_library_by_id() const;
    void print_library_by_name() const;
    bool user_borrow_book(User *usr, Book *book);
    bool user_return_book(User *usr, Book *book);
    ~BooksManager();
};
