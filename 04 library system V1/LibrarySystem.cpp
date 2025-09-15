#include "LibrarySystem.hpp"

LibrarySystem::VerificationResult LibrarySystem::verify(){
    auto [book_ptr, book_name] = books_manager.enter_a_book();
    if(!book_ptr){
        std::cout << "Book is not existed!\n";
        return VerificationResult();
    }
    auto [usr_ptr, usr_name] = users_manager.enter_user();
    if(!usr_ptr){
        std::cout << "User is not existed!\n";
        return VerificationResult();
    }
    return VerificationResult{true, const_cast<User*>(usr_ptr), const_cast<Book*>(book_ptr)};
}
void LibrarySystem::borrow_book(){
    VerificationResult verification = verify();
    if(!verification.success)
        return;
    if(books_manager.user_borrow_book(verification.user, verification.book)){
        users_manager.user_borrow_book(verification.user, verification.book);
        std::cout << "Book (" << verification.book->get_name() << ") is borrowed by User ("
                  << verification.user->get_name()<< ")\n";
    }
    else{
        std::cout << "Sorry, This book is not available now!\n";
    }
}
void LibrarySystem::return_book(){
    VerificationResult verification = verify();
    if(!verification.success)
        return;
    bool book_side = books_manager.user_return_book(verification.user, verification.book);
    bool user_side = users_manager.user_return_book(verification.user, verification.book);
    if(book_side && user_side){
        std::cout << "Book (" << verification.book->get_name() << ") is returned by User ("
                  << verification.user->get_name()<< ")\n";
    }
    else if(!book_side && !user_side){
        std::cout << "This user did not borrow this book before.\n";
    }
    else
        throw std::invalid_argument("Incompatible data");
}

void LibrarySystem::run(){
    std::cout << "\n******************Welcome!******************\n";
    load_data_base();
    std::vector<std::string> menu{"add a book", "search books by prefix", "print who borrowed a book", 
    "print library books by ID", "print library books by name", "add a user", "user borrow a book", 
"user return a book", "print users", "Exit"};
    while(true){
        show_menu(menu, "Main menu");
        int choice = read_validated_input<int>("choose from [1 - 10]: ");
        switch (choice)
        {
        case 1:
            books_manager.add_book();
            break;
        case 2:
            books_manager.search_books_by_prefix();
            break;
        case 3:
            books_manager.print_who_borrowed_book_by_name();
            break;
        case 4:
            books_manager.print_library_by_id();
            break;
        case 5:
            books_manager.print_library_by_name();
            break;
        case 6:
            users_manager.add_user();
            break;
        case 7:
            borrow_book();
            break;
        case 8:
            return_book();
            break;
        case 9:
            users_manager.print_users();
            break;
        case 10:
            update_data_base();
            std::cout << "\n********************Bye!********************\n";
            return;
            break;        
        }
    }
}

void LibrarySystem::load_data_base(){}
void LibrarySystem::update_data_base(){}