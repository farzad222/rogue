#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../gameGlobal.h"

#define LEFT_WALL   3
#define TOP_WALL    0
#define RIGHT_WALL  1
#define BOTTOM_WALL 2

double max(double x, double y){
    if(x>y) return x;
    return y;
}

node *roomSetUp(TRoom room){
    node *newRoom = malloc(sizeof(node));
    if(newRoom == NULL){
		perror("Malloc failure.");
		exit(EXIT_FAILURE);
  	}

    newRoom->room = room;
    newRoom->next = NULL;
    return newRoom;
}

void addFirst(node **head, node *roomSetUp){
    roomSetUp->next = *head;
    *head = roomSetUp;
}

void removeAll(node **head){
    while(*head){
        node *temp = (*head)->next;
        free(*head);
        *head = temp;
    }
}

void mapStart(){ // default starting room
    TRoom r;

    r.width = 15;
    r.height = 6;
    r.p1.x = 15;
    r.p1.y = 5;

    r.p2.x = -15;
    r.p2.y = 5;

    r.p3.x = -15;
    r.p3.y = -5;

    r.p4.x = 15;
    r.p4.y = -5;

    r.room_id = 0;

    roomSetUp(r);

    mvprintw(5, 0, "- - - - - - - -");
    mvprintw(4, 0, "| . . . . . . |");
    mvprintw(3, 0, "| . . . . . . |");
    mvprintw(2, 0, "| . . . . . . |");
    mvprintw(1, 0, "| . . . . . . |");
    mvprintw(0, 0, "- - - - - - - -");
    refresh();
}
/*
void doorGenerate(){
    int *already_door = (int *)calloc(r->room.num_doors, sizeof(int));
        if(already_door == NULL){
            perror("calloc failed");
            exit(EXIT_FAILURE);
        }

        for(int idx=0; idx<r->room.num_doors; idx++){
            int random_wall_side = rand() % 4;
            switch(random_wall_side)
            {
                case 0:
                    r->room.doors[idx].x = rand() % r->room.width;
                    r->room.doors[idx].y = rand() % r->room.height;

                    int index = hash(idx(r->room.doors[idx].x, r->room.doors[idx].y));
                    if(already_door[index] != 0){
                        already_door[index] += 1;
                        r->room.doors[idx].face = LEFT_WALL;
                    }
                    break;
                case 1:
                    r->room.doors[idx].x = rand() % r->room.width;
                    r->room.doors[idx].y = rand() % r->room.height;

                    int index = hash(idx(r->room.doors[idx].x, r->room.doors[idx].y));
                    if(already_door[index] != 0){
                        already_door[index] += 1;
                        r->room.doors[idx].face = LEFT_WALL;
                    }
                    break;
                case 2:
                    r->room.doors[idx].x = rand() % r->room.width;
                    r->room.doors[idx].y = rand() % r->room.height;

                    int index = hash(idx(r->room.doors[idx].x, r->room.doors[idx].y));
                    if(already_door[index] != 0){
                        already_door[index] += 1;
                        r->room.doors[idx].face = LEFT_WALL;
                    }
                    break;
                case 3:
                    r->room.doors[idx].x = rand() % r->room.width;
                    r->room.doors[idx].y = rand() % r->room.height;

                    int index = hash(idx(r->room.doors[idx].x, r->room.doors[idx].y));
                    if(already_door[index] != 0){
                        already_door[index] += 1;
                        r->room.doors[idx].face = LEFT_WALL;
                    }
                    break;
            }
        }
        free(already_door);
}
*/
void roomGenerate(node **head){
    TRoom r;

    if((*head)->next == NULL){
        r.width = 15;
        r.height = 6;
        r.p1.x = 15;
        r.p1.y = 5;

        r.p2.x = -15;
        r.p2.y = 5;

        r.p3.x = -15;
        r.p3.y = -5;

        r.p4.x = 15;
        r.p4.y = -5;

        r.num_doors = rand() % 4;

        //doorGenerate();
    }
    else{
        int gen_width = rand() % 15;
        int gen_height = rand() % 15;
        r.width = gen_width;
        r.height = gen_height;
        r.num_doors = rand() % 4;
        /*
        doorGenerate();
        
        for(int idx=0; idx<r->room.num_doors; idx++){
            switch(r->room.doors[idx].face)
            {



            }
        }
        */
        r.p1.x = gen_width;
        r.p1.y = gen_height;

        r.p2.x = -gen_width;
        r.p2.y = gen_height;

        r.p3.x = -gen_width;
        r.p3.y = -gen_height;

        r.p4.x = gen_width;
        r.p4.y = -gen_height;
    }

    int width_max = max(abs(r.p3.x), abs(r.p4.x));
    int height_max = max(abs(r.p3.y), abs(r.p2.y));

    char (*pre_load_room)[height_max] = calloc(width_max, sizeof(*pre_load_room));
    if (pre_load_room == NULL){
        printf("malloc failed\n");
        exit(EXIT_FAILURE);
    }

        for(int index_w = 0; index_w<width_max; index_w++){ // builds the width first
            for(int index_h = 0; index_h<height_max; index_h++){

                if((index_w == 0 || index_w == width_max)  && 
                (((index_h != r.p3.y && index_h != r.p3.x)) ||
                (index_h != r.p1.y && index_h != r.p1.x) ||
                (index_h != r.p2.y && index_h != r.p2.x) ||
                (index_h != r.p4.y && index_h != r.p4.x))){
                    pre_load_room[index_w][index_h] = '|';
                }
                /*else if(index_h == 0 || index_h == height_max){
                    pre_load_room[index_w][index_h] = '-';
                }*/
                /*else{
                    pre_load_room[index_w][index_h] = '.';
                }*/
                
            }
        }
        /*
        while(r.doors){ // iters through doors to place all of them down
            pre_load_room[r.doors.x][r.doors.y] = "#";
        }
        */
        for(int index_w = 0; index_w<width_max; index_w++){ // prints out what we created
            for(int index_h = 0; index_h<height_max; index_h++){
                char value = pre_load_room[index_w][index_h];
                mvprintw(index_h, index_w, "%c", value);
            }
        }

    addFirst(head, roomSetUp(r));
    refresh();

    /*
    for (int i = 0; i < width_max; i++)
    {
        free(pre_load_room[i]);
    }
    */
    free(pre_load_room);
}

//./test-main