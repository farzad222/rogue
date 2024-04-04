#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../gameGlobal.h"

#define LEFT_WALL   3
#define TOP_WALL    0
#define RIGHT_WALL  1
#define BOTTOM_WALL 2

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

void removeFirst(node **head){
    node *temp = (*head)->next;
    free(*head);
    *head = temp;
}

void removeAll(node **head){
    while(*head){
        removeFirst(head);
    }
}

void mapStart(){ // default starting room
    node *r = malloc(sizeof(node));
    //node *r = roomSetUp(room);
    r->room.width = 15;
    r->room.height = 6;
    r->room.p1.x = 15;
    r->room.p1.y = 5;

    r->room.p2.x = -15;
    r->room.p2.y = 5;

    r->room.p3.x = -15;
    r->room.p3.y = -5;

    r->room.p4.x = 15;
    r->room.p4.y = -5;

    r->room.room_id = 0;

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
void roomGenerate(node *roomSetUp, node **head){
    node *r = malloc(sizeof(node));
    //node *r = roomSetUp(room);

    int width_max = fmax(abs(r->room.p3.x), abs(r->room.p4.x));
    int height_max = fmax(abs(r->room.p3.y), abs(r->room.p2.y));

    char (*pre_load_room)[height_max] = calloc(width_max, sizeof(*pre_load_room));
    if (pre_load_room == NULL){
        printf("malloc failed\n");
        exit(EXIT_FAILURE);
    }

    /*
    char **pre_load_room = (char**) calloc((height_max*width_max), sizeof(char*));
    if (pre_load_room == NULL){
        printf("malloc failed\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<width_max; i++){
        pre_load_room[i] = (char *)calloc((height_max), sizeof(char));
        if (pre_load_room[i] == NULL){
            printf("malloc failed\n");
            exit(EXIT_FAILURE);
        }
    }
    */

    if((*head)->next == NULL){
        r->room.width = 15;
        r->room.height = 6;
        r->room.p1.x = 15;
        r->room.p1.y = 5;

        r->room.p2.x = -15;
        r->room.p2.y = 5;

        r->room.p3.x = -15;
        r->room.p3.y = -5;

        r->room.p4.x = 15;
        r->room.p4.y = -5;

        r->room.num_doors = rand() % 4;

        //doorGenerate();
    }

        

    else{
        int gen_width = rand() % 15;
        int gen_height = rand() % 15;
        r->room.width = gen_width;
        r->room.height = gen_height;
        r->room.num_doors = rand() % 4;

        /*
        doorGenerate();
        
        for(int idx=0; idx<r->room.num_doors; idx++){
            switch(r->room.doors[idx].face)
            {



            }
        }
        */
        r->room.p1.x = gen_width;
        r->room.p1.y = gen_height;

        r->room.p2.x = -gen_width;
        r->room.p2.y = gen_height;

        r->room.p3.x = -gen_width;
        r->room.p3.y = -gen_height;

        r->room.p4.x = gen_width;
        r->room.p4.y = -gen_height;

        

    }
        for(int index_w = 0; index_w<width_max; index_w++){ // builds the width first
            for(int index_h = 0; index_h<height_max; index_h++){
                if(((index_w == 0 || index_w == width_max)  && (index_h != r->room.p3.y || index_h != 0))){
                    pre_load_room[index_w][index_h] = '|';
                }
                else if(index_h == 0 || index_h == height_max){
                    pre_load_room[index_w][index_h] = '-';
                }
                else{
                    pre_load_room[index_w][index_h] = '.';
                }
            }
        }
        /*
        while(r->room.doors){ // iters through doors to place all of them down
            pre_load_room[r->room.doors.x][r->room.doors.y] = "#";
        }
        */
        for(int index_w = 0; index_w<width_max; index_w++){ // prints out what we created
            for(int index_h = 0; index_h<height_max; index_h++){
                char value = pre_load_room[index_w][index_h];
                mvprintw(index_w, index_h, "%c", value);
            }
        }


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