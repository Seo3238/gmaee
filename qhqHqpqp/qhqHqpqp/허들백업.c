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

// 전역 변수
int playerX = 18;
int jump = 0;
int soc = 0; // 스코어 변수 이름 변경

// 게임 초기화 및 규칙 설명
void rule() {
    printf("\033[0m");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("                                    게임 설명: 스페이스바를 눌러 허들을 넘으세요!\n\n");
    printf("                                         게임을 시작하려면 아무 키나 누르세요...");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    getchar();
}

// 맵 그리기
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
    printf("                          Score: %d\n", soc); // 스코어 변수 이름 변경
}

// 게임 상태 업데이트
void updateGame(int hurdlePositions[], int* numHurdles) {
    printf("\033[0m");
    if (_kbhit()) {
        char input = _getch();
        if (input == ' ' && jump == 0) {
            jump = JUMP_HEIGHT;
        }
    }
    if (jump > 0) { jump--; }

    // 플레이어가 화면을 벗어나면 다시 시작
    if (playerX == MAP_WIDTH) { playerX = 0; }

    // 새 허들 생성
    if (*numHurdles < 5 && rand() % 20 == 0) {
        int lastHurdlePosition = (*numHurdles > 0) ? hurdlePositions[*numHurdles - 1] : MAP_WIDTH;
        if (MAP_WIDTH - lastHurdlePosition >= 8) {
            hurdlePositions[*numHurdles] = MAP_WIDTH - 1;
            (*numHurdles)++;
        }
    }

    // 허들 이동 및 스코어 증가
    for (int i = 0; i < *numHurdles; i++) {
        hurdlePositions[i]--;
        if (hurdlePositions[i] == playerX) {
            soc++; // 플레이어가 허들을 넘으면 스코어 증가
        }
        if (hurdlePositions[i] < 0) {
            // 허들이 화면을 벗어나면 제거
            for (int j = i; j < *numHurdles - 1; j++) {
                hurdlePositions[j] = hurdlePositions[j + 1];
            }
            (*numHurdles)--;
        }
        // 충돌 감지
        if (jump == 0 && hurdlePositions[i] == playerX) {
            printf("\n\n\n");
            printf("                                                       Score: %d\n\n", soc); // 스코어 변수 이름 변경
            printf("                                                허들을 피하지 못했습니다!\n");
            printf("\n\n");
            printf("                                            다시 실행하시겠습니까? ( Y / N ): ");
            char key;
            scanf(" %c", &key);
            if (key != 'Y') { exit(0); }
            else {
                system("cls");
                playerX = 18;
                jump = 0;
                soc = 0; // 스코어 변수 이름 변경
                *numHurdles = 1;
                return;
            }
        }
    }

    drawMap(hurdlePositions, *numHurdles);
}

// 양 게임 실행
int sheep() { // 함수 이름 변경
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
