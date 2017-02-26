#ifndef GUEST_H
#define GUEST_H


#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "Class.h"

using namespace std;

class Guest {
public:

    Guest();

    void SetUser(string username);
    void SetPass(string password);
    void SetFirstName(string firstName);
    void SetSecondName(string secondName);
    void SetPhone(string phone);
    void SetStreetNum(string streetNum);
    void SetStreet(string street);
    void AddClass(Class tmp);
    void CreateClass(vector < Quiz > QuizList, string name);
    void DisplayClasses();

    string GetUser();
    string GetPass();
    string GetFirstName();
    string GetSecondName();
    string GetPhone();
    string GetStreetNum();
    string GetStreet();

    int GetClassListSize();
    vector < Class > ClassList;

private:

    int ClassListSize;

    string username;
    string password;
    string firstName;
    string secondName;
    string phone;
    string streetNum;
    string street;
};


#endif // GUEST_H
