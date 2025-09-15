#include "BooksManager.hpp"

std::pair<const Book*, std::string> BooksManager::enter_a_book()const{
    std::string book_name;
    std::cout << "Enter book name: ";
    getline(std::cin, book_name);
    return {static_cast<const Book*>(names_dictionary.word_exist(book_name)), book_name};
}
bool BooksManager::add_book(){
    auto [is_existed, book_name] = enter_a_book();
    if(is_existed){
        std::cout << "This name is already existed!\n";
        return false;
    }
    int id = read_validated_input<int>("Enter book id: ");
    if(ids_dictionary.find(id) != ids_dictionary.end()){
        std::cout << "This id is already existed!\n";
        return false;
    }
    int quantity = read_validated_input<int>("Enter quantity: ");
    if(quantity <= 0){
        std::cout << "Quantity must be greater than zero\n";
        return false;
    }
    Book *book = new Book(id, book_name, quantity);
    ids_dictionary[book->id] = book;
    names_dictionary.insert(book, book->get_name());
    return true;
}
void BooksManager::search_books_by_prefix(){
    std::cout << "Enter book prefix: ";
    std::string prefix;
    getline(std::cin, prefix);
    std::vector<Book*> res;
    names_dictionary.auto_complete(prefix, res);
    if(res.empty()){
        std::cout << "There is no book with such prefix.\n";
        return;
    }
    Book::print_header(1);
    for(auto &book : res){
        book->print(1);
    }
}
void BooksManager::print_who_borrowed_book_by_name() const{
    auto [book_ptr, book_name] = enter_a_book();
    if(!book_ptr){
        std::cout << "\tThere is no book with such name.\n";
    }
    else{
        book_ptr->print_detailed(1);
    }
}
void BooksManager::print_library_by_id() const{
    if(ids_dictionary.empty())
        return;
    std::cout << "Library sorted by ids: \n";
    Book::print_header(1);
    for(auto &[id, book] : ids_dictionary){
        book->print(1);
    }
}
void BooksManager::print_library_by_name() const{
    if(ids_dictionary.empty())
        return;
    std::cout << "Library sorted by ids: \n";
    Book::print_header(1);
    names_dictionary.traverse([](Book *book){
        book->print(1);
    });
}
bool BooksManager::user_borrow_book(User *usr, Book *book){
    return book->borrow(usr);
}
bool BooksManager::user_return_book(User *usr, Book *book){
    return book->return_(usr);
}
BooksManager::~BooksManager(){
    for(auto&[id, book] : ids_dictionary){
        delete book;
    }
}
