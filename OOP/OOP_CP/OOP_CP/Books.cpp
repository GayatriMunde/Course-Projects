#include "Books.h"

using namespace std;

void Book::addBook()
{
    string bName, aName;

    cout << endl << endl;
    cout << "---- NEW BOOK ENTRY ----" << endl;
    while (true) {
        cout << "Enter Book Id: ";
        cin >> bookId;
        if (bookId <= 0)
            cout << "Invalid Book Id! Try again." << endl;
        else
            break;
    }

    cout << "Enter The Name of The Book: ";
    cin.ignore();
    getline(cin, bName);
    bookName = bName;

    cout << "Enter The Author's Name: ";
    getline(cin, aName);
    authName = aName;

    while (true) {
        cout << "Enter the number of copies: ";
        cin >> totalCount;
        if (totalCount <= 0)
            cout << "Inavlid count of books! Try again." << endl;
        else
            break;
    }
}

void Book::setName(string name) {
    bookName = name;
}

void Book::setAuth(string name) {
    authName = name;
}

void Book::setCount(int num) {
    totalCount = num;
}

void Book::getDetails() {
    cout << "Book Id: " << bookId << endl;
    cout << "Book Name: " << bookName << endl;
    cout << "Author Name: " << authName << endl;
    cout << endl;
}

int Book::getId() {
    return bookId;
}

int Book::getAvailableBooks() {
    return totalCount;
}

void addBook()
{
    Book tempBook;
    tempBook.addBook();
    insertIntoBooks(&tempBook);

    char chr;
    cout << "Do you want to add more? (Y/N)" << endl;
    cin >> chr;
    if (chr == 'Y' || chr == 'y') {
        addBook();
    }
}

void modifyBookName(int id)
{
    string bName;
    cout << "Enter modified name: ";
    cin >> bName;
    updateBook(id, 1, bName);
}

void modifyAuthName(int id)
{
    string aName;
    cout << "Enter modified Author name: ";
    cin >> aName;
    updateBook(id, 2, aName);
}

void modifyBooks(int id)
{
    int inp;
    cout << endl;
    cout << "What do you want to modify: " << endl;
    cout << "1. Book Name" << endl;
    cout << "2. Author Name" << endl;
    cout << "3. No of Copies left" << endl;

    cin >> inp;
    switch (inp) {
    case 1:
        modifyBookName(id);
        break;
    case 2:
        modifyAuthName(id);
        break;
    case 3:
        updateBook(id, 3, string());
        break;
    }

    char chr;
    cout << "Do you want to modify more? (Y/N)" << endl;
    cin >> chr;
    if (chr == 'Y' || chr == 'y') {
        modifyBooks(id);
    }
}

void insertIntoBooks(Book* book)
{
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("Library.db", &DB);

    if (exit) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DB));
        return;
    }

    string sql = "INSERT INTO Books VALUES(" + to_string(book->bookId) +
        ",'" + book->bookName + "','" + book->authName +
        "'," + to_string(book->totalCount) + "," + to_string(book->totalCount) + ");";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        cerr << "Error Insert" << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else
        cout << "Book Added Successfully!";
    cout << endl << endl;

    sqlite3_close(DB);
}

static int callbackBooks(void* unused, int count, char** data, char** colNames)
{
    for (int i = 0; i < count; i++) {
        cout << colNames[i] << " = " << data[i];
    }
    cout << endl;

    return 0;
}

void displayBooks(int id)
{
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("Library.db", &DB);

    if (exit) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DB));
        return;
    }

    string sql;

    if (id)
        sql = "SELECT * FROM Books WHERE Id=" + to_string(id) + ";";
    else
        sql = "SELECT * FROM Books;";
    exit = sqlite3_exec(DB, sql.c_str(), callbackBooks, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        cerr << "Error Display : " << messaggeError << endl;
        sqlite3_free(messaggeError);
    }

    sqlite3_close(DB);
}

void updateBook(int id, int inp, string temp)
{
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("Library.db", &DB);

    if (exit) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DB));
        return;
    }

    string sql;
    if (inp == 1) {
        sql = "UPDATE Books SET BookName='" + temp + "' WHERE Id=" + to_string(id) + ";";
    }
    else if (inp == 2) {
        sql = "UPDATE Books SET AuthorName='" + temp + "' WHERE Id=" + to_string(id) + ";";
    }
    else {
        int ac, tc;
        cout << "Enter available count of book = ";
        cin >> ac;
        cout << "Enter total count of book = ";
        cin >> tc;
        sql = "UPDATE Books SET AvailableCount=" + to_string(ac) + ", TotalCount=" + to_string(tc) + " WHERE Id=" + to_string(id) + ";";
    }
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        cerr << "Error Updation : " << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else
        cout << "Record updated successfully" << endl;

    sqlite3_close(DB);
}

void deleteBook(int id)
{
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("Library.db", &DB);

    if (exit) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DB));
        return;
    }

    string sql = "DELETE FROM Books WHERE Id=" + to_string(id) + ";";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        cerr << "Error Deletion : " << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else
        cout << "Book with id " << id << " deleted successfully!" << endl;
    cout << endl;

    sqlite3_close(DB);
}