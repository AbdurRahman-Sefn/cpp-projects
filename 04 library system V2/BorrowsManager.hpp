#pragma once
#include "User.hpp"
#include "Book.hpp"
#include "BorrowOperation.hpp"

class LibrarySystem;

class BorrowsManager
{
private:
    static const int MAX_BORROWS_PER_USER = 5;
    static const int MAX_BORROWS_REPETITION = 1;
    static const std::vector<BorrowOperation*> NA;
    std::unordered_map<const User*, std::vector<BorrowOperation*>> borrows_by_user;
    std::unordered_map<const Book*, std::vector<BorrowOperation*>> borrows_by_book;
    void create_borrow_link(const User *user,const Book *book);
    void update_database();
    static void deserialize(const std::string &borrow_str, int &user_id, int &book_id);
    friend LibrarySystem;
public:
    BorrowsManager(const BorrowsManager&) = delete;
    BorrowsManager &operator=(const BorrowsManager&) = delete;
    BorrowsManager() = default;
    bool return_book(User* user, Book* book);
    BorrowResult borrow_book(User* user, Book* book);
    const std::vector<BorrowOperation*> &get_book_history(Book *book) const;
    const std::vector<BorrowOperation*> &get_user_history(User *user) const;
    ~BorrowsManager();
};