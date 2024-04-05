/*
** EPITECH PROJECT, 2023
** a_maze_d
** File description:
** a_maze_d
*/

#include "./../a_maze_d.h"


/*typedef struct room {
    char *name;
    int nb_parent;
    struct room *room_next;
    int if_obstacles;
    int if_already_browsed;
    int cost;
    int if_start;
    int if_end;
} room;*/

typedef struct robot {
    char *name;
    room *current_room;
}robot;

void print_f(robot *rb, int nb_of_robot)
{
    for (int i = 0; i < nb_of_robot; ++i) {
        my_putstr(rb[i]->name);
        my_putstr("-");
        my_putstr(rb[i]->current_room->name);
        if (i != nb_of_robot - 1)
            my_putstr("-");
    }
    my_putstr("\n");
}

void move_robot(robot *rb, room *end, int nb_of_robot)
{
    room *room_next;

    for (int i = 0; i < nb_of_robot; ++i) {
        if (!rb[i].current_room->if_end) {
            room_next = path_finding(rb[i].current_room);
            rb[i].current_room = room_next;
        }
    }
    print_f(rb);
}

char *name_f(int i)
{
    //char *a = 
    return "Pi";
}

robot *init_robot_f(int nb, room *start)
{
    robot *rb = malloc(sizeof(robot) * nb);

    for (int i = 0; i <= nb; ++i) {
        rb[i].name = name_f(i + 1);
        rb[i].current_room = start;
    }
    return rb;
}

room *path_finding(room *current_room)
{
    int a = current_room->nb_parent;
    room *r;
    room *m;
    int n = 1000;

    if (a == 1 && !current_room->if_obstacles)
        return current_room->room_next[0];
    for (int i = 0; i <= a; ++i) {
        if (n >=  current_room->room_next[i]->nb_parent) {
            n = current_room->room_next[i]->nb_parent;
            r = current_room->room_next[i];
        }
    }
    return r;
}

void move(room *start, room *end, int nb_of_robot)
{
	robot *rb = init_robot_f(nb_of_robot, start);
    int i = 1;
    my_putstr("#moves");

    while(i){
        move_robot(rb, end);
        i = if_end_f(rb, end);
    }

}