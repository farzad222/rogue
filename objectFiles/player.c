#include <ncurses.h>
#include <stdlib.h>
#include "../gameGlobal.h"

Player *playerSetUp(){
    Player *newPlayer = malloc(sizeof(Player));

    newPlayer->xPos = 14;
    newPlayer->yPos = 14;
    newPlayer->health = 20;

    mvprintw(newPlayer->yPos, newPlayer->xPos, "&");

    refresh();
    return newPlayer;
}