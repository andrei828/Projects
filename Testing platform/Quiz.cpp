#include "Quiz.h"

Quiz::Quiz()
{
    grade = -1;
}

void Quiz::SetName(string name)
{
    this -> name = name;
}

void Quiz::SetGrade(short grade)
{
    this -> grade = grade;
}

void Quiz::SetQuiz(vector < pair < vector < string > , char > > QuizContent)
{
    this -> QuizContent = QuizContent;
}

short Quiz::GetGrade()
{
    return grade;
}

string Quiz::GetName()
{
    return name;
}

