#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "Guest.h"

using namespace std;

class Admin {
public:

    Admin();

    friend Admin Singleton();

    void CreateUser(string username, string password, string firstName, string secondName, string phone, string streetNum, string street);
    void SetPassword(string password);
    void DeleteUser(Guest tmp);
    void DisplayUserList();
    void AddUserInList(Guest tmp);

    string GetUsername();
    string GetPassword();

    vector < Guest > UserList;

private:

    string username;
    string password;
};


#endif // ADMIN_H
