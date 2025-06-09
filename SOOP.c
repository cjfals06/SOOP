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

    Sleep(2500);
    system("cls");

    int y = 0;
    int u = 2;
    int m = 3;
    int cp = 0;
    int prev_pos = -1;
    int toy = 0, laser = 0;
    int so = 0, tower = 0;
    int scratcher_set = 0;
    int tower_set = 0;

    Position cat_rc = { ROOM_WIDTH / 2, ROOM_HEIGHT / 2 };
    Position sp = { -1, -1 };
    Position tp = { -1, -1 };

    while (1) {

        printf("============== 현재 상태 ==============\n");
        printf("현재까지 만든 수프: %d개\n", y);
        printf("CP: %d 포인트\n", cp);
        printf("%s 기분(0~3): %d\n", h, m);
        switch (m) {
        case 0: printf("기분이 매우 나쁩니다.\n"); break;
        case 1: printf("심심해합니다.\n"); break;
        case 2: printf("식빵을 굽습니다.\n"); break;
        case 3: printf("골골송을 부릅니다.\n"); break;
        }
        printf("집사와의 관계(0~4): %d\n", u);
        switch (u) {
        case 0: printf("곁에 오는 것조차 싫어합니다.\n"); break;
        case 1: printf("간식 자판기 취급입니다.\n"); break;
        case 2: printf("그럭저럭 쓸 만한 집사입니다.\n"); break;
        case 3: printf("훌륭한 집사로 인정받고 있습니다.\n"); break;
        case 4: printf("집사 껌딱지입니다.\n"); break;
        }
        printf("========================================\n");

        int d = rand() % 6 + 1;
        int L = 6 - u;

        printf("6 - %d = 주사위 눈이 %d이하이면 그냥 기분이 나빠집니다.\n", u, L);
        printf("주사위를 굴립니다. 또르르...\n");
        printf("%d(이)가 나왔습니다.\n", d);

        if (d <= L) {
            if (m > 0) {
                printf("%s의 기분이 나빠집니다: %d -> %d\n", h, m, m - 1);
                m--;
            }
            else {
                printf("%s의 기분은 이미 최악입니다.\n", h);
            }
        }
        else {
            printf("%s의 기분은 변하지 않았습니다.\n", h);
        }

        int sel;
        int feed = 1, scratch = -1, point = -1;
        int op = 2;

        printf("\n어떤 상호작용을 하시겠습니까?\n");
        printf("0. 아무것도 하지 않음\n");
        printf("1. 긁어 주기\n");

        if (toy) {
            printf("%d. 장난감 쥐로 놀아 주기\n", op);
            scratch = op++;
        }
        if (laser) {
            printf("%d. 레이저 포인터로 놀아 주기\n", op);
            point = op++;
        }

        printf(">> ");
        scanf_s("%d", &sel);

        if (sel == 0) {
            if (m > 0) {
                m--;
                printf("%s의 기분이 나빠졌습니다: %d -> %d\n", h, m + 1, m);
            }
            if (d <= 5 && u > 0) {
                u--;
                printf("친밀도가 감소합니다: %d\n", u);
            }
        }
        else if (sel == feed) {
            printf("%s의 기분은 그대로입니다: %d\n", h, m);
            if (d >= 5 && u < 4) {
                u++;
                printf("친밀도가 증가합니다: %d\n", u);
            }
        }
        else if (sel == scratch) {
            printf("장난감 쥐로 %s랑 놀아 주었습니다.\n", h);
            if (m < 3) m++;
            if (d >= 4 && u < 4) {
                u++;
                printf("친밀도가 증가합니다: %d\n", u);
            }
        }
        else if (sel == point) {
            printf("레이저 포인터로 %s랑 신나게 놀아 주었습니다.\n", h);
            m += (m <= 1) ? 2 : (3 - m);
            if (d >= 2 && u < 4) {
                u++;
                printf("친밀도가 증가합니다: %d\n", u);
            }
        }

        int cp_a = (m > 0 ? m - 1 : 0) + u;
        cp += cp_a;
        printf("\n%s의 기분과 친밀도에 따라 CP %d 포인트가 생산되었습니다. 현재 CP: %d\n", h, cp_a, cp);

        if (so && !scratcher_set) {
            sp = random_position();
            scratcher_set = 1;
        }
        if (tower && !tower_set) {
            tp = random_position();
            tower_set = 1;
        }