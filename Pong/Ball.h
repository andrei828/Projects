#ifndef Pong_Ball_h
#define Pong_Ball_h

#include <iostream>
#include "Ball.h"
#include "Palette.h"

#define MapSize 84
#define Wall '#'
#define BallObject '@'

using namespace std;

class Ball {
public:
    
    Ball();
    
    // incaplsuation
    int Get_pos_x();
    int Get_pos_y();
    int Get_speed();
    
    void Set_pos_x(int pos_x);
    void Set_pos_y(int pos_y);
    void Set_speed(int speed);
    // end incapsulation
    
    void increaseHeight();
    void decreaseHeight();
    void moveLeft();
    void moveRight();
    void BallStatus(bool h);
    void BallDirection(bool h);
    
    bool collisionGoodWall();
    bool collisionBadWall();
    
private:
    
    int pos_x;
    int pos_y;
    int speed;
    
};

void Ball::BallStatus(bool h)
{
    if (h == 0) {
        decreaseHeight();
    } else {
        increaseHeight();
    }
}

void Ball::BallDirection(bool h)
{
    if (h == 0) {
        moveLeft();
    } else {
        moveRight();
    }
}

bool Ball::collisionGoodWall()
{
    if (pos_x == -1) {
        return 1;
    } else if (pos_x == (MapSize / 2) - 2) {
        return 1;
    }
    return 0;
}

bool Ball::collisionBadWall()
{
    if (pos_y == 0) {
        return 1;
    } else if (pos_y == MapSize - 2) {
        return 1;
    }
    return 0;
}

void Ball::increaseHeight()
{
    pos_x--;
}

void Ball::decreaseHeight()
{
    pos_x++;
}

void Ball::moveLeft()
{
    pos_y--;
}

void Ball::moveRight()
{
    pos_y++;
}

// ***********  Get incapsulated variables **************

int Ball::Get_pos_x()
{
    return pos_x;
}

int Ball::Get_pos_y()
{
    return pos_y;
}

int Ball::Get_speed()
{
    return speed;
}

//************  End *****************


//************  Set incapsulated variables ***************

void Ball::Set_pos_x(int pos_x)
{
    this -> pos_x = pos_x;
}

void Ball::Set_pos_y(int pos_y)
{
    this -> pos_y = pos_y;
}

void Ball::Set_speed(int speed)
{
    this -> speed = speed;
}

//************  End *****************


//**********  Constructor *************

Ball::Ball()
{
    pos_x = 21;
    pos_y = 42;
    speed = 2000;
}

//********** End Constructor **********
#endif







