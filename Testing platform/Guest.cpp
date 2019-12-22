#include "Guest.h"

Guest::Guest()
{

}

void Guest::AddClass(Class tmp)
{
    ClassList.push_back(tmp);
}

void Guest::CreateClass(vector < Quiz > QuizList, string name)
{
    Class tmp;

    for (int i = 0; i < QuizList.size(); i++) {
        tmp.AddQuiz(QuizList[i]);
    }

    tmp.SetName(name);

    AddClass(tmp);
}

void Guest::DisplayClasses()
{
    if (!ClassList.empty()) {
        for (int i = 0; i < ClassList.size(); i++) {
            cout << ClassList[i].GetName() << endl;
        }
    } else {
        cout << "There are no classes" << endl;
    }
}

void Guest::SetUser(string username)
{
    this -> username = username;
}

void Guest::SetPass(string password)
{
    this -> password = password;
}

void Guest::SetFirstName(string firstName)
{
    this -> firstName = firstName;
}

void Guest::SetSecondName(string secondName)
{
    this -> secondName = secondName;
}

void Guest::SetPhone(string phone)
{
    this -> phone = phone;
}

void Guest::SetStreetNum(string streetNum)
{
    this -> streetNum = streetNum;
}

void Guest::SetStreet(string street)
{
    this -> street = street;
}

string Guest::GetUser()
{
    return username;
}

string Guest::GetPass()
{
    return password;
}

string Guest::GetFirstName()
{
    return firstName;
}

string Guest::GetSecondName()
{
    return secondName;
}

string Guest::GetPhone()
{
    return phone;
}

string Guest::GetStreetNum()
{
    return streetNum;
}

string Guest::GetStreet()
{
    return street;
}

int Guest::GetClassListSize()
{
    return ClassList.size();
}
