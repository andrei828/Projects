#ifndef QUIZ_H
#define QUIZ_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using  namespace std;

class Quiz {
public:

    Quiz();

    void SetName(string name);
    void SetGrade(short grade);
    void SetQuiz(vector < pair < vector < string > , char > > QuizContent);

    short GetGrade();
    string GetName();

    vector < string > Question;
    vector < pair < vector < string > , char > > QuizContent;
    
private:

    string name;
    short grade;

};


#endif // QUIZ_H
