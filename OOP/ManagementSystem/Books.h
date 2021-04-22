#include<bits/stdc++.h>

using namespace std;

class Book{
    int bookId;
    string bookName;
    string authName;
    int totalCount; 
    
 public:
    void addBook(){
        string bName, aName;

        cout << endl << endl;
        cout << "---- NEW BOOK ENTRY ----" << endl;
        cout << "Enter Book Id: ";
        cin >> bookId;

        cout << "Enter The Name of The Book: ";
        cin.ignore();
        getline(cin, bName);
        bookName = bName;
        
        cout << "Enter The Author's Name: ";
        getline(cin, aName);
        authName = aName;
      
      	cout << "Enter the number of copies: ";
        cin >> totalCount;
        
        cout << "Book Added Successfully!";
        cout << endl << endl;
    }

    void setName(string name){
        bookName = name;
    }

    void setAuth(string name){
        authName = name;
    }

    void setCount(int num){
        totalCount = num;
    }
  
    void getDetails(){
        cout << "Book Id: " << bookId << endl;
        cout << "Book Name: " << bookName << endl;
        cout << "Author Name: " << authName << endl;
        cout << endl;
    }

    int getId(){
        return bookId;
    }
  
  	int getAvailableBooks(){
    	return totalCount;
    }
};

void addBook(vector<Book> &books){
    Book tempBook;
    tempBook.addBook();
    books.push_back(tempBook);

    char chr;
    cout << "Do you want to add more? (Y/N)" << endl;
    cin >> chr;
    if (chr == 'Y' || chr == 'y'){
        addBook(books);
    }
}

vector<Book> createBook(){
    vector<class Book> books;
    addBook(books);

    return books;
}

void bookDisplayAll(vector<Book> books){
    for (int i = 0; i < books.size(); i++){
        books[i].getDetails();
    }   
    cout << endl;
}

void displayBook(int id, vector<Book> books){
    int index = getIndex(id, books);
    if (index < 0)  
        return;
    else
        books[index].getDetails();
}

void removeBook(int id, vector<Book> &books){
    int index = getIndex(id, books);
    if (index < 0)  
        return;
    else
        books.erase(books.begin() + index);

    cout << "Book with id " << id << " deleted successfully!" << endl;
    cout << endl;
}

void modifyBookName(Book &book){
    string bName;
    cout << "Enter modified name: ";
    cin >> bName;
    book.setName(bName);
}

void modifyAuthName(Book &book){
    string aName;
    cout << "Enter modified Author name: ";
    cin >> aName;
    book.setAuth(aName);
}

void modifyBooks(int id, vector<Book> &books){
    int index = getIndex(id, books);
    if (index < 0)
        return;

    int inp;
    cout << endl;
    cout << "What do you want to modify: " << endl;
    cout << "1. Book Name" << endl;
    cout << "2. Author Name" << endl;
    cout << "3. No of Copies left" << endl;

    cin >> inp;
    switch(inp){
        case 1: 
            modifyBookName(books[index]);
            break;
        case 2: 
            modifyAuthName(books[index]);
            break;
        case 3: 
            int num;
            cout << "Enter number of copies: ";
            cin >> num;
            books[index].setCount(num);
            break;
    }

    char chr;
    cout << "Do you want to modify more? (Y/N)" << endl;
    cin >> chr;
    if (chr == 'Y' || chr == 'y'){
        modifyBooks(id, books);
    }
}