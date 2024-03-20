#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME_LENGTH 20

// Define the room struct
typedef struct room {
    char name[MAX_NAME_LENGTH];
    int nb_parent;
    struct room **room_next;
    bool if_obstacles;
    bool if_already_browsed;
    int cost;
    bool if_start;
    bool if_end;
} room;

typedef struct robot {
    char name[MAX_NAME_LENGTH];
    struct room *current_room;
} robot;

void my_putstr(const char *str) {
    printf("%s", str);
}

// Function to initialize a room
room *create_room(const char *name, bool if_start, bool if_end) {
    room *new_room = malloc(sizeof(room));
    if (new_room == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strncpy(new_room->name, name, MAX_NAME_LENGTH);
    new_room->if_start = if_start;
    new_room->if_end = if_end;
    // Other initialization goes here
    return new_room;
}

// Function to connect rooms
void connect_rooms(room *room1, room *room2) {
    room1->room_next = realloc(room1->room_next, sizeof(room *) * (room1->nb_parent + 1));
    if (room1->room_next == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    room1->room_next[room1->nb_parent++] = room2;
}

// Breadth-first search algorithm
room *bfs(room *start) {
    room *queue[1000]; // Queue to store rooms to be visited
    int front = 0, rear = -1; // Front and rear pointers for the queue
    room *current_room = start;

    current_room->if_already_browsed = true;
    queue[++rear] = current_room;

    while (front <= rear) {
        current_room = queue[front++];
        if (current_room->if_end) {
            return current_room; // Found the end room
        }
        // Enqueue adjacent rooms
        for (int i = 0; i < current_room->nb_parent; ++i) {
            room *next_room = current_room->room_next[i];
            if (!next_room->if_already_browsed && !next_room->if_obstacles) {
                next_room->if_already_browsed = true;
                queue[++rear] = next_room;
            }
        }
    }
    return NULL; // End room not found
}

// Move robots according to path found by BFS
void move_robots(robot *rb, int nb_of_robot, room *end) {
    for (int i = 0; i < nb_of_robot; ++i) {
        if (!rb[i].current_room->if_end) {
            room *room_next = bfs(rb[i].current_room);
            if (room_next != NULL) {
                rb[i].current_room = room_next;
            }
        }
    }
}

int main() {
    // Create rooms
    room *start = create_room("Start", true, false);
    room *end = create_room("End", false, true);
    room *room1 = create_room("Room1", false, false);
    room *room2 = create_room("Room2", false, false);
    room *room3 = create_room("Room3", false, false);

    // Connect rooms
    connect_rooms(start, room1);
    connect_rooms(room1, room2);
    connect_rooms(room1, room3);
    connect_rooms(room2, end);
    connect_rooms(room3, end);

    // Initialize robots
    robot robots[2];
    strcpy(robots[0].name, "Robot1");
    robots[0].current_room = start;
    strcpy(robots[1].name, "Robot2");
    robots[1].current_room = start;

    // Move robots
    move_robots(robots, 2, end);

    // Print robot positions
    for (int i = 0; i < 2; ++i) {
        printf("%s-%s\n", robots[i].name, robots[i].current_room->name);
    }

    // Free memory
    free(start);
    free(end);
    free(room1);
    free(room2);
    free(room3);

    return 0;
}
