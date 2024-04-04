#include <ncurses.h>
#include <stdlib.h>
#include "../gameGlobal.h"


int screenSetUp();

int main(int argc, char* argv[]){
    int ch;
    screenSetUp();

    mapStart();


    while ((ch = getch()) != 'q'){

    }
    endwin();


    return 0;
}

int screenSetUp(){
    initscr();
    printw("Hetefe");
    noecho();

    refresh();
    return 0;
} //cc -o test-main test-main.c -lncurses

//cc -o test test.c -lncurses
//gcc -g -o test test.c -lncurses