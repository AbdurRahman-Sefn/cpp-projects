#pragma once
#include "Book.hpp"
#include "User.hpp"
#include "BorrowOperation.hpp"
#include <Dictionary.hpp>
#include <input_utils.hpp>

class BooksManager{
    std::map<int, Book*> ids_dictionary;
    Dictionary <Book>names_dictionary;
    void load_database();
    void update_database()const;
    void push_book(Book *book);
    void clear();
public:
    BooksManager();
    BooksManager(const BooksManager &) = delete;
    BooksManager &operator=(const BooksManager &) = delete;
    std::pair<Book*, std::string> enter_a_book();
    AddBookResult add_book(std::string &book_name_formatted);
    void search_books_by_prefix();
    void increment_book(Book *book);
    void decrement_book(Book *book);
    void print_borrowed_books(const std::vector<BorrowOperation*> &operations) const;
    void print_library_by_id() const;
    void print_library_by_name() const;
    const Book* get_book_by_id(int id)const;
    ~BooksManager();
};
