#pragma once
#include "stdlib.h"
#include <iostream>

#include "Line.h"
#include "Display.h"

class Board{

    
    public :
    int bg[16];

    Board();
    ~Board();
    void add_random();
    void display(int status);
    int checker();

    bool move_up();
    bool move_down();
    bool move_right();
    bool move_left();
};
