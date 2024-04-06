#include <ncurses.h>
#include <stdlib.h>
#include "../gameGlobal.h"


int screenSetUp();

int main(int argc, char* argv[]){
    int ch;
    screenSetUp();

    //mapStart();
    int n = 0;

    TRoom new_room;
    new_room.room_id = n;
    n++;
    node *dungeon_tracker = roomSetUp(new_room);
    roomGenerate(&dungeon_tracker);

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
// NIGGER SCARAB
// ./test-main