#pragma once
#ifndef BOOKS_H
#define BOOKS_H
#include <iostream>
#include <string>
#include "sqlite3.h"

class Book {
    int bookId;
    std::string bookName;
    std::string authName;
    int totalCount;

public:
    void addBook();

    /*Setter functions*/
    void setName(std::string name);
    void setAuth(std::string name);
    void setCount(int num);

    /*Getter Functions*/
    void getDetails();
    int getId();
    int getAvailableBooks();

    /*Insert into database function is friend*/
    friend void insertIntoBooks(Book* book);
};

/*Call to addBook function of Book class*/
void addBook();

/*Modify functions to make changes in existing database*/
void modifyBookName(int id);
void modifyAuthName(int id);
void modifyBooks(int id);

/*Database functions linked to Books table in Library Database*/
static int callbackBooks(void* unused, int count, char** data, char** colNames);
void insertIntoBooks(Book* book);
void displayBooks(int id = 0);
void updateBook(int id, int inp, std::string temp);
void deleteBook(int id);
#endif