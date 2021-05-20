#include "Students.h"

using namespace std;

void Student::addStudent() {
    string name, branch;
    cout << endl << endl;
    cout << "---- NEW STUDENT ENTRY ----" << endl;

    cout << "Enter student ID: ";
    cin >> studId;

    cout << "Enter The Name of student: ";
    cin.ignore();
    getline(cin, name);
    studName = name;

    cout << "Enter The branch: ";
    getline(cin, branch);
    studBranch = branch;

    cout << "Enter Mobile Number: ";
    cin >> studContact;
    /*while (to_string(studContact).length() != 10) {
        cout << "Please enter valid number!!" << endl;
        cout << "Enter again: ";
        cin >> studContact;
    }*/

    cout << "Student Added Successfully!" << endl;
    cout << endl << endl;
}

void Student::setBranch(string branch) {
    studBranch = branch;
}

void Student::setContact(int num) {
    while (to_string(num).length() != 10) {
        cout << "Enter valid number" << endl;
        cin >> num;
    }
    studContact = num;
}

void Student::getDetails() {
    cout << endl;
    cout << "Student Id: " << studId << endl;
    cout << "Student Name: " << studName << endl;
    cout << "Student Branch: " << studBranch << endl;
    cout << "Student Contact: " << studContact << endl;
}

int Student::getId() {
    return studId;
}

void addStudent() {
    Student stud;
    stud.addStudent();
    insertIntoStudents(&stud);

    char chr;
    cout << "Do you want to add more? (Y/N)" << endl;
    cin >> chr;
    if (chr == 'Y' || chr == 'y') {
        addStudent();
    }
}

void modifyBranch(int id)
{
    string sBranch;
    cout << "Enter new branch: ";
    cin >> sBranch;
    updateStud(id, 1, sBranch);
}

void modifyContact(int id)
{
    int num;
    cout << "Enter new number: ";
    cin >> num;
    updateStud(id, 2, to_string(num));
}

void modifyStudent(int id)
{
    int inp;
    cout << endl;
    cout << "What do you want to modify: " << endl;
    cout << "1. Student Branch" << endl;
    cout << "2. Contact Number" << endl;
    cout << "3. Clear all Books Details" << endl;

    cout << endl << "Enter your choice: ";
    cin >> inp;
    switch (inp) {
    case 1:
        modifyBranch(id);
        break;
    case 2:
        modifyContact(id);
        break;
    case 3:
        updateStud(id, 3, string());
    }

    cout << "Do you want to modify more? (Y/N)" << endl;
    char chr;
    cin >> chr;
    if (chr == 'Y' || chr == 'y') {
        modifyStudent(id);
    }
}

void insertIntoStudents(Student* student)
{
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("Library.db", &DB);

    if (exit) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DB));
        return;
    }

    string sql = "INSERT INTO Students VALUES(" + to_string(student->studId) +
        ",'" + student->studName + "','" + student->studBranch +
        "'," + to_string(student->studContact) + ",0);";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        cerr << "Error Insert : " << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else
        cout << "Record added Successfully!" << endl;

    sqlite3_close(DB);
}

static int callbackStud(void* unused, int count, char** data, char** colNames)
{
    for (int i = 0; i < count; i++) {
        cout << colNames[i] << " = " << data[i] << " ";
    }
    cout << endl;

    return 0;
}

void displayStudents(int id)
{
    if (id < 0) {
        cout << "Invalid Student id! Try again." << endl;
    }
    else {
        sqlite3* DB;
        char* messaggeError;
        int exit = sqlite3_open("Library.db", &DB);

        if (exit) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DB));
            return;
        }

        string sql;

        if (id)
            sql = "SELECT * FROM Students WHERE Id=" + to_string(id) + ";";
        else
            sql = "SELECT * FROM Students;";
        exit = sqlite3_exec(DB, sql.c_str(), callbackStud, 0, &messaggeError);
        if (exit != SQLITE_OK) {
            cerr << "Error Display : " << messaggeError << endl;
            sqlite3_free(messaggeError);
        }

        sqlite3_close(DB);
    }
}

void updateStud(int id, int inp, string temp)
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
        sql = "UPDATE Students SET Branch='" + temp + "' WHERE Id=" + to_string(id) + ";";
    }
    else if (inp == 2) {
        sql = "UPDATE Students SET ContactNo.='" + temp + "' WHERE Id=" + to_string(id) + ";";
    }
    else {
        sql = "UPDATE Students SET BooksIssued=0 WHERE Id=" + to_string(id) + ";";
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

void deleteStud(int id)
{
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("Library.db", &DB);

    if (exit) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DB));
        return;
    }

    string sql = "DELETE FROM Students WHERE Id=" + to_string(id) + ";";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        cerr << "Error Deletion : " << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else
        cout << "Student record with id " << id << " deleted successfully!" << endl;
    cout << endl;

    sqlite3_close(DB);
}