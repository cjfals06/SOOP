#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#define ROOM_WIDTH 15
#define ROOM_HEIGHT 4
#define HME_POS 1
#define BWL_POS (ROOM_WIDTH - 2)

typedef struct {
    int x;
    int y;
} Position;

void draw_room(Position cat, int has_scratcher, Position scratcher, int has_tower, Position tower) {
    for (int y = 0; y < ROOM_HEIGHT; y++) {
        for (int x = 0; x < ROOM_WIDTH; x++) {
        }

