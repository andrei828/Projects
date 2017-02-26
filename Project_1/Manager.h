#ifndef Project_1_Manager_h
#define Project_1_Manager_h

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>

using namespace std;

class Manager {
public:
    
    Manager();
    
    void SetPath(string path);
    void CreateFile(char path[], char mask[], char name[]);
    
    string GetPath();
    
private:
    
    string path;
    
};

Manager::Manager()
{
    
}

void Manager::SetPath(string path)
{
    this -> path = path;
}

void Manager::CreateFile(char path[], char mask[], char name[])
{
    char str[80];
    path = "/Users/Andrei/Documents/Swift/Project_1/Project_1/";
    name = "Sample";
    mask = ".txt";
    strcpy(str, path);
    strcat(str, name);
    strcat(name, mask);
    
    fstream file;
    file.open(name, ios::in | ios::out | ios::app);
    if (!file.is_open()) {
        cout << "There was an error opening the file " << endl;
    } else{
        file << "Success"<< endl;
    }
}

string Manager::GetPath()
{
    return path;
}

#endif
