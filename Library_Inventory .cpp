// Macy So
// Library_Inventory

#include <iostream>
#include <vector>
#include <string>
//using namespace std;

//class Book ----------------------------------------------------------------------------
class Book{ //class
public:
    int Id;
    std::string Title;
    std::string Author;
    bool CHeckedOut;
    
    
    Book();
    Book (int id, std::string title, std::string author); //Constructor
    
    bool operator == (const Book &book) const {
        if (Title.compare(book.Title) == 0){
            return true;
        }
        else {
            return false;
        }
    }
    
};

// Dummy Book
Book::Book(){}

Book::Book (int id, std::string title, std::string author){
    Book::Id = id;
    Book::Title = title;
    Book::Author = author;
    Book::CHeckedOut = false;
}

//class Inventory ----------------------------------------------------------------------------
class Inventory{
public:
    std::vector<Book>Books;
    
    void AddBook (Book book);
    void RemoveBook (Book book);
    bool FindBookByTitle(std::string title, Book &book);
    void CheckOutBook(Book &book);
    void CheckInBook(Book &book);
    
private:
    
};
//void AddBook ----------------------------------------------------------------------------
void Inventory::AddBook(Book book){
    
    Inventory::Books.push_back(book);
    
}
//bool FindBookByTitle ----------------------------------------------------------------------------
bool Inventory::FindBookByTitle(std::string title, Book &book){
    std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book(0, title,""));
    if ( it != Inventory::Books.end()){
        book = *it;
        return true;
    }
    else {
        return false;
    }
}

void Inventory::CheckOutBook(Book &book){
    book.CHeckedOut = true;
}

void Inventory::CheckInBook(Book &book){
    book.CHeckedOut = false;
}

using namespace std;

Inventory _inventory; //Global variable

int main() {
    
    while (true){
        cout << "Choose an option: " << endl;
        cout << "1. Add Book " << endl;
        cout << "2. List All Books " << endl;
        cout << "3. Check Out Book " << endl;
        cout << "4. Check In Book " << endl;
        cout << "0. Exit " << endl;
        
        int input;
        cin >> input ;
        cin.ignore();
        
        switch(input){
            case 0:
                cout << "Thankyou, Goodbye!" << endl ;
                return 0;
            case 1: {
                cout << "Enter Title: ";
                string title;
                getline(cin, title);
                
                cout << "Enter Author: ";
                string author;
                getline(cin, author);
                
                int id = _inventory.Books.size() + 1;
                
                Book newBook(id, title, author);
                
                /*if (newBook == myBook){
                    // some code ...
                }*/
                
                _inventory.AddBook(newBook);
                break;
            }
            case 2: {
                cout << "ID\tTitle\tAuthor" << endl ; // \t tab is for indentations
                for (int i = 0; i < _inventory.Books.size(); i++){ // Loop through our vector
                    // Taking each book.id / .title/ .author from each book FROM our INVENTORY
                    // _inventory is the library / obj
                    cout << _inventory.Books[i].Id << "\t" << _inventory.Books[i].Title << "\t" << _inventory.Books[i].Author << endl ;
                }
                cout << endl ;
                break;
            }
            case 3:{
                cout << "Enter a book title to check out: ";
                string title;
                getline(cin, title);
                
                Book foundBook;
                if (_inventory.FindBookByTitle(title, foundBook)){
                    
                    if (foundBook.CHeckedOut){
                        cout << "Book already checked out" << endl;
                        break;
                    }
                    _inventory.CheckOutBook(foundBook);
                    cout << "Book checked out!" << endl ;
                }
                else{
                    cout <<"Book not found" << endl ;
                }
                break;
            }
            case 4:{
                cout << "Enter a book title to check in: ";
                string title;
                getline(cin, title);

                Book foundBook;
                if (_inventory.FindBookByTitle(title, foundBook)){

                    if (!foundBook.CHeckedOut){
                        cout << "Book already checked in" << endl ;
                        break;
                    }
                    _inventory.CheckInBook(foundBook);
                    cout << "Book checked in!" << endl ;
                }
                else{
                    cout <<"Book not found" << endl ;
                }
                break;
            }
            default:
                cout << "Invalid selection. Try again" << endl ;
                break ;
        }
    }
    
    return 0;
}
