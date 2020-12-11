#include <iostream>

#include <Line.h>

int* line[4];

Line::Line(int* a, int* b, int* c, int* d) {
    line[0] = a;
    line[1] = b;
    line[2] = c;
    line[3] = d;
}

Line::~Line() {}

bool Line::evolve(void) {
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



void Line::show(void) {
    std::cout << *line[0] << *line[1] << *line[2] << *line[3] << std::endl;
}

int Line::elt(int indice) {
    return *(line[indice]);
}
