#include "LibrarySystem.hpp"
#include <fstream>

LibrarySystem::LibrarySystem(){
    load_borrows_database();
}

void LibrarySystem::load_borrows_database(){
    std::ifstream data("BorrowOperations.txt");
    if(data.fail()){
        data.close();
        throw std::invalid_argument("CAN't open database of borrow operations --> \"BorrowOperations.txt\"");
    }
    std::string borrow_str;
    while(read_and_trim(data, borrow_str)){
        int user_id{-1};
        int book_id{-1};
        borrows_manager.deserialize(borrow_str, user_id, book_id);
        const User *user = users_manager.get_user_by_id(user_id);
        const Book *book = books_manager.get_book_by_id(book_id);
        borrows_manager.create_borrow_link(user, book);
    }
}

LibrarySystem::VerificationResult LibrarySystem::verify(){
    auto [book_ptr, book_name] = books_manager.enter_a_book();
    if(!book_ptr){
        std::cout << "\tBook is not existed!\n";
        return VerificationResult();
    }
    auto [usr_ptr, usr_name] = users_manager.enter_user();
    if(!usr_ptr){
        std::cout << "\tUser is not existed!\n";
        return VerificationResult();
    }
    return VerificationResult{true, const_cast<User*>(usr_ptr), const_cast<Book*>(book_ptr)};
}
void LibrarySystem::borrow_book(){
    VerificationResult verification = verify();
    if(!verification.success)
        return;
    BorrowResult borrow_request = borrows_manager.borrow_book(verification.user, verification.book);
    std::cout << "\t";
    switch (borrow_request)
    {
    case BorrowResult::SUCCESS:
        books_manager.decrement_book(verification.book);
        std::cout << "Book " << verification.book->get_name_formatted() << " is borrowed by User "
                << verification.user->get_name_formatted()<< "\n";
        break;
    case BorrowResult::BOOK_NOT_AVAILABLE:
        std::cout << "Book " << verification.book->get_name_formatted() << " is not available for now\n";
        break;
    case BorrowResult::USER_REACHED_MAX_BORROWED_BOOKS:
        std::cout << "User " << verification.user->get_name_formatted() << " has reached maximum limit of borrowed books. Try return a one\n";
        break;
    case BorrowResult::USER_REACHED_MAX_REPETITIONS:
        std::cout << "User " << verification.user->get_name_formatted() << " has reached maximum limit of borrowing this book. Try return a one\n";
        break;
    }
}
void LibrarySystem::return_book(){
    VerificationResult verification = verify();
    if(!verification.success)
        return;
    bool return_request = borrows_manager.return_book(verification.user, verification.book);
    if(return_request){
        books_manager.increment_book(verification.book);
        std::cout << "\tBook " << verification.book->get_name_formatted() << " is returned by User "
                  << verification.user->get_name_formatted()<< "\n";
    }
    else{
        std::cout << "\tThis user did not borrow this book before.\n";
    }
}

void LibrarySystem::print_who_borrowed_book_by_name(){
    auto[book, book_name] = books_manager.enter_a_book();
    if(!book){
        std::cout << "\tThere is no book with such name.\n";
        return;
    }
    const std::vector<BorrowOperation*> &book_history = borrows_manager.get_book_history(book);
    users_manager.print_borrowers(book_history);
}

void LibrarySystem::print_user_borrowed_books(){
    auto [user, user_name] = users_manager.enter_user();
    if(!user){
        std::cout << "\tThere is no users with such name.\n";
        return;
    }
    const std::vector<BorrowOperation*> &user_history = borrows_manager.get_user_history(user);
    books_manager.print_borrowed_books(user_history);
}

void LibrarySystem::add_book(){
    std::string book_added_formatted_name;
    AddBookResult adding_request = books_manager.add_book(book_added_formatted_name);
    switch (adding_request)
    {
    case AddBookResult::NAME_IS_EXISTED_BEFORE:
        std::cout << "\tThis name is already existed!\n";
        break;
    case AddBookResult::ID_IS_EXISTED_BEFORE:
        std::cout << "\tThis id is already existed!\n";
        break;
    case AddBookResult::INVALID_QUANTITY:
        std::cout << "\tQuantity must be greater than zero\n";
        break;
    case AddBookResult::SUCCESS:
        std::cout << "\tBook " << book_added_formatted_name << " has been added to the system!\n";
    }
}
void LibrarySystem::add_user(){
    std::string user_added_formatted_name;
    AddUserResult adding_request = users_manager.add_user(user_added_formatted_name);
    switch (adding_request)
    {
    case AddUserResult::NAME_IS_EXISTED_BEFORE:
        std::cout << "\tThis name is already existed!\n";
        break;
    case AddUserResult::ID_IS_EXISTED_BEFORE:
        std::cout << "\tThis id is already existed!\n";
        break;
    case AddUserResult::SUCCESS:
        std::cout << "\tUser " << user_added_formatted_name << " has been added to the system!\n";
    }
}
void LibrarySystem::run(){
    std::cout << "\n****************************Welcome!****************************\n";
    std::vector<std::string> menu{"add a book", "search books by prefix", "print who borrowed a book", "print books borrowed by a user",
    "print library books by ID", "print library books by name", "add a user", "user borrow a book", 
"user return a book", "print users by name", "print users by id", "Exit"};
    while(true){
        show_menu(menu, "\nMain menu");
        int choice = read_validated_input<int>("\nchoose from [1 - 12]: ");
        switch (choice)
        {
        case 1:
            add_book();
            break;
        case 2:
            books_manager.search_books_by_prefix();
            break;
        case 3:
            print_who_borrowed_book_by_name();
            break;
        case 4:
            print_user_borrowed_books();
            break;
        case 5:
            books_manager.print_library_by_id();
            break;
        case 6:
            books_manager.print_library_by_name();
            break;
        case 7:
            add_user();
            break;
        case 8:
            borrow_book();
            break;
        case 9:
            return_book();
            break;
        case 10:
            users_manager.print_users_by_name();
            break;
        case 11:
            users_manager.print_users_by_id();
            break;
        case 12:
            std::cout << "\n******************************Bye!******************************\n";
            return;
            break;        
        }
    }
}

