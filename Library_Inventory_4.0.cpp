// Macy So
// Library_Inventory

#include <iostream>
#include <vector>
#include <string>
//using namespace std;

//class Book ---------------------------------------------------------------------------- // Book.h file
class Book{ //class
private:
    int Id;
    std::string Title;
    std::string Author;
    bool CHeckedOut;
    
public:
    
    Book();
    Book (std::string title, std::string author); //Constructor
    
    void SetBookId(int id);
    void CheckInOrOut(bool checkOut);
    void Displaybook();
    bool IsCheckedOut();
    
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

Book::Book (std::string title, std::string author){
    Book::Title = title;
    Book::Author = author;
    Book::CHeckedOut = false;
}

void Book::CheckInOrOut(bool checkOut){
    CHeckedOut = checkOut;
}

void Book::Displaybook(){
    std::cout << Id << "\t" <<Title << "\t" << Author << std::endl ;
}

bool Book::IsCheckedOut(){
    return CHeckedOut;
}

void Book::SetBookId(int id){
    Id = id;
}

// Check in or out result header file --------------------------------------------- **CheckInOrOutResult.h
enum class CheckInOrOutResult{
    Success,
    BookNotFound,
    AlreadyCheckedoutOut,
    AlreadyCheckedin,
    Failure
};

//class Role ---------------------------------------------------------------------------  // Role.h
enum class Role{
    Member, Employee, Admin
};

//class User --------------------------------------------------------------------------- // User.cpp file // User.h
class User {
public:
    int id;
    std::string FirstName;
    std::string LastName;
    std::string userName;
    Role role;
    
    bool operator == (const User& user) const{
        if (userName.compare(user.userName)==0){
            return true;
        }
        else{
            return false;
        }
    }
};
std::vector <User> _users;
User _loggedInUser;

//class Inventory ---------------------------------------------------------------------------- // Inventory.cpp file // Inventory.h **
class Inventory{
public:
    Inventory();
    
    void DisplayAllBooks();
    void DisplayCheckedOutBooks();
    int NumberOfBooks();
    Book GetBookByIndex(int index);
    //signitures !!!
    void AddBook (Book book);
    void RemoveBook (std::string title);
    int FindBookByTitle(std::string title);
    CheckInOrOutResult CheckInOrOutBook(std::string title, bool checkOut);
    
private:
    std::vector<Book>Books;
    int MaxBookId;
    
};

Inventory::Inventory(){
    Inventory::MaxBookId = 0;
}

int Inventory::NumberOfBooks(){
    return Inventory::Books.size();
}

Book Inventory::GetBookByIndex(int index){
    return Inventory::Books[index];
}
//void AddBook ----------------------------------------------------------------------------
void Inventory::AddBook(Book book){
    Inventory::MaxBookId++;
    book.SetBookId(MaxBookId);
    Inventory::Books.push_back(book);
    
}

//void RemoveBook ----------------------------------------------------------------------------
void Inventory::RemoveBook(std::string title){
    
    //TODO: handle MaxBookId when removing
    
    std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book(title,""));

    //.end() refers to pass the end
    if ( it != Inventory::Books.end()){
        Inventory::Books.erase(it);
    }
    
    
}

void Inventory::DisplayCheckedOutBooks(){
    std::cout << "ID\tTitle\tAuthor" << std::endl ; // \t tab is for indentations
    for (int i = 0; i < NumberOfBooks(); i++){ // Loop through our vector
        if (GetBookByIndex(i).IsCheckedOut())
        Books[i].Displaybook();
    }
    std::cout << std::endl ;
}

void Inventory::DisplayAllBooks(){
    std::cout << "ID\tTitle\tAuthor" << std::endl ; // \t tab is for indentations
    for (int i = 0; i < NumberOfBooks(); i++){ // Loop through our vector
        Books[i].Displaybook();
    }
    std::cout << std::endl ;
}

void CreateAccount(){
    
    User newUser;
    
    /*std::cout<<"First name: "  ;
    std::string FirstName;
    getline(std::cin, FirstName);
    std::cout << std::endl;
    
    std::cout<<"Last name: "  ;
    std::string LastName;
    getline(std::cin, LastName);
     std::cout << std::endl;*/
    
    std::cout<<"Username: "  ;
    getline(std::cin, newUser.userName);
    std::cout << std::endl;
    
    std::cout<<"Choose a role: " << std::endl;
    std::cout<<"1. Admin" << std::endl;
    std::cout<<"2. Empoyee" << std::endl;
    std::cout<<"3. Member" << std::endl;
    
    int roleOption;
    std:: cin >> roleOption;
    std::cin.ignore();
    
    if (roleOption == 1){
        newUser.role = Role::Admin;
    }
    else if (roleOption == 2){
        newUser.role = Role::Employee;
    }
    else {
        newUser.role = Role::Member;
    }
    
    _users.push_back(newUser);
}

void Login(){
    
    std::cout << "Choose an option:" << std::endl;
    std::cout << "1. Log in" << std::endl;
    std::cout << "2. Create account" << std::endl;
    
    int option;
    std::cin >> option;
    std::cin.ignore();
    
    if (option == 2){
        CreateAccount();
    }
    
    std::cout << "Enter username: ";
    std::string userName;
    getline(std::cin, userName);
    
    User user;
    user.userName = userName;
    
    std::vector<User>::iterator it = find(_users.begin(), _users.end(), user);
    
    if (it != _users.end()){
        _loggedInUser = _users[it - _users.begin()];
    }
    
}

//bool FindBookByTitle ----------------------------------------------------------------------------
int Inventory::FindBookByTitle(std::string title){
    std::vector<Book>::iterator it = std::find(Inventory::Books.begin(), Inventory::Books.end(), Book(title,""));
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

CheckInOrOutResult Inventory::CheckInOrOutBook(std::string title, bool checkOut){
    int foundBookIndex = FindBookByTitle(title);
    
    if(foundBookIndex < 0){
        return CheckInOrOutResult::BookNotFound;
    }
    else if(checkOut == Books[foundBookIndex].IsCheckedOut()) { // false false
        
        if (checkOut){
            return CheckInOrOutResult::AlreadyCheckedoutOut;
        }
        else {
            return CheckInOrOutResult::AlreadyCheckedin;
        }
    }

    Books[foundBookIndex].CheckInOrOut(checkOut);
    return CheckInOrOutResult::Success;
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
    
    Book newBook(title, author);
    
    _inventory.AddBook(newBook);
}

void ListAllBooks(){
    _inventory.DisplayAllBooks();
}

void CheckInOrOutBook(bool checkOut){
    
    string InOrOut;
    if (checkOut){
        InOrOut = "out";
    }
    else {
        InOrOut = "in";
    }
    
    cout << "Enter a book title to check" << InOrOut << " : ";
    string title;
    getline(cin, title);
    
    CheckInOrOutResult result = _inventory.CheckInOrOutBook(title, checkOut); //NEAT!
    if(result == CheckInOrOutResult::BookNotFound){ // book not found
        cout << "Book not found" << endl;
    }
    else if (result == CheckInOrOutResult::Success){
        cout << "Book checked " << InOrOut << " !" << endl;
    }
    else if (result == CheckInOrOutResult::AlreadyCheckedin || result == CheckInOrOutResult::AlreadyCheckedoutOut){
        cout << "Book already " << InOrOut << "!" << endl ;
    }
    else {
        cout << "Book failed checking "<< InOrOut << " !" << endl;
    }
}

void RemoveBook(){
    cout << "Enter Title: ";
    string title;
    getline(cin, title);

    _inventory.RemoveBook(title);
}

void DisplayCHeckedOutBooks(){
    _inventory.DisplayCheckedOutBooks();
}

int main() {
    
    Login();
    
    while (true){
        cout << endl ;
        cout << "Choose an option: " << endl;
        
        if (_loggedInUser.role == Role::Employee|| _loggedInUser.role == Role::Admin){
            cout << "1. Add Book " << endl;
            cout << "5. Remove Book From Library " << endl;
            cout << "6. List all checked out books" << endl ;
        }
        else {
            cout << "2. List All Books " << endl;
            cout << "3. Check Out Book " << endl;
            cout << "4. Check In Book " << endl;
        }
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
                CheckInOrOutBook(true);
                break;
            case 4:
                CheckInOrOutBook(false);
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
