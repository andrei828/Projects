#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "Admin.h"
#include "Guest.h"
#include "Class.h"
#include "Quiz.h"

using namespace std;

void DisplaySetAdminPassword();
void DisplayRegisterUser();
void DisplayAdminVsGuest();
void DisplayAdminLogin();
void DisplayGuestLogin();
void DisplayUserLogin();
void DisplayUserList();
void DisplayClasses(Guest & tmp);
void DisplayQuizzes(Class & tmp, Guest & guest);
void DisplayGrade  (Quiz  & tmp, Class & cls, Guest & guest);

void DisplayRegisterUserAdmin();
void DisplayClassesAdmin(Guest & tmp);
void DisplayQuizzesAdmin(Class & tmp, Guest & guest);
void DisplayGradeAdmin  (Quiz  & tmp, Class & cls, Guest & guest);

void SaveEverything();
void LoadEverything();

Admin root;
string pswd;

int main() {
    
    LoadEverything();
    
    DisplaySetAdminPassword();
    
    DisplayAdminVsGuest();
    
}

void LoadEverything()
{
    fstream database;
    
    database.open("database.txt");
    
    if (!database.is_open()) {
        cout << "Could not open the database" << endl;
    } else {
        
        //getting the number of users
        int UserListSize;
        database >> UserListSize;
        
        for (int i = 0; i < UserListSize; i++) {
            //adding the user info
            string username;
            string password;
            string firstName;
            string secondName;
            string phone;
            string streetNum;
            string street;
            
            database >> username;
            database >> password;
            database >> firstName;
            database >> secondName;
            database >> phone;
            database >> streetNum;
            database >> street;
            
            Guest tmp;
            tmp.SetUser(username);
            tmp.SetPass(password);
            tmp.SetFirstName(firstName);
            tmp.SetSecondName(secondName);
            tmp.SetPhone(phone);
            tmp.SetStreetNum(streetNum);
            tmp.SetStreet(street);
            root.AddUserInList(tmp);
            
            //getting the number of classes
            int ClassListSize;
            database >> ClassListSize;
            
            for (int j = 0; j < ClassListSize; j++) {
                //adding the classes to the user
                string name;
                
                database >> name;
                
                Class tmp;
                tmp.SetName(name);
                root.UserList[i].AddClass(tmp);
                
                //getting the number of quizzes
                int QuizListSize;
                database >> QuizListSize;
                
                for (int k = 0; k < QuizListSize; k++) {
                    //adding the quizzes to the class
                    string name;
                    short grade;
                    
                    database >> name;
                    
                    //getting the number of questions in a quiz
                    int QuizContentSize;
                    database >> QuizContentSize;
                    
                    vector < pair < vector < string > , char > > QuizContent;
                    pair < vector < string > , char > aux;
                    string auxiliarString;
                    
                    for (int ot = 0; ot < QuizContentSize; ot++) {
                        database.ignore(1000, '\n');
                        for (int to = 0; to < 5; to++) {
                            getline(database, auxiliarString);
                            aux.first.push_back(auxiliarString);
                        }
                        database >> aux.second;
                        QuizContent.push_back(aux);
                        aux.first.clear();
                    }
                    database >> grade;
                    Quiz temp;
                    temp.SetName(name);
                    temp.SetQuiz(QuizContent);
                    temp.SetGrade(grade);
                    root.UserList[i].ClassList[j].AddQuiz(temp);
                    QuizContent.clear();
                }
            }
        }
        database.close();
    }
}

void SaveEverything()
{
    fstream database;
    
    database.open("database.txt");
    
    if (!database.is_open()) {
        cout << "Could not open the database" << endl;
    } else {
        
        //index for UserList
        unsigned long index = root.UserList.size();
        database << index << endl;
        
        for (int i = 0; i < index; i++) {
            database << root.UserList[i].GetUser()       << endl;
            database << root.UserList[i].GetPass()       << endl;
            database << root.UserList[i].GetFirstName()  << endl;
            database << root.UserList[i].GetSecondName() << endl;
            database << root.UserList[i].GetPhone()      << endl;
            database << root.UserList[i].GetStreetNum()  << endl;
            database << root.UserList[i].GetStreet()     << endl;
            
            //index for ClassList
            unsigned long index = root.UserList[i].ClassList.size();
            database << index << endl;
            
            for (int j = 0; j < index; j++) {
                database << root.UserList[i].ClassList[j].GetName() << endl;
                
                //index for QuizList
                unsigned long index = root.UserList[i].ClassList[j].QuizList.size();
                database << index << endl;
                
                for (int k = 0; k < index; k++) {
                    database << root.UserList[i].ClassList[j].QuizList[k].GetName() << endl;
                    
                    
                    //index for QuizContent
                    unsigned long index = root.UserList[i].ClassList[j].QuizList[k].QuizContent.size();
                    database << index << endl;
                    
                    for (int x = 0; x < index; x++) {
                        for (int y = 0; y < 5; y++) {
                            database << root.UserList[i].ClassList[j].QuizList[k].QuizContent[x].first[y] << endl;
                        }
                        database << root.UserList[i].ClassList[j].QuizList[k].QuizContent[x].second << endl;
                    }
                    database << root.UserList[i].ClassList[j].QuizList[k].GetGrade() << endl;
                }
            }
        }
        database.close();
    }
}

void DisplaySetAdminPassword()
{
    ifstream pass("passFile.in");
    
    pass >> pswd;
    
    root.SetPassword(pswd);
}

void DisplayRegisterUser()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    Guest user;
    
    string username;
    string password;
    string firstName;
    string secondName;
    string phone;
    string streetNum;
    string street;
    
    cout << "Username:      "; cin >> username;
    cout << "Password:      "; cin >> password;
    cout << "First Name:    "; cin >> firstName;
    cout << "Second Name:   "; cin >> secondName;
    cout << "Phone Number:  "; cin >> phone;
    cout << "Street Name:   "; cin >> street;
    cout << "Street Number: "; cin >> streetNum;
    
    cout << endl << endl;
    int number_of_classes;
    cout << "Insert the number of classes: "; cin >> number_of_classes;
    
    
    string name;
    
    for (int i = 0; i < number_of_classes; i++) {
    begin1:
        Class * tmp = new Class();
        cout << "Insert the name of the class " << i+1 << ": ";
        cin >> name;
        
        for (int j = 0; j < user.GetClassListSize(); j++) {
            if (name == user.ClassList[j].GetName()) {
                cout << "Username taken" << endl;
                goto begin1;
            }
        }
        
        tmp -> SetName(name);
        cout << endl;
        short isQuiz;
    begin2:
        cout << "Do you have any quizzes in this class?" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No, I'll add them later" << endl;
        cin  >> isQuiz;
        
        if (isQuiz == 1) {
        beginQuiz:
            short number_of_quizzes;
            cout << "Insert the number of quizzes in this class: ";
            cin >> number_of_quizzes;
            string QuizName;
            
            Quiz * temp = new Quiz[number_of_quizzes];
            
            for (int j = 0; j < number_of_quizzes; j++) {
                cout << "Insert the name of the quiz: ";
                cin  >> QuizName;
                temp[j].SetName(QuizName);
                tmp -> AddQuiz(temp[j]);
            } cout << endl;
            delete [] temp;
        } else if (isQuiz == 2){
            continue;
        } else {
            cout << "Choose a valid command" << endl;
            goto begin2;
        }
        
        user.AddClass(*tmp);
        delete tmp;
    }
    user.SetUser(username);
    user.SetPass(password);
    user.SetFirstName(firstName);
    user.SetSecondName(secondName);
    user.SetPhone(phone);
    user.SetStreetNum(streetNum);
    user.SetStreet(street);
    
    root.AddUserInList(user);
    SaveEverything();
    cout << "Registered successfully" << endl;
    cout << "Enter any key to proceed" << endl;
    char x; cin >> x;
    DisplayGuestLogin();
}

void DisplayRegisterUserAdmin()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    Guest user;
    
    string username;
    string password;
    string firstName;
    string secondName;
    string phone;
    string streetNum;
    string street;
    
    cout << "Username:      "; cin >> username;
    cout << "Password:      "; cin >> password;
    cout << "First Name:    "; cin >> firstName;
    cout << "Second Name:   "; cin >> secondName;
    cout << "Phone Number:  "; cin >> phone;
    cout << "Street Name:   "; cin >> street;
    cout << "Street Number: "; cin >> streetNum;
    
    cout << endl << endl;
    int number_of_classes;
    cout << "Insert the number of classes: "; cin >> number_of_classes;
    
    
    string name;
    
    for (int i = 0; i < number_of_classes; i++) {
    begin1:
        Class * tmp = new Class();
        cout << "Insert the name of the class " << i+1 << ": ";
        cin >> name;
        
        for (int j = 0; j < user.GetClassListSize(); j++) {
            if (name == user.ClassList[j].GetName()) {
                cout << "Username taken" << endl;
                goto begin1;
            }
        }
        
        tmp -> SetName(name);
        cout << endl;
        short isQuiz;
    begin2:
        cout << "Do you have any quizzes in this class?" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No, I'll add them later" << endl;
        cin  >> isQuiz;
        
        if (isQuiz == 1) {
        beginQuiz:
            short number_of_quizzes;
            cout << "Insert the number of quizzes in this class: ";
            cin >> number_of_quizzes;
            string QuizName;
            
            Quiz * temp = new Quiz[number_of_quizzes];
            
            for (int j = 0; j < number_of_quizzes; j++) {
                cout << "Insert the name of the quiz: ";
                cin  >> QuizName;
                temp[j].SetName(QuizName);
                tmp -> AddQuiz(temp[j]);
            } cout << endl;
            delete [] temp;
        } else if (isQuiz == 2){
            continue;
        } else {
            cout << "Choose a valid command" << endl;
            goto begin2;
        }
        
        user.AddClass(*tmp);
        delete tmp;
    }
    user.SetUser(username);
    user.SetPass(password);
    user.SetFirstName(firstName);
    user.SetSecondName(secondName);
    user.SetPhone(phone);
    user.SetStreetNum(streetNum);
    user.SetStreet(street);
    
    root.AddUserInList(user);
    SaveEverything();
    cout << "Registered successfully"  << endl;
    cout << "Enter any key to proceed" << endl;
    string c; cin >> c;
    DisplayUserList();
}


void DisplayUserLogin()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    string name;
    string pswd;
    
begin3:
    cout << "Insert the username: ";
    cin  >> name;
    
    cout << "Insert the password: ";
    cin  >> pswd;
    
    for (int i = 0; i < root.UserList.size(); i++) {
        if (name == root.UserList[i].GetUser() && pswd == root.UserList[i].GetPass()) {
            DisplayClasses(root.UserList[i]);
        }
    }
    cout << "Wrong username or password "<< endl;
    goto begin3;
}

void DisplayClasses(Guest & tmp)
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    cout << "Type 0 to Log Out" << endl << endl;
    
    cout << "Name of classes: " << endl << endl;
    for (int i = 0; i < tmp.GetClassListSize(); i++) {
        cout << i+1 << ") "<< tmp.ClassList[i].GetName() << endl;
    }
    int c; cout << "Choose the class: "; cin >> c;
    
    if (c == 0) {
        DisplayGuestLogin();
    } else {
        for (int i = 0; i < tmp.GetClassListSize(); i++) {
            if (c-1 == i) {
                DisplayQuizzes(tmp.ClassList[i], tmp);
            }
        }
    }
}

void DisplayClassesAdmin(Guest & tmp)
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    cout << "Type 0 to Log Out" << endl << endl;
    
    cout << "        Admin" << endl << endl;
    
    cout << "Name of classes: " << endl << endl;
    for (int i = 0; i < tmp.GetClassListSize(); i++) {
        cout << i+1 << ") "<< tmp.ClassList[i].GetName() << endl;
    }
    
    short k;
    cout << endl << "*******************************" << endl;
    cout << "1) See the quizzes of the class" << endl;
    cout << "2) Add a class" << endl;
    cout << "3) Delete a class" << endl;
    
    cin >> k;
    
    if (k == 1) {
        int c; cout << "Choose the number that indicates the class: ";
        cin >> c;
        if (c == 0) {
            DisplayUserList();
        } else {
            for (int i = 0; i < tmp.GetClassListSize(); i++) {
                if (c-1 == i) {
                    DisplayQuizzesAdmin(tmp.ClassList[i], tmp);
                }
            }
        }
    } else if (k == 2) {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
        string name;
        cout << "Enter the name of the class: "; cin >> name;
        bool ok = true;
        
        for (int i = 0; i < tmp.ClassList.size(); i++) {
            if (name == tmp.ClassList[i].GetName()) {
                ok = false;
            }
        }
        
        if (ok) {
            Class temp;
            temp.SetName(name);
            tmp.AddClass(temp);
        }
        SaveEverything();
        DisplayClassesAdmin(tmp);
        
    } else if (k == 3) {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    begin10:
        string name;
        cout << "Enter the name of the class: "; cin >> name;
        bool ok = false;
        
        for (int i = 0; i < tmp.ClassList.size(); i++) {
            if (name == tmp.ClassList[i].GetName()) {
                tmp.ClassList.erase(tmp.ClassList.begin() + i);
                ok = true;
                break;
            }
        }
        
        if (!ok) {
            cout << "Enter a valid name" << endl;
            goto begin10;
        }
        SaveEverything();
        DisplayClassesAdmin(tmp);
    } else if (k == 0) {
        DisplayUserList();
    }
}

void DisplayQuizzes(Class & tmp, Guest & guest)
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    cout << "Type 0 to go back" << endl << endl;
    
    cout << "Name of Quizzes: " << endl << endl;
    for (int i = 0; i < tmp.QuizList.size(); i++) {
        cout << i+1 << ") " << tmp.QuizList[i].GetName() << endl;
    }
    int c; cout << "Choose the quiz: "; cin >> c;
    
    if (c == 0) {
        DisplayClasses(guest);
    } else {
        for (int i = 0; i < tmp.QuizList.size(); i++) {
            if (c-1 == i) {
                DisplayGrade(tmp.QuizList[i], tmp, guest);
            }
        }
    }
}

void DisplayQuizzesAdmin(Class & tmp, Guest & guest)
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    cout << "Type 0 to go back" << endl << endl;
    
    cout << "        Admin" << endl << endl;
    
    cout << "Name of Quizzes: " << endl << endl;
    for (int i = 0; i < tmp.QuizList.size(); i++) {
        cout << i+1 << ") " << tmp.QuizList[i].GetName() << endl;
    }
    
    short k;
    cout << endl << "************************" << endl;
    cout << "1) See the grade of quiz" << endl;
    cout << "2) Add a quiz" << endl;
    cout << "3) Delete quiz" << endl;
    
    cin >> k;
    
    if (k == 1) {
        int c; cout << "Choose the number that indicates the quiz: ";
        cin >> c;
        
        if (c == 0) {
            DisplayClassesAdmin(guest);
        } else {
            for (int i = 0; i < tmp.QuizList.size(); i++) {
                if (c-1 == i) {
                    DisplayGradeAdmin(tmp.QuizList[i], tmp, guest);
                }
            }
        }
    } else if (k == 2) {
        //#####################################################
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
        int a;
        string name;
        cout << "Enter the name of the quiz: "; cin >> name;
        cout << "Do you know the grade for this quiz?" << endl;
        cout << "1) Yes" << endl;
        cout << "2) No"  << endl;
        cin  >> a;
        if (a == 1) {
            short grade;
            cout << "Insert the grade: "; cin >> grade;
            tmp.CreateQuiz(name, grade);
            DisplayQuizzesAdmin(tmp, guest);
        } else if (a == 2) {
            cout << "Ok" << endl;
            tmp.CreateQuiz(name, -1);
            SaveEverything();
            DisplayQuizzesAdmin(tmp, guest);
        }
        
    } else if (k == 3) {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    begin9:
        string name;
        cout << "Enter the name of the quiz: "; cin >> name;
        int ok = false;
        for (int i = 0; i < tmp.QuizList.size(); i++) {
            if (name == tmp.QuizList[i].GetName()) {
                tmp.QuizList.erase(tmp.QuizList.begin() + i);
                ok = true;
                break;
            }
        }
        if (!ok) {
            cout << "Enter a valid name" << endl;
            goto begin9;
        }
        SaveEverything();
        DisplayQuizzesAdmin(tmp, guest);
    } else if (k == 0) {
        DisplayClassesAdmin(guest);
    }
}

void DisplayGrade(Quiz & tmp, Class & cls, Guest & guest)
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    cout << "Type 0 to go back" << endl;
    cout << "Type -1 to redo the quiz" << endl << endl;
begin9:
    if (tmp.GetGrade() != -1) {
        cout << "Grade: " << tmp.GetGrade() << endl << endl;
    } else {
        char a;
        float grade = 100;
        float get   = grade / tmp.QuizContent.size();
        for (int i = 0; i < tmp.QuizContent.size(); i++) {
                cout << tmp.QuizContent[i].first[0] << endl;
                cout << "a) " << tmp.QuizContent[i].first[1] << endl;
                cout << "b) " << tmp.QuizContent[i].first[2] << endl;
                cout << "c) " << tmp.QuizContent[i].first[3] << endl;
                cout << "d) " << tmp.QuizContent[i].first[4] << endl;
                cout << "> ";
            cin >> a;
            if (a != tmp.QuizContent[i].second) {
                grade -= get;
            } else if (a == '0') {
                DisplayQuizzes(cls, guest);
            }
        }
        cout << "Your grade is: " << grade << endl;
        tmp.SetGrade(grade);
    }
    
    cout << "Type any key to go back "<< endl;
    string c; cin >> c;
    if (c == "-1") {
        tmp.SetGrade(-1);
        goto begin9;
    }
    SaveEverything();
    DisplayQuizzes(cls, guest);
}

void DisplayGradeAdmin(Quiz & tmp, Class & cls, Guest & guest)
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    cout << "Type 0 to go back" << endl;
    if (tmp.QuizContent.empty()) {
        cout << "Type -1 to create the test" << endl << endl;
    } else {
        cout << endl;
    }
    cout << "        Admin" << endl << endl;
    
    
    if (tmp.GetGrade() != -1) {
        cout << "Grade: " << tmp.GetGrade() << endl << endl;
    } else if (tmp.GetGrade() == -1) {
        cout << "The user didn't take the test yet" << endl;
    }
    
begin8:
    short i;
    cout << "Insert grade: ";   cin >> i;
    if (i > 0 && i < 11) {
        tmp.SetGrade(i);
    } else if (i == 0) {
        DisplayQuizzesAdmin(cls, guest);
    } else if (i == -1) {
        pair < vector < string > , char > QuizContent;
        int number_of_q;
        string full[5];
        string question;
        string answer1;
        string answer2;
        string answer3;
        string answer4;
        char a;
        cout << "Enter the number of questions: ";
        cin  >> number_of_q;
        
        for (int o = 0; o < number_of_q; o++) {
            cin.ignore(1000, '\n');
            cout << "Enter the question: ";
            getline(cin, question);

            cout << "a) ";
            getline(cin, answer1);
            
            cout << "b) ";
            getline(cin, answer2);
            
            cout << "c) ";
            getline(cin, answer3);
            
            cout << "d) ";
            getline(cin, answer4);
            
            cout << "Enter the letter that indicates the answer: ";
            cin  >> a;
            
            full[0] = question;
            full[1] = answer1;
            full[2] = answer2;
            full[3] = answer3;
            full[4] = answer4;
            
            pair < vector < string >, char > aux;
            for (int k = 0; k < 5; k++) {
                aux.first.push_back(full[k]);
            }
            aux.second = a;
            tmp.QuizContent.push_back(aux);
        }
        SaveEverything();
        cout << "Test entered succesfully" << endl;
        cout << "Type any key to go back";
        char x;
        cin >> x;
        DisplayQuizzesAdmin(cls, guest);

    } else {
        cout << "Insert a valid grade" << endl;
        goto begin8;
    }
}

void DisplayUserList()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
begin4:
    if (!root.UserList.empty()) {
        cout << "User names:" << endl;
        for (int i = 0; i < root.UserList.size(); i++) {
            cout << root.UserList[i].GetUser() << endl;
        }
    } else {
        cout << "There are no users yet" << endl;
    }
    
    cout << "1) Register a new user" << endl;
    cout << "2) Delete a user" << endl;
    cout << "3) Modify a user" << endl;
    cout << "4) Go back"       << endl;
    
    short c; cin >> c;
    
    if (c == 1) {
        DisplayRegisterUserAdmin();
    } else if (c == 2) {
        string name;
        int ok = false;
        cout << "Insert the username: "; cin >> name;
        for (int i = 0; i < root.UserList.size(); i++) {
            if (name == root.UserList[i].GetUser()) {
                ok = true;
                root.DeleteUser(root.UserList[i]);
                cout << "Deleted successfully" << endl;
                SaveEverything();
                goto begin4;
            }
        }
        if (!ok) {
            cout << "Wrong name" << endl;
            goto begin4;
        }
        
    } else if (c == 3) {
        string name;
        cout << "Insert the name of the user: ";
        cin  >> name;
        int ok = false;
        for (int i = 0; i < root.UserList.size(); i++) {
            if (name == root.UserList[i].GetUser()) {
                ok = true;
                DisplayClassesAdmin(root.UserList[i]);
            }
        }
        if (!ok) {
            cout << "Wrong name" << endl;
            goto begin4;
        }
        
    } else if (c == 4) {
        DisplayAdminVsGuest();
    } else {
        cout << "Choose a valid command" << endl;
        goto begin4;
    }
    
}

void DisplayGuestLogin()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    pswd = "";
begin5:
    cout << "1) Register user" << endl;
    cout << "2) Login as user" << endl;
    cout << "3) Go back"       << endl;
    
    int c; cin >> c;
    if (c == 1){
        DisplayRegisterUser();
    } else if (c == 2){
        DisplayUserLogin();
    } else if (c == 3) {
        DisplayAdminVsGuest();
    } else {
        cout << "Choose a valid command" << endl;
        goto begin5;
    }
    
}

void DisplayAdminLogin()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
begin6:
    pswd = "";
    cout << "Insert the admin password: ";
    cin >> pswd;
    
    if (pswd == root.GetPassword()) {
        DisplayUserList();
    } else {
        goto begin6;
    }
}

void DisplayAdminVsGuest()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    cout << "1) Admin" << endl;
    cout << "2) User " << endl;
    cout << "3) Save " << endl;
    
begin:
    short c; cin >> c;
    if (c == 1){
        DisplayAdminLogin();
    } else if (c == 2){
        DisplayGuestLogin();
    } else if (c == 3) {
        SaveEverything();
    } else {
        cout << "Choose a valid command" << endl;
        goto begin;
    }
}
