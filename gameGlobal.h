#ifndef GAMEGLOBAL_H
#define GAMEGLOBAL_H


typedef struct Player{
    int xPos;
    int yPos;
    int health;
}Player;
Player *playerSetUp();


typedef struct Cordinates // coordinates of the doors and edges in a room
{
    int x, y;
    int face;
}TCoordinates;

typedef struct Room{
    TCoordinates doors; // door cords
    TCoordinates p1, p2, p3, p4; // corners of room
    int width, height; 
    int room_id;
    int num_doors;
    int token; // % chance for special/unique room
}TRoom;

typedef struct node_tag // a linked list to keep track of room and their door locations
{   
    TRoom room;
    struct node_tag *next;
}   node;
node *roomSetUp(TRoom room);


unsigned hash(unsigned a);
int idx(int x, int y);
void mapStart();
void roomGenerate(node *roomSetUp, node **head);



#endif