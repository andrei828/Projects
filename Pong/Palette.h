#ifndef Pong_Palette_h
#define Pong_Palette_h

#define MapSize 82
#define Wall '#'
#define BallObject '@'

class Palette {
public:
   
    Palette();
    
    // incaplsuation
    int Get_length();
    int Get_pos_y();
    int Get_pos_x();
    int Get_score();
    int GetInput();
    
    void Set_length(int length);
    void Set_pos_x(int pos_x);
    void Set_pos_y(int pos_y);
    void Set_score(int score);
    void SetInput(char input);
    // end incapsulation
    
    void MoveUp();
    void MoveDown();
    
private:
    
    int length;
    int score;
    int pos_x;
    bool pos_y;
    char input;
};

void Palette::MoveUp()
{
    --pos_x;
    length = pos_x + 6;
}

void Palette::MoveDown()
{
    ++pos_x;
    length = pos_x + 6;
}

// ***********  Get incapsulated variables **************

int Palette::Get_length()
{
    return length;
}

int Palette::Get_pos_x()
{
    return pos_x;
}

int Palette::Get_score()
{
    return score;
}

int Palette::Get_pos_y()
{
    if (pos_y == 0) {
        return 1;
    } else {
        return MapSize - 1;
    }
}

int Palette::GetInput()
{
    return input;
}

//************  End *****************


//************  Set incapsulated variables ***************

void Palette::Set_length(int length)
{
    this -> length = length;
}

void Palette::Set_pos_x(int pos_x)
{
    this -> pos_x = pos_x;
}

void Palette::Set_pos_y(int pos_y)
{
    this -> pos_y = pos_y;
}

void Palette::Set_score(int score)
{
    this -> score = score;
}

void Palette::SetInput(char input)
{
    this -> input = input;
}

//************  End *****************

//**********  Constructor *************

Palette::Palette()
{
    //this -> pos_y = pos_y;
    pos_x  = 19;
    length = pos_x + 6;
    score  = 0;
}

//********** End Constructor **********
#endif
