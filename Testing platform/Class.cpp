#include "Class.h"

Class::Class()
{

}

void Class::CreateQuiz(string name, short grade)
{
    Quiz tmp;
    tmp.SetName(name);
    tmp.SetGrade(grade);
    AddQuiz(tmp);
}

void Class::AddQuiz(Quiz tmp)
{
    QuizList.push_back(tmp);
}

void Class::SetName(string name)
{
    this -> name = name;
}

string Class::GetName()
{
    return name;
}
