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
    printf("****�߿��̿� ����****\n");
    printf("�߿����� �̸��� �����ּ���: ");
    scanf_s("%s", h, sizeof(h));
    printf("�߿����� �̸��� %s�Դϴ�.", h);

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

        printf("============== ���� ���� ==============\n");
        printf("������� ���� ����: %d��\n", y);
        printf("CP: %d ����Ʈ\n", cp);
        printf("%s ���(0~3): %d\n", h, m);
        switch (m) {
        case 0: printf("����� �ſ� ���޴ϴ�.\n"); break;
        case 1: printf("�ɽ����մϴ�.\n"); break;
        case 2: printf("�Ļ��� �����ϴ�.\n"); break;
        case 3: printf("������ �θ��ϴ�.\n"); break;
        }
        printf("������� ����(0~4): %d\n", u);
        switch (u) {
        case 0: printf("�翡 ���� ������ �Ⱦ��մϴ�.\n"); break;
        case 1: printf("���� ���Ǳ� ����Դϴ�.\n"); break;
        case 2: printf("�׷����� �� ���� �����Դϴ�.\n"); break;
        case 3: printf("�Ǹ��� ����� �����ް� �ֽ��ϴ�.\n"); break;
        case 4: printf("���� �������Դϴ�.\n"); break;
        }
        printf("========================================\n");

        int d = rand() % 6 + 1;
        int L = 6 - u;

        printf("6 - %d = �ֻ��� ���� %d�����̸� �׳� ����� �������ϴ�.\n", u, L);
        printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
        printf("%d(��)�� ���Խ��ϴ�.\n", d);

        if (d <= L) {
            if (m > 0) {
                printf("%s�� ����� �������ϴ�: %d -> %d\n", h, m, m - 1);
                m--;
            }
            else {
                printf("%s�� ����� �̹� �־��Դϴ�.\n", h);
            }
        }
        else {
            printf("%s�� ����� ������ �ʾҽ��ϴ�.\n", h);
        }

        int sel;
        int feed = 1, scratch = -1, point = -1;
        int op = 2;

        printf("\n� ��ȣ�ۿ��� �Ͻðڽ��ϱ�?\n");
        printf("0. �ƹ��͵� ���� ����\n");
        printf("1. �ܾ� �ֱ�\n");

        if (toy) {
            printf("%d. �峭�� ��� ��� �ֱ�\n", op);
            scratch = op++;
        }
        if (laser) {
            printf("%d. ������ �����ͷ� ��� �ֱ�\n", op);
            point = op++;
        }

        printf(">> ");
        scanf_s("%d", &sel);

        if (sel == 0) {
            if (m > 0) {
                m--;
                printf("%s�� ����� ���������ϴ�: %d -> %d\n", h, m + 1, m);
            }
            if (d <= 5 && u > 0) {
                u--;
                printf("ģ�е��� �����մϴ�: %d\n", u);
            }
        }
        else if (sel == feed) {
            printf("%s�� ����� �״���Դϴ�: %d\n", h, m);
            if (d >= 5 && u < 4) {
                u++;
                printf("ģ�е��� �����մϴ�: %d\n", u);
            }
        }
        else if (sel == scratch) {
            printf("�峭�� ��� %s�� ��� �־����ϴ�.\n", h);
            if (m < 3) m++;
            if (d >= 4 && u < 4) {
                u++;
                printf("ģ�е��� �����մϴ�: %d\n", u);
            }
        }
        else if (sel == point) {
            printf("������ �����ͷ� %s�� �ų��� ��� �־����ϴ�.\n", h);
            m += (m <= 1) ? 2 : (3 - m);
            if (d >= 2 && u < 4) {
                u++;
                printf("ģ�е��� �����մϴ�: %d\n", u);
            }
        }

        int cp_a = (m > 0 ? m - 1 : 0) + u;
        cp += cp_a;
        printf("\n%s�� ��а� ģ�е��� ���� CP %d ����Ʈ�� ����Ǿ����ϴ�. ���� CP: %d\n", h, cp_a, cp);

        if (so && !scratcher_set) {
            sp = random_position();
            scratcher_set = 1;
        }
        if (tower && !tower_set) {
            tp = random_position();
            tower_set = 1;
        }