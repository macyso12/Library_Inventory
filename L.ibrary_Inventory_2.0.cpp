// Macy So
// Library_Inventory

#include <iostream>
#include <vector>
#include <string>
//using namespace std;

//class Book ---------------------------------------------------------------------------- // Book.h file
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

//class Inventory ---------------------------------------------------------------------------- // Inventory.cpp file
class Inventory{
public:
    //std::vector<Book>Books;
    int MaxBookId;
    
    Inventory();
    
    int GetNextBookId();
    int NumberOfBooks();
    Book* GetBookByIndex(int index);
    //signitures !!!
    void AddBook (Book book);
    void RemoveBook (std::string title);
    int FindBookByTitle(std::string title);
    void CheckOutBook(Book* book);
    void CheckInBook(Book* book);
    
private:
    std::vector<Book>Books;
    
};

Inventory::Inventory(){
    Inventory::MaxBookId = 0;
}

int Inventory::GetNextBookId(){
    Inventory::MaxBookId++;
    return Inventory::MaxBookId;
}

int Inventory::NumberOfBooks(){
    return Inventory::Books.size();
}

Book* Inventory::GetBookByIndex(int index){
    return &Inventory::Books[index];
}
//void AddBook ----------------------------------------------------------------------------
void Inventory::AddBook(Book book){
    
    Inventory::Books.push_back(book);
    
}

//void RemoveBook ----------------------------------------------------------------------------
void Inventory::RemoveBook(std::string title){
    std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book(0, title,""));

    //.end() refers to pass the end
    if ( it != Inventory::Books.end()){
        Inventory::Books.erase(it);
    }
    
    
}
//bool FindBookByTitle ----------------------------------------------------------------------------
int Inventory::FindBookByTitle(std::string title){
    std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book(0, title,""));
    // we go through all the book, go through the dummy book we created
    // is the 1st book in the vector equal to this book, need to overload the vector to find = operator
    
    //.end() refers to pass the end
    if ( it == Inventory::Books.end()){
        return -1;
    }
    else {
        int index = it - Inventory::Books.begin();
        return index;
    }
}

void Inventory::CheckOutBook(Book* book){
    book->CHeckedOut = true;
}

void Inventory::CheckInBook(Book* book){
    book->CHeckedOut = false;
}

using namespace std;

Inventory _inventory; //Global variable

void AddNewBook(){
    cout << "Enter Title: ";
    string title;
    getline(cin, title);
    
    cout << "Enter Author: ";
    string author;
    getline(cin, author);
    
    int id = _inventory.GetNextBookId();
    
    Book newBook(id, title, author);
    
    _inventory.AddBook(newBook);
}

void ListAllBooks(){
    cout << "ID\tTitle\tAuthor" << endl ; // \t tab is for indentations
    for (int i = 0; i < _inventory.NumberOfBooks(); i++){ // Loop through our vector
        // Taking each book.id / .title/ .author from each book FROM our INVENTORY
        // _inventory is the library / obj
        cout << _inventory.GetBookByIndex(i)->Id << "\t" << _inventory.GetBookByIndex(i)->Title << "\t" << _inventory.GetBookByIndex(i)->Author << endl ;
    }
    cout << endl ;
}

void CheckInOrOutBook(bool checkIn){
    
    string InOrOut;
    if (checkIn){
        InOrOut = "in";
    }
    else {
        InOrOut = "out";
    }
    
    cout << "Enter a book title to check" << InOrOut << " : ";
    string title;
    getline(cin, title);
    
    int foundBookIndex = _inventory.FindBookByTitle(title);
    
    if (foundBookIndex >= 0){
        Book* foundbook = _inventory.GetBookByIndex(foundBookIndex); //& memory location * pointer
        
        // if checkedOut == false, then we're checked in
        // if checkedout == true, then we're cheched out
        if (!foundbook->CHeckedOut == checkIn){
            cout << "Book already checked " << InOrOut << " . " << endl;
            return;
        }
        if (checkIn){
            _inventory.CheckInBook(foundbook);
        }
        else{
            _inventory.CheckOutBook(foundbook);
        }
        _inventory.CheckOutBook(foundbook);
        cout << "Book checked " << InOrOut << " !" << endl ;
    }
    else{
        cout <<"Book not found" << endl ;
    }
}

void RemoveBook(){
    cout << "Enter Title: ";
    string title;
    getline(cin, title);
    
    _inventory.RemoveBook(title);
}

void DisplayCHeckedOutBooks(){
    for (int i = 0; i < _inventory.NumberOfBooks(); i++){
        if(_inventory.GetBookByIndex(i)->CHeckedOut){
            cout << _inventory.GetBookByIndex(i)->Id << "\t" <<_inventory.GetBookByIndex(i)->Title << "\t" << _inventory.GetBookByIndex(i)->Author << endl ;
        }
    }
    cout << endl ;
}

int main() {
    
    while (true){
        cout << "Choose an option: " << endl;
        cout << "1. Add Book " << endl;
        cout << "2. List All Books " << endl;
        cout << "3. Check Out Book " << endl;
        cout << "4. Check In Book " << endl;
        cout << "5. Remove Book From Library " << endl;
        cout << "6. List all checked out books" << endl ;
        cout << "0. Exit " << endl;
        
        int input;
        cin >> input ;
        cin.ignore();
        
        switch(input){
            case 0:
                cout << "Thankyou, Goodbye!" << endl ;
                return 0;
            case 1:
                AddNewBook();
                break;
            case 2:
                ListAllBooks();
                break;
            case 3:
                CheckInOrOutBook(false);
                break;
            case 4:
                CheckInOrOutBook(true);
                break;
            case 5:
                RemoveBook();
                break;
            case 6:
                DisplayCHeckedOutBooks();
                break;
            default:
                cout << "Invalid selection. Try again" << endl ;
                break ;
        }
    }
    
    return 0;
}
