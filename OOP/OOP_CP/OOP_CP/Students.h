#pragma once
#ifndef STUDENTS_H
#define STUDENTS_H
#include <iostream>
#include <string>
#include "sqlite3.h"

class Student {
    int studId;
    std::string studName;
    std::string studBranch;
    long int studContact;

public:
    void addStudent();

    /*Setter Functions*/
    void setBranch(std::string branch);
    void setContact(int num);

    /*Getter Functions*/
    void getDetails();
    int getId();

    /*Insert into database function is friend*/
    friend void insertIntoStudents(Student*);
};

/*Call to addStudent function of Student class*/
void addStudent();

/*Modify functions to make changes in Students table in Library database*/
void modifyBranch(int id);
void modifyContact(int id);
void modifyStudent(int id);

/*Database functions linked to Students table in Library Database*/
static int callbackStud(void* unused, int count, char** data, char** colNames);
void insertIntoStudents(Student* student);
void displayStudents(int id = 0);
void updateStud(int id, int inp, std::string temp);
void deleteStud(int id);
#endif