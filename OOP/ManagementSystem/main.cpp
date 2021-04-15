#include<bits/stdc++.h>
#include "Structs.h"
#include "Books.h"
#include "Students.h"

using namespace std;

void mainMenu(vector<Student> &students, vector<Book> &books);

void adminMenu(vector<Student> &students, vector<Book> &books){
    int inpAdmin, id;
    cout << endl;
    cout<<"-----Admin Menu------"<<endl;
    cout<<"1.Get all students data"<<endl;
    cout<<"2.Get particular student info"<<endl;
    cout<<"3.All books data"<<endl;
    cout<<"4.Particular Book data"<<endl;
    cout<<"5.Remove student "<<endl;
    cout<<"6.Remove Book"<<endl;
    cout<<"7.Edit Book"<<endl;
    cout<<"8.Edit Student Details"<<endl;
    cout<<"9.Add New Book Details"<<endl;
    cout<<"10.Add New Student Details"<<endl;
    cout<<"11.Exit"<<endl;

    cout << endl << "Enter your choice: ";
    cin >> inpAdmin;

    switch(inpAdmin){
        case 1:
            studDisplayAll(students);
            break;
        case 2:
            cout << "Enter the id: ";
            cin >> id;
            displayStudents(id, students);
            break;
        case 3:
            bookDisplayAll(books);
            break;
        case 4:
            cout << "Enter the id: ";
            cin >> id;
            displayBook(id, books);
           break;
        case 5:
            cout << "Enter the id: ";
            cin >> id;
            removeStudent(id, students);
            break;
        case 6:
            cout << "Enter the id: ";
            cin >> id;
            removeBook(id, books);
            break;
        case 7:
            modifyBooks(id, books);
            break;
        case 8:
            modifyStudent(id, students);
            break;
        case 9:
            addBook(books);
            break;
        case 10:
            addStudent(students);
            break;
        case 11:
            mainMenu(students, books);
            break;
        default:
            return;
    }

    while (inpAdmin < 11){
        adminMenu(students, books);
    }
}

void bookIssue(vector<Student> &students, vector<Book> &books){
    int studId, bookId, index; 
    cout << "Enter student Id: ";
    cin >> studId;

    index = getIndex(studId, students);
    if (index == -1){
        cout << endl << "Enter Valid Student Id!" << endl;
        return;
    }

    cout << "Enter book Id: ";
    cin >> bookId;
    if (getIndex(bookId, books) == -1){
        cout << endl << "Enter Valid book Id!" << endl;
        return;
    }

    vector<int> tempBooks = students[index].getBooks();
    tempBooks.push_back(bookId);
    students[index].setBooks(tempBooks);

    char chr;
    cout << "Do you want to add more? (Y/N)" << endl;
    cin >> chr;
    if (chr == 'Y' || chr == 'y'){
        bookIssue(students, books);
    }
}

void bookRemove(vector<Student> &students, vector<Book> &books){
    int studId, bookId, index; 
    cout << "Enter student Id: ";
    cin >> studId;

    index = getIndex(studId, students);
    if (index == -1){
        cout << endl << "Enter Valid Student Id!" << endl;
        return;
    }

    cout << "Enter book Id: ";
    cin >> bookId;
    if (getIndex(bookId, books) == -1){
        cout << endl << "Enter Valid book Id!" << endl;
        return;
    }

    vector<int> tempBooks = students[index].getBooks();
    for(int i = 0; i < tempBooks.size(); i++){
        if(bookId == tempBooks[i]){   
            tempBooks.erase(tempBooks.begin() + i);  
        }
    }

    students[index].setBooks(tempBooks);

    char chr;
    cout << "Do you want to add more? (Y/N)" << endl;
    cin >> chr;
    if (chr == 'Y' || chr == 'y'){
        bookIssue(students, books);
    }
}


/*
void addSbook(Student &students, int book_id){
    vector<int> books = students.getBooks();
    books.push_back(book_id);
}

void removeSbook(Student &students, int book_id){   
    vector <int> books = students.getBooks();

    for(int i=0;i<books.size();i++){
        if(book_id == books[i]){   
            books.erase(books.begin() + i);  
        }
    }
}

void bookIssue(vector<Student> &students){  
    int studId, bookId; 
    cout << "Enter student Id: ";
    cin >> studId;

    cout << "Enter book Id: ";
    cin >> bookId;

    int index = getIndex(studId, students);
    if (index < 0)  
        return;
    else
        addSbook(students[index], bookId);
}

void bookRemove(vector<Student>&students){   
    int studId, bookId; 
    cout << "Enter student Id: ";
    cin >> studId;

    cout << "Enter book Id: ";
    cin >> bookId;

    int index = getIndex(studId, students);
    if (index < 0)  
        return;
    else
        removeSbook(students[index], bookId);
}*/

void mainMenu(vector<Student> &students, vector<Book> &books){
    int inpMenu;
    cout << endl;
    cout << "----------MENU-----------" << endl;
    cout << " 1.Book Issue" << endl;
    cout << " 2.Book recieved" << endl;
    cout << " 3.Admin Login" << endl;
    cout << " 4.Exit" << endl;
   
    cout << endl << "Enter your choice: ";
    cin >> inpMenu;
    switch(inpMenu){
        case 1:
            bookIssue(students, books);
            break;
        case 2:
            bookRemove(students, books); 
            break;
        case 3:
            adminMenu(students, books);
            break;
        case 4:
            return;
            break;
        default:
            cout << "Enter valid number" << endl;
    }

    while(inpMenu < 4){
        mainMenu(students, books);
    }
}

int main(){
    cout << endl << "Create the database!" << endl;
    vector<Book> books = createBook();
    vector<Student> students = createStud();
    mainMenu(students, books);
    return 0;
}