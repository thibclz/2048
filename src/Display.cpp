#include "stdlib.h"
#include <iostream>
#include <Display.h>

int bg[36];
int status;

Display::Display(int* board, int stat) {
    status = stat;
    int j = 0;
    for (int i = 0; i < 36; i++){
        if (i< 6 || i >= 30 || i%6 == 0 || i%6 == 5) {
            bg[i] = -1;
        }
        else {
            bg[i] = board[j];
            j++;
        }
    }
}
Display::~Display(){};


void Display::backgroundClear(void){
    std::system("clear");
}

void Display::printBoard(void){
    for( int j=0; j<6; j++){
        for( int i=0; i<6; i++){
            if (bg[i+j*6] == 0 ){
                std::cout << " x ";
            }   
            else if (bg[i+j*6] == -1) {
                std::cout << " # ";
            }
            else{
                std::cout <<" " << bg[i+j*6] << " ";
            }
        }
        std::cout << std::endl;
    }
    if (status == 1) {
        std::cout << "GAGNE" << std::endl;
    }
    else if (status == 2) {
        std::cout << "PERDU" << std::endl;
    }
}
