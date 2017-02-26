#include "Admin.h"

Admin::Admin()
{
    username = "Admin";
}

void Admin::CreateUser(string username, string password, string firstName, string secondName, string phone, string streetNum, string street)
{
    Guest tmp;
    tmp.SetUser(username);
    tmp.SetPass(password);
    tmp.SetFirstName(firstName);
    tmp.SetSecondName(secondName);
    tmp.SetPhone(phone);
    tmp.SetStreetNum(streetNum);
    tmp.SetStreet(street);
    AddUserInList(tmp);
}

void Admin::AddUserInList(Guest tmp)
{
    UserList.push_back(tmp);
}

void Admin::DisplayUserList()
{
    if (!UserList.empty()) {
        for (int i = 0; i < UserList.size(); i++) {
            cout << UserList[i].GetUser() << endl;
        }
    } else {
        cout << "List of users is empty" << endl;
    }
}

void Admin::DeleteUser(Guest tmp)
{
    if (!UserList.empty()) {
        for (int i = 0; i < UserList.size(); i++) {
            if (UserList[i].GetUser() == tmp.GetUser()) {
                UserList.erase(UserList.begin() + i);
                break;
            }
        }
    }
}

void Admin::SetPassword(string password)
{
    this -> password = password;
}

string Admin::GetUsername()
{
    return username;
}

string Admin::GetPassword()
{
    return password;
}

Admin Singleton()
{
    static Admin instance;
    return instance;
}

