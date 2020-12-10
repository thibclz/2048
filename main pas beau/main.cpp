#include "stdlib.h"
#include <iostream>
#include "sys/ioctl.h"
#include "termios.h"
#include "stdio.h"
#include "time.h"

/* Afin d'éviter d'avoir à gerer le probleme d'affichage, les scores (habituellement 2, 4, 8, 16,...) seront affichés selon la puissance
de 2 correspondante (2->1, 4->2, etc) et le score cible etant 2048 -> 10 marque la victoire, on prendra aussi la convention à -> 0 */



class Display //working
{

    private:

    int bg[36];
    const char* cmd_clear="clear";
    int status;
    public :

    Display(int* board, int stat) {
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
    ~Display(){};




    void backgroundClear(void){
        int out = system( cmd_clear);
        if( out != 0){
            std::cerr << "clear command failed" << std::endl;
            exit(1);
        }
    }

    void printBoard(void){
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
};


class Line  //working
{   public :
    int* line[4];

    Line(int* a, int* b, int* c, int* d) {
        line[0] = a;
        line[1] = b;
        line[2] = c;
        line[3] = d;
    }

    ~Line() {}

    bool evolve(void) {
        bool has_changed = false;

        for  (int i = 0; i < 4; i++) {
            if (*(line[i]) != 0) {
                for (int j = i+1; j<4; j++) {
                    if (*(line[j]) == *(line[i])){
                        *(line[i]) = *(line[i]) + 1;
                        *(line[j]) = 0;
                        has_changed = true;
                        j = 4;
                    }
                    else if (*(line[j]) != 0) {
                        j = 4;
                    }
                }
            }
        }
        for (int i = 0; i <= 3; i++) {
            if (*(line[i]) == 0) {
                for (int j = i+1; j<4; j++) {
                    if (*(line[j]) != 0) {
                        *(line[i]) = *(line[j]);
                        *(line[j]) = 0;
                        has_changed = true;
                        j = 4;
    

                    }
                }
            }
        }
        return has_changed;
    }



    void show(void) {
        std::cout << *line[0] << *line[1] << *line[2] << *line[3] << std::endl;
    }

    int elt(int indice) {
        return *(line[indice]);
    }
};

class Board {

public :
    int board[16];


    Board(void) {
        
        for (int i = 0; i < 16; i++) {
            board[i] = 0;

        }

    }
    ~Board(){}

    void add_random(void){
        bool done = false;
        srand(time(NULL));

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

    void display(int status) {
        Display display(board, status);
        display.backgroundClear();
        display.printBoard();
    }

    int checker(void) { 
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

    bool move_up(void){
        bool has_changed = false;
        for(int j = 0; j < 4; j++){
            Line line(board+j, board+j+4, board+j+8, board+j+12);
            bool result  = line.evolve();
            has_changed = (has_changed || result);
        }
        return has_changed; 
    }

    bool move_down(void){
        bool has_changed = false;
        for(int j = 0; j < 4; j++){
            Line line(board+j+12, board+j+8, board+j+4, board+j);
            bool result = line.evolve();   
            has_changed = (has_changed || result);                 
        }
        return has_changed;
    }

    bool move_right(void){
        bool has_changed = false;
        for(int i = 0; i < 4; i++){
            Line line(board+4*i+3, board+4*i+2, board+4*i+1, board+4*i);
            bool result = line.evolve();
            has_changed = (has_changed || result);
        }
        return has_changed;
    }
    

    bool move_left(void){
        bool has_changed = false;
        for(int i = 0; i < 4; i++){
            Line line(board+4*i, board+1+4*i, board+2+4*i, board+3+4*i);
            bool result = line.evolve();
            has_changed = (has_changed || result);
        }
        return has_changed;
    }

};


// Key tester
namespace internal {

static const int STDIN=0;
static bool initialized = false;
 

int keyEvent(){
    if( !initialized){
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }
    int bytesWaiting;
    //int bytesWaiting;                                                                                                                                                        
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

void frameSleep(const int& ms){
    clock_t end;
    end = clock() + ms * CLOCKS_PER_SEC/1000;
    while( clock() < end){
        // wait 
    }
}

}



int main(){

    //test gauche gauche haut

    // int board[16] = 
    // {0,1,1,2,
    // 0,1,1,2,
    // 0,0,0,0,
    // 0,0,0,0};


    // {
    // for(int i = 0; i < 4; i++){
    //         Line line(board+4*i, board+1+4*i, board+2+4*i, board+3+4*i);
    //         line.evolve();}
    // Display display(board, 0);
    // display.printBoard();
    // }
    // {
    // for(int i = 0; i < 4; i++){
    //         Line line(board+4*i, board+1+4*i, board+2+4*i, board+3+4*i);
    //         line.evolve();}
    // Display display(board, 0);
    // display.printBoard();
    // }
    // {
    // for(int j = 0; j < 4; j++){
    //         Line line(board+j, board+j+4, board+j+8, board+j+12);
    //         line.evolve();}
    // Display display(board, 0);
    // display.printBoard();
    // }



//code effectif


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
            std::cout << has_changed << std::endl;
            
        }   
    }
    return 0;
}