#include <iostream>
#include "Books.h"
#include "Students.h"

using namespace std;

void mainMenu();

void adminMenu() {
    int inpAdmin, id;
    cout << endl;
    cout << "-----Admin Menu------" << endl;
    cout << "1.Get all students data" << endl;
    cout << "2.Get particular student info" << endl;
    cout << "3.All books data" << endl;
    cout << "4.Particular Book data" << endl;
    cout << "5.Remove student " << endl;
    cout << "6.Remove Book" << endl;
    cout << "7.Edit Book" << endl;
    cout << "8.Edit Student Details" << endl;
    cout << "9.Add New Book Details" << endl;
    cout << "10.Add New Student Details" << endl;
    cout << "11.Exit" << endl;

    cout << endl << "Enter your choice: ";
    cin >> inpAdmin;

    switch (inpAdmin) {
    case 1:
        displayStudents();
        break;
    case 2:
        cout << "Enter the id: ";
        cin >> id;
        if (id > 0)
            displayStudents(id);
        else
            cout << "Invalid id!" << endl;
        break;
    case 3:
        displayBooks();
        break;
    case 4:
        cout << "Enter the id: ";
        cin >> id;
        if (id > 0)
            displayBooks(id);
        else
            cout << "Invalid id!" << endl;
        break;
    case 5:
        cout << "Enter the id: ";
        cin >> id;
        if (id > 0)
            deleteStud(id);
        else
            cout << "Invalid id!" << endl;
        break;
    case 6:
        cout << "Enter the id: ";
        cin >> id;
        if (id > 0)
            deleteBook(id);
        else
            cout << "Invalid id!" << endl;
        break;
    case 7:
        cout << "Enter the id: ";
        cin >> id;
        if (id > 0)
            modifyBooks(id);
        else
            cout << "Invalid id!" << endl;
        break;
    case 8:
        cout << "Enter the id: ";
        cin >> id;
        if (id > 0)
            modifyStudent(id);
        else
            cout << "Invalid id!" << endl;
        break;
    case 9:
        addBook();
        break;
    case 10:
        addStudent();
        break;
    case 11:
        return;
    default:
        return;
    }

    if (inpAdmin < 11) {
        adminMenu();
    }
}

void bookIssue() {
    int studId, bookId;
    while (true) {
        cout << "Enter student Id: ";
        cin >> studId;
        if (studId > 0)
            break;
        else
            cout << "Invalid id! Try again." << endl;
    }

    while (true) {
        cout << "Enter book Id: ";
        cin >> bookId;
        if (bookId > 0)
            break;
        else
            cout << "Invalid id! Try again." << endl;
    }
    
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("Library.db", &DB);

    if (exit) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DB));
        return;
    }

    string sql = "INSERT INTO Relational VALUES(" + to_string(studId) + "," + to_string(bookId) + ");\n"
                "UPDATE Books SET AvailableCount = (AvailableCount - 1) WHERE Id=" + to_string(bookId) + ";\n"
                "UPDATE Students SET BooksIssued = (BooksIssued + 1) WHERE Id=" + to_string(studId) + ";";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        cerr << "Error Issue : " << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else
        cout << "Book issued Successfully!" << endl;

    sqlite3_close(DB);

    char chr;
    cout << "Do you want to issue more? (Y/N)" << endl;
    cin >> chr;
    if (chr == 'Y' || chr == 'y') {
        bookIssue();
    }
}

void bookRemove() {
    int studId, bookId;
    while (true) {
        cout << "Enter student Id: ";
        cin >> studId;
        if (studId > 0)
            break;
        else
            cout << "Invalid id! Try again." << endl;
    }

    while (true) {
        cout << "Enter book Id: ";
        cin >> bookId;
        if (bookId > 0)
            break;
        else
            cout << "Invalid id! Try again." << endl;
    }
    
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("Library.db", &DB);

    if (exit) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DB));
        return;
    }

    string sql = "DELETE FROM Relational WHERE studID=" + to_string(studId) + " AND bookID=" + to_string(bookId) + "; "
                "UPDATE Books SET AvailableCount = (AvailableCount + 1) WHERE Id=" + to_string(bookId) + "; "
                "UPDATE Students SET BooksIssued = (BooksIssued - 1) WHERE Id=" + to_string(studId) + ";";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        cerr << "Error Return : " << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else
        cout << "Book returned Successfully!" << endl;

    sqlite3_close(DB);

    char chr;
    cout << "Do you want to return more? (Y/N)" << endl;
    cin >> chr;
    if (chr == 'Y' || chr == 'y') {
        bookRemove();
    }
}


void mainMenu() {
    int inpMenu;
    cout << endl;
    cout << "----------MENU-----------" << endl;
    cout << " 1.Book Issue" << endl;
    cout << " 2.Book recieved" << endl;
    cout << " 3.Admin Login" << endl;
    cout << " 4.Exit" << endl;

    cout << endl << "Enter your choice: ";
    cin >> inpMenu;
    switch (inpMenu) {
    case 1:
        bookIssue();
        break;
    case 2:
        bookRemove();
        break;
    case 3:
        adminMenu();
        break;
    case 4:
        return;
    default:
        cout << "Enter valid number" << endl;
    }

    if (inpMenu < 4) {
        mainMenu();
    }
}

int main() {
    mainMenu();
    return 0;
}