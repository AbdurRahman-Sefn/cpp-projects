#include "BooksManager.hpp"
#include <algorithm>
#include <fstream>

std::pair<Book*, std::string> BooksManager::enter_a_book(){
    std::string book_name;
    std::cout << "Enter book name: ";
    read_and_trim(std::cin, book_name);
    return {names_dictionary.word_exist(book_name), book_name};
}
void BooksManager::push_book(Book *book){
    ids_dictionary[book->id] = book;
    names_dictionary.insert(book, book->get_name());
}
void BooksManager::clear(){
    ids_dictionary.clear();
    names_dictionary.clear();
}

AddBookResult BooksManager::add_book(std::string &book_name_formatted){
    auto [is_existed, book_name] = enter_a_book();
    if(is_existed){
        return AddBookResult::NAME_IS_EXISTED_BEFORE;
    }
    int id = read_validated_input<int>("Enter book id: ");
    if(ids_dictionary.find(id) != ids_dictionary.end()){
        return AddBookResult::ID_IS_EXISTED_BEFORE;
    }
    int quantity = read_validated_input<int>("Enter quantity: ");
    if(quantity <= 0){
        return AddBookResult::INVALID_QUANTITY;
    }
    Book *book = new Book(id, book_name, quantity);
    push_book(book);
    book_name_formatted = book->get_name_formatted();
    return AddBookResult::SUCCESS;
}
void BooksManager::search_books_by_prefix(){
    std::cout << "Enter book prefix: ";
    std::string prefix;
    read_and_trim(std::cin, prefix);
    std::vector<Book*> res;
    names_dictionary.auto_complete(prefix, res);
    if(res.empty()){
        std::cout << "\tThere is no book with such prefix.\n";
        return;
    }
    Book::print_header(1);
    for(auto &book : res){
        book->print(1);
    }
}

void BooksManager::print_library_by_id() const{
    if(ids_dictionary.empty())
        return;
    std::cout << "\tBooks sorted by id: \n";
    Book::print_header(2);
    for(auto &[id, book] : ids_dictionary){
        book->print(2);
    }
}
void BooksManager::print_library_by_name() const{
    if(ids_dictionary.empty())
        return;
    std::cout << "\tBooks sorted by name: \n";
    Book::print_header(2);
    names_dictionary.traverse([](Book *book){
        book->print(2);
    });
}

void BooksManager::increment_book(Book *book){
    book->borrowed--;
    if(book->borrowed < 0){
        throw std::invalid_argument("Incompatible borrowing or returning!");
    }
}
void BooksManager::decrement_book(Book *book){
    if(!book->is_available()){
        throw std::invalid_argument("Incompatible borrowing or returning!");
    }
    book->borrowed++;
}

void BooksManager::print_borrowed_books(const std::vector<BorrowOperation*> &operations) const{
    std::vector<std::string> books_names;
    for(auto &operation : operations){
        books_names.push_back(operation->book->get_name_formatted());
    }
    std::sort(books_names.begin(), books_names.end());
    for(int i = 0; i < books_names.size(); ++i){
        std::string cur_name = books_names[i];
        int freq = 1;
        while(i + 1 < books_names.size() && cur_name == books_names[i + 1]){
            ++i;
            ++freq;
        }
        if(freq > 1)
            --i;
            std::cout << "\t" << std::setw(2) << std::right << freq << " item(s) of Book " <<  cur_name << " borrowed by this user.\n" ;
    }
}

const Book* BooksManager::get_book_by_id(int id) const{
    auto it = ids_dictionary.find(id);
    if(it == ids_dictionary.cend()){
        return nullptr;
    }
    return it->second;
}

BooksManager::BooksManager(){
    load_database();
}

BooksManager::~BooksManager(){
    update_database();
    for(auto&[id, book] : ids_dictionary){
        delete book;
    }
}

void BooksManager::load_database(){
    std::ifstream data("Books.txt");
    if(data.fail()){
        data.close();
        throw std::invalid_argument("CAN't open database of books --> \"Books.txt\"");
    }
    clear();
    std::string book_str;
    while(read_and_trim(data, book_str)){
        Book *book = new Book(book_str);
        push_book(book);
    }
    data.close();
}

void BooksManager::update_database()const{
    std::ofstream data("Books.txt");
    if(data.fail()){
        data.close();
        throw std::invalid_argument("CAN't open database of books --> \"Books.txt\"");
    }
    for(auto&[id, book] : ids_dictionary){
        data << book->to_string() << "\n";
    }
    data.close();
}