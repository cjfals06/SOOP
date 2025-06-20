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

void sudden_quest(int* cp, int* soup, int* m, const char* name) {
    int cor = rand() % 3 + 1;
    int g;
    printf("\n?? 돌발 퀘스트 발생!! ??\n");
    printf("쥐가 수프를 들고 도망갑니다! ????\n");
    printf("3개의 쥐구멍 중 어디에 숨었을까요?\n");
    printf("1번 / 2번 / 3번 중 선택하세요 >> ");
    scanf_s("%d", &g);

    if (g == cor) {
        int bonus = rand() % 4 + 1;
        printf("정답입니다! 보상으로 쥐가 여태 훔친 재산을 드릴게요!\n");
        printf("두구두구.......     수프 +%d, CP +50 획득!\n", bonus);
        *cp += 50;
        *soup += bonus;
    }
    else {
        printf("틀렸습니다...!\n");
        printf("쥐: ㅋㅋ 그것도 못맞추네  니 수프 맛있다~\n");
        if (*m > 0) {
            printf("%s의 기분이 나빠졌습니다....: %d -> %d\n", name, *m, *m - 1);
            (*m)--;
        }
    }
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

    int turn_count = 0;

    while (1) {
        turn_count++;

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

        printf("\n이동\n");
        Position* target = NULL;

        if (m == 0) {
            printf("기분이 매우 나쁜 %s(은)는 집으로 향합니다.\n", h);
            target = &(Position) { HME_POS, 1 };
        }
        else if (m == 1) {
            if (so || tower) {
                Position* obj1 = so ? &sp : NULL;
                Position* obj2 = tower ? &tp : NULL;
                if (obj1 && !obj2) target = obj1;
                else if (!obj1 && obj2) target = obj2;
                else {
                    int dist1 = abs(cat_rc.x - obj1->x) + abs(cat_rc.y - obj1->y);
                    int dist2 = abs(cat_rc.x - obj2->x) + abs(cat_rc.y - obj2->y);
                    target = (dist1 <= dist2) ? obj1 : obj2;
                }
                printf("%s(은)는 심심해서 놀이기구 쪽으로 이동합니다.\n", h);
            }
            else {
                printf("놀 거리가 없어서 기분이 매우 나빠집니다...\n");
                if (m > 0) m--;
            }
        }
        else if (m == 2) {
            printf("%s(은)는 기분좋게 식빵을 굽고 있습니다.\n", h);
        }
        else if (m == 3) {
            printf("%s(은)는 골골송을 부르며 수프를 만들러 갑니다.\n", h);
            target = &(Position) { BWL_POS, 1 };
        }

        if (target && !(cat_rc.x == target->x && cat_rc.y == target->y)) {
            if (cat_rc.x < target->x) cat_rc.x++;
            else if (cat_rc.x > target->x) cat_rc.x--;
            else if (cat_rc.y < target->y) cat_rc.y++;
            else if (cat_rc.y > target->y) cat_rc.y--;
        }

        printf("\n행동\n");
        int acted = 0;

        if (cat_rc.x == HME_POS && cat_rc.y == 1) {
            if (prev_pos == HME_POS) {
                printf("%s(은)는 집에서 쉬고 있습니다. 기분이 좋아졌습니다!\n", h);
                if (m < 3) { m++; printf("기분: %d -> %d\n", m - 1, m); }
                acted = 1;
            }
            else {
                printf("%s(은)는 이제 집에 도착했습니다.\n", h);
            }
        }
        else if (cat_rc.x == BWL_POS && cat_rc.y == 1) {
            printf("%s(은)는 수프를 만듭니다!\n", h);
            const char* soups[] = { "감자", "양송이", "브로콜리" };
            int soup_type = rand() % 3;
            printf("%s(이)가 %s 수프를 만들었습니다!\n", h, soups[soup_type]);
            y++;
            acted = 1;
        }
        else if (so && cat_rc.y == sp.y) {
            printf("%s(은)는 스크래처를 긁고 놀았습니다.\n", h);
            if (m < 3) { m++; printf("기분이 조금 좋아졌습니다: %d -> %d\n", m - 1, m); }
            acted = 1;
        }
        else if (tower && cat_rc.y == tp.y) {
            printf("%s(은)는 캣타워를 뛰어다닙니다.\n", h);
            if (m < 3) {
                int gain = (m <= 1) ? 2 : (3 - m);
                m += gain;
                printf("기분이 제법 좋아졌습니다: %d -> %d\n", m - gain, m);
            }
            acted = 1;
        }

        if (!acted) {
            printf("%s(은)는 방을 돌아다니고 있습니다.\n", h);
        }

        prev_pos = cat_rc.x;

        draw_room(cat_rc, scratcher_set, sp, tower_set, tp);

        if (turn_count % 3 == 0) {
            sudden_quest(&cp, &y, &m, h);
        }

        while (1) {
            printf("\n상점에서 물건을 살 수 있습니다. 어떤 물건을 구매할까요?\n");
            printf("현재 CP: %d\n", cp);
            printf("0. 아무것도 사지 않는다.\n");
            printf("1. 장난감 쥐: 1 CP%s\n", toy ? " (품절)" : "");
            printf("2. 레이저 포인터: 2 CP%s\n", laser ? " (품절)" : "");
            printf("3. 스크래처: 4 CP%s\n", so ? " (품절)" : "");
            printf("4. 캣 타워: 6 CP%s\n", tower ? " (품절)" : "");
            printf(">> ");

            int c;
            scanf_s("%d", &c);

            if (c == 0) break;
            if (c < 0 || c > 4) {
                printf("잘못된 입력입니다. 다시 입력해주세요.\n");
                continue;
            }

            if (c == 1 && !toy && cp >= 1) {
                toy = 1; cp -= 1;
                printf("장난감 쥐를 구매했습니다. (보유 CP %d 포인트)\n", cp);
                break;
            }
            else if (c == 2 && !laser && cp >= 2) {
                laser = 1; cp -= 2;
                printf("레이저 포인터를 구매했습니다. (보유 CP %d 포인트)\n", cp);
                break;
            }
            else if (c == 3 && !so && cp >= 4) {
                so = 1; cp -= 4;
                do {
                    sp = random_position();
                } while (
                    (sp.x == tp.x && sp.y == tp.y) ||
                    (sp.x == HME_POS && sp.y == 1) ||
                    (sp.x == BWL_POS && sp.y == 1));
                scratcher_set = 1;
                printf("스크래처를 구매했습니다. (보유 CP %d 포인트)\n", cp);
                break;
            }
            else if (c == 4 && !tower && cp >= 6) {
                tower = 1; cp -= 6;
                do {
                    tp = random_position();
                } while (
                    (tp.x == sp.x && tp.y == sp.y) ||
                    (tp.x == HME_POS && tp.y == 1) ||
                    (tp.x == BWL_POS && tp.y == 1));
                tower_set = 1;
                printf("캣 타워를 구매했습니다. (보유 CP %d 포인트)\n", cp);
                break;
            }
            else {
                printf("불가능 다시 선택해주세요.\n");
            }
        }

        Sleep(1500);
        system("cls");
    }

    return 0;
}