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
            if (y == 0 || y == ROOM_HEIGHT - 1) {
                printf("#");
            }
            else if (x == 0 || x == ROOM_WIDTH - 1) {
                printf("#");
            }
            else if (cat.x == x && cat.y == y) {
                printf("C");
            }
            else if (has_scratcher && scratcher.x == x && scratcher.y == y) {
                printf("S");
            }
            else if (has_tower && tower.x == x && tower.y == y) {
                printf("T");
            }
            else if (x == HME_POS && y == 1) {
                printf("H");
            }
            else if (x == BWL_POS && y == 1) {
                printf("B");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

Position random_position() {
    Position p;
    p.x = rand() % (ROOM_WIDTH - 2) + 1;
    p.y = rand() % (ROOM_HEIGHT - 2) + 1;
    return p;
}

int main(void) {
    srand((unsigned int)time(NULL));
    char h[100];
    printf("****야옹이와 수프****\n");
    printf("야옹이의 이름을 지어주세요: ");
    scanf_s("%s", h, sizeof(h));
    printf("야옹이의 이름은 %s입니다.", h);