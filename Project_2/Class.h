#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "Quiz.h"

using namespace std;

class Class {
public:

    Class();

    void SetName(string name);
    void CreateQuiz(string name, short grade);
    void AddQuiz(Quiz tmp);

    string GetName();

    vector < Quiz > QuizList;

private:

    string name;
};


#endif // CLASS_H
