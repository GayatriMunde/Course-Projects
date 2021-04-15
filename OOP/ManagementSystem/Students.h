#include<bits/stdc++.h>

using namespace std;

class Student{
    int studId;
    string studName;
    string studBranch;
    long int studContact;
  	vector<int> books;
  
  public:
  	void addStudent(){
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
        cin.ignore();
        getline(cin, branch);
        studBranch = branch;
        
        cout << "Enter Mobile Number: ";
        cin >> studContact;
        while (to_string(studContact).length() != 10){
            cout << "Please enter valide number!!" << endl;
            cout << "Enter again: ";
            cin >> studContact;
        } 

        cout << "Student Added Successfully!" << endl;
        cout << endl << endl;
    }

    void setBranch(string branch){
        studBranch = branch;
    }

    void setContact(int num){
        while (to_string(num).length() != 10){
            cout << "Enter valide number" << endl;
            cin >> num;
        } 
        studContact = num;
    }
  
    void getDetails(){
        cout << endl;
        cout << "Student Id: " << studId << endl;
        cout << "Student Name: " << studName << endl;
        cout << "Student Branch: " << studBranch << endl;
        cout << "Student Contact: " << studContact << endl;
        cout << "No. of books Student issued: " << books.size() << endl;
        
        cout << "List of books: " << endl;
        for (int i = 0; i < books.size(); i++){
            cout << i + 1 << ") " << books[i] << endl; 
        }
        cout << endl;
    }
  
  	int getId(){
    	return studId;
    }

    vector<int> getBooks(){
        return books;
    }

    void resetBooks(){
        books.clear();
    }

};

void addStudent(vector<Student> &students){
    Student stud;
    stud.addStudent();
    students.push_back(stud);

//--->
    char chr;
    cout << "Do you want to add more? (Y/N)" << endl;
    cin >> chr;
    if (chr == 'Y' || chr == 'y'){
        addStudent(students);
    }
}

vector<Student> createStud(){
    vector<class Student> students;
    addStudent(students);

    return students;
}

void studDisplayAll(vector<Student> students){
    for (int i = 0; i < students.size(); i++){
        students[i].getDetails();
    }
    cout << endl;
}

void displayStudents(int id, vector<Student> students){
    int index = getIndex(id, students);
    if (index < 0)  
        return;
    else
        students[index].getDetails();
}

void removeStudent(int id, vector<Student> &students){
    int index = getIndex(id, students);
    if (index < 0)  
        return;
    else
        students.erase(students.begin() + index);

    cout << "Student with id " << id << " deleted successfully!" << endl;
    cout << endl;
}


void modifyBranch(Student &stud){
    string sBranch;
    cout << "Enter new branch: ";
    cin >> sBranch;
    stud.setBranch(sBranch);
}

void modifyContact(Student &stud){
    int num;
    cout << "Enter new number: ";
    cin >> num;
    stud.setContact(num);
}

void modifyStudent(int id, vector<Student> &students){
    int index = getIndex(id, students);
    if (index < 0)
        return;

    int inp;
    cout << endl;
    cout << "What do you want to modify: " << endl;
    cout << "1. Student Branch" << endl;
    cout << "2. Contact Number" << endl;
    cout << "3. Clear all Books Details" << endl;

    cout << endl << "Enter your choice: ";
    cin >> inp;
    switch(inp){
        case 1: 
            modifyBranch(students[index]);
            break;
        case 2: 
            modifyContact(students[index]);
            break;
        case 3:
            students[index].resetBooks();
    }

    cout << "Do you want to modify more? (Y/N)" << endl;
    char chr;
    cin >> chr;
    if (chr == 'Y' || chr == 'y'){
        modifyStudent(id, students);
    }
}
