#include "stdlib.h"
#include <iostream>
#include <Board.h>
#include "Line.h"
#include "Display.h"

int board[16];


Board::Board(void) {
    srand(time(NULL));
    for (int i = 0; i < 16; i++) {
        board[i] = 0;

    }

}
Board::~Board(){}

void Board::add_random(void){
    bool done = false;

    while (not done) {
        int place = rand()%16;
        if (board[place] == 0) {
            done = true;
            if ((float) rand()/RAND_MAX < 0.9) {
                board[place] = 1;
            }
            else {
                board[place] = 2;
            }
        }
    }
}

void Board::display(int status) {
    Display display(board, status);
    display.backgroundClear();
    display.printBoard();
}

int Board::checker(void) { 
    //check the game status :
    //0 : continue
    //1 : win
    //2 : lose
    for (int i = 0; i < 16; i++){
        if (board[i] == 10) { //looking for a win
            return 1;
        }
    }
    return 0;
}

bool Board::move_up(void){
    bool has_changed = false;
    for(int j = 0; j < 4; j++){
        Line line(board+j, board+j+4, board+j+8, board+j+12);
        bool result  = line.evolve();
        has_changed = (has_changed || result);
    }
    return has_changed; 
}

bool Board::move_down(void){
    bool has_changed = false;
    for(int j = 0; j < 4; j++){
        Line line(board+j+12, board+j+8, board+j+4, board+j);
        bool result = line.evolve();   
        has_changed = (has_changed || result);                 
    }
    return has_changed;
}

bool Board::move_right(void){
    bool has_changed = false;
    for(int i = 0; i < 4; i++){
        Line line(board+4*i+3, board+4*i+2, board+4*i+1, board+4*i);
        bool result = line.evolve();
        has_changed = (has_changed || result);
    }
    return has_changed;
}


bool Board::move_left(void){
    bool has_changed = false;
    for(int i = 0; i < 4; i++){
        Line line(board+4*i, board+1+4*i, board+2+4*i, board+3+4*i);
        bool result = line.evolve();
        has_changed = (has_changed || result);
    }
    return has_changed;
}
