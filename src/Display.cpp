#include "stdlib.h"
#include <iostream>

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
