#ifndef Pong_Map_h
#define Pong_Map_h

#include <iostream>
#include "Ball.h"
#include "Palette.h"

#define MapSize 84
#define Wall '#'
#define BallObject '@'
#define Pall '$'

using namespace std;

//map 16x16
//ball 8x8

class Map {
public:
    
    Map();
    
    void Display();
    void PlaceObjects();
    void CleanMap();
    void FindBallNeighbour();

    bool GetEnd();
    
private:

    char c;
    bool end;
    bool UpDown;
    bool LeftRight;
    char map[MapSize][MapSize];
    Ball ball;
    Palette palette1;
    Palette palette2;
};

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    
    return 0;
}

void Map::FindBallNeighbour()
{
    // map[ball.Get_pos_x()][ball.Get_pos_y()] = BallObject;
    if (LeftRight == 0) {
        if (map[ball.Get_pos_x() - 1][ball.Get_pos_y() - 1] == '$') {
            LeftRight = 1;
        } else if (map[ball.Get_pos_x()][ball.Get_pos_y() - 1] == '$') {
            LeftRight = 1;
        } else if (map[ball.Get_pos_x() + 1][ball.Get_pos_y() - 1] == '$') {
            LeftRight = 1;
        }
    } else {
        if (map[ball.Get_pos_x() - 1][ball.Get_pos_y() + 1] == '$') {
            LeftRight = 0;
        } else if (map[ball.Get_pos_x()][ball.Get_pos_y() + 1] == '$') {
            LeftRight = 0;
        } else if (map[ball.Get_pos_x() + 1][ball.Get_pos_y() + 1] == '$') {
            LeftRight = 0;
        }
    }
}

//********** Display **********

void Map::Display()
{
    CleanMap();
    PlaceObjects();
    
    for (int i = 0; i < MapSize * 2; i++) {
        cout << Wall;
    } cout << endl;
    
    for (int i = 0; i < (MapSize - 1) / 2; i++) {
        cout << Wall;
        for (int j = 0; j < MapSize - 1; j++) {
            if (map[i][j] == 0) {
                cout << "  ";
            } else {
                cout << map[i][j] << " ";
            }
        }cout << Wall << endl;
    }
    
    for (int i = 0; i < MapSize * 2; i++) {
        cout << Wall;
    } cout << endl << endl << endl << endl << endl << endl << endl << endl;
}

void Map::CleanMap()
{
    for (int i = 0; i < MapSize / 2; i++) {
        for (int j = 0; j < MapSize; j++) {
            map[i][j] = ' ';
        }
    }
}

//********** End Display **********

void Map::PlaceObjects()
{
    map[ball.Get_pos_x()][ball.Get_pos_y()] = BallObject;
    
    if(kbhit()){
        c = getchar();
        if (c == 'x') {
            palette1.MoveUp();
        } else if (c == 'v') {
            palette1.MoveDown();
        } else if (c == 'k') {
            palette2.MoveUp();
        } else if (c == 'm') {
            palette2.MoveDown();
        }
    }
    for (int i = palette1.Get_pos_x(); i <= palette1.Get_length(); i++) {
        map[i][palette1.Get_pos_y()] = Pall;
    }
    
    for (int i = palette2.Get_pos_x(); i <= palette2.Get_length(); i++) {
        map[i][palette2.Get_pos_y()] = Pall;
    }

        ball.BallStatus(UpDown);
        ball.BallDirection(LeftRight);
    if (ball.collisionGoodWall()) {
        if (UpDown == 0) {
            UpDown = 1;
        } else {
            UpDown = 0;
        }
    }
    FindBallNeighbour();
    if (ball.collisionBadWall()) {
        end  = true;
    }
}

bool Map::GetEnd()
{
    return end;
}

//**********  Constructor *************

Map::Map()
{
    for (int i = 0; i < MapSize; i++) {
        for (int j = 0; j < MapSize; j++) {
            map[i][j] = NULL;
        }
    }
    
    end = false;
    UpDown = 0;
    LeftRight = 0;
    palette1.Set_pos_y(0);
    palette2.Set_pos_y(1);
}

//********** End Constructor **********


#endif
