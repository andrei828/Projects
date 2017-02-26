#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "Map.h"
#include "Ball.h"
#include "Palette.h"

using namespace std;

int main() {
    
    Map Map;
    Ball Ball;
    while (1) {
        Map.Display();
        if (Map.GetEnd() == true) {
            break;
        }
        usleep(40000);
    }
    
}
