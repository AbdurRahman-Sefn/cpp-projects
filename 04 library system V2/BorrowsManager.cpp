#include "BorrowsManager.hpp"
#include <algorithm>
#include <fstream>

const std::vector<BorrowOperation*> BorrowsManager::NA;

void BorrowsManager::create_borrow_link(const User *user,const Book *book){
    BorrowOperation *operation = new BorrowOperation(user, book);
    borrows_by_book[book].push_back(operation);
    borrows_by_user[user].push_back(operation);
}

BorrowResult BorrowsManager::borrow_book(User* user, Book* book){
    if(!book->is_available()){
        return BorrowResult::BOOK_NOT_AVAILABLE;
    }
    const auto &it = borrows_by_user.find(user);
    if(it != borrows_by_user.cend()){
        if(it->second.size() >= MAX_BORROWS_PER_USER){
            return BorrowResult::USER_REACHED_MAX_BORROWED_BOOKS;
        }
        int freq = 0;
        for(const auto &operation : it->second){
            if(operation->book == book)
                freq++;
        }
        if(freq >= MAX_BORROWS_REPETITION)
            return BorrowResult::USER_REACHED_MAX_REPETITIONS;
    }
    create_borrow_link(user, book);
    return BorrowResult::SUCCESS;
}
bool BorrowsManager::return_book(User* user, Book* book) {
    auto it_user = borrows_by_user.find(user);
    if (it_user == borrows_by_user.end()) {
        return false;
    }

    auto &operations = it_user->second;
    auto operation_it = std::find_if(operations.begin(), operations.end(),
        [book](const BorrowOperation* op) { return op->book == book; });

    if (operation_it == operations.end()) {
        return false;
    }

    BorrowOperation* operation = *operation_it;
    operations.erase(operation_it);

    auto &book_operations = borrows_by_book[book];
    auto book_operation_it = std::find(book_operations.begin(), book_operations.end(), operation);
    
    if (book_operation_it == book_operations.end()) {
        throw std::invalid_argument("Incompatible Data");
    }

    book_operations.erase(book_operation_it);
    delete operation;
    return true;
}
const std::vector<BorrowOperation*> &BorrowsManager::get_book_history(Book *book) const{
    auto it = borrows_by_book.find(book);
    return it != borrows_by_book.cend() ? it->second : NA;
}
const std::vector<BorrowOperation*> &BorrowsManager::get_user_history(User *user) const{
    auto it = borrows_by_user.find(user);
    return it != borrows_by_user.cend() ? it->second : NA;
}
BorrowsManager::~BorrowsManager(){
    update_database();
    for(auto &[key, v] : borrows_by_book){
        for(auto &operation : v){
            delete operation;
        }
    }
}
void BorrowsManager::update_database(){
    std::ofstream data("BorrowOperations.txt");
    if(data.fail()){
        std::cerr << "CAN't open database of borrow operations --> \"BorrowOperations.txt\"";
        return;
    }
    for(auto &[book, operations] : borrows_by_book){
        for(auto &operation : operations){
            data << operation->to_str() << "\n";
        }
    }
    data.close();
}

void BorrowsManager::deserialize(const std::string &borrow_str, int &user_id, int &book_id){
    BorrowOperation::deserialize(borrow_str, user_id, book_id);
}