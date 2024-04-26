#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define MAP_WIDTH 80
#define MAP_HEIGHT 20
#define GROUND_HEIGHT 2
#define JUMP_HEIGHT 7
#define HURDLE_CHAR 'A'
#define GROUND_CHAR '_'
#define PLAYER_CHAR '*'
#define DELAY_MS 50

// ���� ����
int playerX = 18;
int jump = 0;
int soc = 0; // ���ھ� ���� �̸� ����

// ���� �ʱ�ȭ �� ��Ģ ����
void rule() {
    printf("\033[0m");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("                                    ���� ����: �����̽��ٸ� ���� ����� ��������!\n\n");
    printf("                                         ������ �����Ϸ��� �ƹ� Ű�� ��������...");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    getchar();
}

// �� �׸���
void drawMap(int hurdlePositions[], int numHurdles) {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    for (int i = 0; i < MAP_HEIGHT; i++) {
        cursorPosition.Y = i;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == MAP_HEIGHT - GROUND_HEIGHT - jump && j == playerX) { printf("%c", PLAYER_CHAR); }
            else {
                int isHurdle = 0;
                for (int k = 0; k < numHurdles; k++) {
                    if (i == MAP_HEIGHT - GROUND_HEIGHT && j == hurdlePositions[k]) {
                        printf("%c", HURDLE_CHAR);
                        isHurdle = 1;
                        break;
                    }
                }
                if (!isHurdle) {
                    if (i == MAP_HEIGHT - GROUND_HEIGHT) { printf("%c", GROUND_CHAR); }
                    else { printf(" "); }
                }
            }
        }
        printf("\n");
    }
    printf("                          Score: %d\n", soc); // ���ھ� ���� �̸� ����
}

// ���� ���� ������Ʈ
void updateGame(int hurdlePositions[], int* numHurdles) {
    printf("\033[0m");
    if (_kbhit()) {
        char input = _getch();
        if (input == ' ' && jump == 0) {
            jump = JUMP_HEIGHT;
        }
    }
    if (jump > 0) { jump--; }

    // �÷��̾ ȭ���� ����� �ٽ� ����
    if (playerX == MAP_WIDTH) { playerX = 0; }

    // �� ��� ����
    if (*numHurdles < 5 && rand() % 20 == 0) {
        int lastHurdlePosition = (*numHurdles > 0) ? hurdlePositions[*numHurdles - 1] : MAP_WIDTH;
        if (MAP_WIDTH - lastHurdlePosition >= 8) {
            hurdlePositions[*numHurdles] = MAP_WIDTH - 1;
            (*numHurdles)++;
        }
    }

    // ��� �̵� �� ���ھ� ����
    for (int i = 0; i < *numHurdles; i++) {
        hurdlePositions[i]--;
        if (hurdlePositions[i] == playerX) {
            soc++; // �÷��̾ ����� ������ ���ھ� ����
        }
        if (hurdlePositions[i] < 0) {
            // ����� ȭ���� ����� ����
            for (int j = i; j < *numHurdles - 1; j++) {
                hurdlePositions[j] = hurdlePositions[j + 1];
            }
            (*numHurdles)--;
        }
        // �浹 ����
        if (jump == 0 && hurdlePositions[i] == playerX) {
            printf("\n\n\n");
            printf("                                                       Score: %d\n\n", soc); // ���ھ� ���� �̸� ����
            printf("                                                ����� ������ ���߽��ϴ�!\n");
            printf("\n\n");
            printf("                                            �ٽ� �����Ͻðڽ��ϱ�? ( Y / N ): ");
            char key;
            scanf(" %c", &key);
            if (key != 'Y') { exit(0); }
            else {
                system("cls");
                playerX = 18;
                jump = 0;
                soc = 0; // ���ھ� ���� �̸� ����
                *numHurdles = 1;
                return;
            }
        }
    }

    drawMap(hurdlePositions, *numHurdles);
}

// �� ���� ����
int sheep() { // �Լ� �̸� ����
    srand(time(NULL));
    int hurdlePositions[5] = { 40 };
    int numHurdles = 1;
    rule();

    while (1) {
        drawMap(hurdlePositions, numHurdles);
        updateGame(hurdlePositions, &numHurdles);
        Sleep(DELAY_MS);
    }

    return 0;
}
