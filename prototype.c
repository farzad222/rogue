#include <ncurses.h>
#include <stdlib.h>

typedef struct Player{
    int xPos;
    int yPos;
    int health;
}Player;

int screenSetUp();
int mapSetUp();
Player *playerSetUp();

int main(){
    Player *user = playerSetUp();
    int ch;
    screenSetUp();

    mapSetUp();


    while ((ch = getch()) != 'q'){

    }
    endwin();

    free(user);
    return 0;
}

int screenSetUp(){
    initscr();
    printw("Hetefe");
    noecho();

    refresh();
    return 0;
} //cc -o prototype prototype.c -lncurses

int mapSetUp(){
    mvprintw(13, 13, "- - - - - - - -");
    mvprintw(14, 13, "| . . . . . . |");
    mvprintw(15, 13, "| . . . . . . |");
    mvprintw(16, 13, "| . . . . . . |");
    mvprintw(17, 13, "| . . . . . . |");
    mvprintw(18, 13, "- - - - - - - -");
    refresh();
    return 0;
}

Player *playerSetUp(){
    Player *newPlayer = malloc(sizeof(Player));

    newPlayer->xPos = 14;
    newPlayer->yPos = 14;
    newPlayer->health = 20;

    mvprintw(newPlayer->yPos, newPlayer->xPos, "&");

    refresh();
    return newPlayer;
}
//cc -o test test.c -lncurses
//gcc -g -o test test.c -lncurses