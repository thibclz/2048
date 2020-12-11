#include "stdlib.h"
#include <iostream>

#include "stdio.h"
#include "time.h"

#include "internals.h"
#include "Board.h"
#include "Display.h"
#include "Line.h"

/* Afin d'éviter d'avoir à gerer le probleme d'affichage, les scores (habituellement 2, 4, 8, 16,...) seront affichés selon la puissance
de 2 correspondante (2->1, 4->2, etc) et le score cible etant 2048 -> 10 marque la victoire, on prendra aussi la convention à -> 0 */



// Key tester




int main(){

    Board board;
    board.add_random();
    
    board.display(0);

    char key;
    const int lap=200;
    while( true ){
        bool has_changed = false;
        internal::frameSleep(lap);
        if( internal::keyEvent() ){
            std::cin >> key; 
            switch (key) {
                case 'z' :
                    has_changed = board.move_up();
                case 'd' :
                    has_changed = board.move_right();
                case 's' :
                    has_changed = board.move_down();
                case 'q' :
                    has_changed = board.move_left();
                default :
                    break;
            }
            
            if (has_changed) {
                int status = board.checker();
                board.add_random();
                board.display(status);
            }
            else {
                board.display(0);
            }            
        }   
    }
    return 0;
}



//test

// int main(){
//         //test gauche gauche haut

//     int board[16] = 
//     {0,1,1,2,
//     0,1,1,2,
//     0,0,0,0,
//     0,0,0,0};


//     {
//     for(int i = 0; i < 4; i++){
//             Line line(board+4*i, board+1+4*i, board+2+4*i, board+3+4*i);
//             line.evolve();}
//     Display display(board, 0);
//     display.printBoard();
//     }
//     {
//     for(int i = 0; i < 4; i++){
//             Line line(board+4*i, board+1+4*i, board+2+4*i, board+3+4*i);
//             line.evolve();}
//     Display display(board, 0);
//     display.printBoard();
//     }
//     {
//     for(int j = 0; j < 4; j++){
//             Line line(board+j, board+j+4, board+j+8, board+j+12);
//             line.evolve();}
//     Display display(board, 0);
//     display.printBoard();
//     }
// return 0;
// }