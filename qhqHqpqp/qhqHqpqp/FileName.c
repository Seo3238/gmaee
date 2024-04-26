#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define DINO_X 0
#define DINO_Y 15
#define TREE_X 94
#define TREE_Y 25
#define ����_X 90
#define ����_Y 25
// ����� ������ ����



void setting();               // Ŀ���̵�, �ܼ�â ����
void gotoxy(int x, int y);    // 
void start();
int game(int);
void score(int);
int crashing();
void end(int);


void ����(int);                  // �����׸���
void ����1();                 //���������


//���� ���� �Լ�
void draw_dino(int);          // ����׸���
void earase_dino();           // ���������
void earase_foot();           // �������

//���� ���� �Լ�
void tree();                  //���� �����ʿ��� �������� �̵���Ű�� �Լ�
void draw_tree();            // �����׸���
void erase_tree();           // ���������

int ����X = ����_X;
int treeX = TREE_X;
int dinoX = DINO_X;
int dinoY = DINO_Y;



int key = 0; //Ű���� �Է� �ޱ�


int main()
{
	int tic = 0; //���� �� �ð� �������� ���� ���� ���
	int crash = 0; //�浹 üũ

	setting();
	start();

	while (1) {

		tic = game(tic);

		//'�����̽� ��' ������ ����
		if (_kbhit()) {
			key = _getch();
			if (key == 32 && dinoY - 15 == 0) { //'�����̽� ��'�� ������ ������ �ٴڿ� ���� ��

				int h = 0; //���� ���� �ʱ�ȭ

				while (h < 9) { //y������ 8ĭ ��� == ��������
					earase_dino();
					dinoY--;
					tic = game(tic);
					crash = crashing();
					if (crash == -1)
						break;
					h++;
				}

				while (h > 0) { //y������ 8ĭ �ϰ�
					tic = game(tic);
					crash = crashing();
					if (crash == -1)
						break;
					dinoY++;
					earase_dino();
					h--;
				}
			}
		}
		crash = crashing();
		if (crash == -1) //�浹 �� Ż��
			break;

	}

	end(tic);

	system("pause>>null");
	return 0;
}
int game(int tic) { //����ȭ�� ���� ���
	score(tic);
	tree();
	draw_dino(tic);
	����(tic);

	Sleep(20); //0.02��		//������ ����
	tic++;

	return tic;
}

int crashing() { //�浹 ����	//���̵� '��'
	// (����1 && ����2) && ����
	// ����1: ������ ���� 11ĭ���� �ڿ� ����
	// ����2: ������ ���� 15ĭ���� �տ� ����
	// ����1 && ����2: ������ ���� 11ĭ�� 15ĭ ���̿� ����
	// ����: ���� �� 3ĭ�� ���� 5ĭ ���� ���̰� ���ų� ���� ��
	if ((dinoX + 6 <= treeX + 2 && dinoX + 10 >= treeX + 2) && dinoY + 12 >= TREE_Y + 2)
		return -1;
	else
		return 0;
}

void draw_dino(int tic) { //���� �׸���---------------------------------------------------------------------------------------------------draw_dino

	int toc = tic % 8;

	//����
	gotoxy(dinoX, dinoY);			printf("\n");
	gotoxy(dinoX, dinoY + 1);		printf("          �����\n");
	gotoxy(dinoX, dinoY + 2);		printf("          ������\n");
	gotoxy(dinoX, dinoY + 3);		printf("          ������\n");
	gotoxy(dinoX, dinoY + 4);		printf("         ��         ��\n");
	gotoxy(dinoX, dinoY + 5);		printf("       ��             ��\n");
	gotoxy(dinoX, dinoY + 6);		printf("  ����     ��    �� ��\n");
	gotoxy(dinoX, dinoY + 7);		printf("  ��  ��       ���� ��\n");
	gotoxy(dinoX, dinoY + 8);		printf("  ��                  ��\n");
	gotoxy(dinoX, dinoY + 9);		printf("  ��                  ��\n");
	gotoxy(dinoX, dinoY + 10);		printf("    ��                ��\n");
	gotoxy(dinoX, dinoY + 11);		printf("      ��             ��\n");
	gotoxy(dinoX, dinoY + 12);		printf("        ��� ��� ��\n");


	//�� ������ ����
	if (toc >= 0 && toc <= 3) //4tic ���� ����
	{
		earase_foot();
		gotoxy(dinoX, dinoY + 13); //�� �׸���
		printf("           ��\n");
		//printf("         @@");
	}
	else
	{
		earase_foot();
		gotoxy(dinoX, dinoY + 13); //�� �׸���
		printf("                ��\n");
		//printf("              @@");
	}
}

void earase_foot() { //�� �����
	gotoxy(dinoX, dinoY + 13);
	printf("                        \n");
	printf("                          ");
}

void earase_dino() { //���� �����
	for (int i = 0; i < 24; i++) {   // ������ �����ϰ� ���ƿ��µ��� ����� ����� ������. // ������� ������ �Ӹ��� õ�忡 �ΰ����ų� ���� ������µ��� ������ ����
		gotoxy(dinoX, 6 + i);
		printf("                              ");
	}
	earase_foot();
}



//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

//�ڡڡ�

void ����(int tic) { //������ �׸���---------------------------------------------------------------------------------------------------������

	int toc = tic % 8;

	//����

	gotoxy(����X, ����_Y + 2);        printf("  ���������     \n");


	//�� ������ ����
	if (toc >= 0 && toc <= 3) //4tic ���� ����
	{
		����1();
		gotoxy(����X, ����_Y);      printf(" ���          ���    \n");
		gotoxy(����X, ����_Y + 1);  printf("����      ����     \n");
		//                          printf("  ���������     \n");
		gotoxy(����X, ����_Y + 3);  printf("     �����          ");
	}
	else
	{
		����1();
		gotoxy(����X, ����_Y);      printf("       ����          \n");
		gotoxy(����X, ����_Y + 1);  printf("    �������       \n");
		//							printf("  ���������     \n");
		gotoxy(����X, ����_Y + 3);  printf("����        ����   ");

	}
}

void ����1() { //�� �����
	gotoxy(����X, 6);
	printf("                                             \n");
	printf("                                             \n");
	printf("                                             \n");
	printf("                                               ");
}
void ����2() { //�� �����
	gotoxy(����X, 6);
	printf("                                             \n");
	printf("                                             \n");
	printf("                                             \n");
	printf("                                               ");
}



//------------------------------------------------------------------------------------------------------------------------------------------



void draw_tree() { //���� �׸���--------------------------------------------------------------------------------------------------------draw_tree
	gotoxy(treeX + 2, TREE_Y);         printf(" ���\n");
	gotoxy(treeX, TREE_Y + 1);        printf("�� ��� ��\n");
	gotoxy(treeX, TREE_Y + 2);        printf("������\n");
	gotoxy(treeX + 2, TREE_Y + 3);      printf(" ���\n");
	gotoxy(treeX + 2, TREE_Y + 4);      printf(" ���");
}

void erase_tree() { //���� �����
	gotoxy(treeX + 3, TREE_Y);        printf("     \n");
	gotoxy(treeX + 1, TREE_Y + 1);   printf("          \n");
	gotoxy(treeX + 1, TREE_Y + 2);   printf("          \n");
	gotoxy(treeX + 3, TREE_Y + 3);     printf("     \n");
	gotoxy(treeX + 3, TREE_Y + 4);      printf("     ");
}

void tree() { //���� �����ʿ��� �������� �̵�
	treeX--; //�������� �� ĭ �̵�
	erase_tree(); //�����
	draw_tree(); //�׸���

	if (treeX == 0)
		treeX = TREE_X; //������ ���� ������ �̵��ϸ� �ʱ�ȭ
}

void gotoxy(int x, int y) //----------------------------------------------------------------------------------------------------------gotoxy 
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setting() {  // ----------------------------------------------------------------------------------------------------------------setting
	//�ܼ�â ����
	system("title Jumping Dino by.woo");
	system("mode con:cols=150 lines=30");

	//Ŀ�� ����
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.dwSize = 1;
	ConsoleCursor.bVisible = 0; //Ŀ�� ����
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void start() { //���� ȭ��
	while (1) {
		gotoxy(30, 10);
		printf("Press 'Space bar' to start the game");
		draw_dino(0);

		if (_kbhit()) {
			key = _getch();
			if (key == 32) { //'�����̽� ��' �Է� Ȯ��
				system("cls");
				break;
			}
		}
	}
}

void score(int tic) { //���� ���
	gotoxy(45, 1);
	printf("score : %4d", tic / 5 * 10); // tic/5 �� 10��		//�ʵ� �� 4ĭ Ȯ�� (nõ������)
}

void end(int tic) { //���� ȭ��
	system("cls");
	int a = 10;
	gotoxy(a, a);		printf(" #####      ##    ##   ##  #######            #####    ##  ##  #######   ######  \n");
	gotoxy(a, a + 1);	printf("##   ##    ####   ### ###   ##  ##           ##   ##   ##  ##   ##  ##   ##  ##  \n");
	gotoxy(a, a + 2);	printf("##        ##  ##  #######   ##               ##   ##   ##  ##   ##       ##  ##  \n");
	gotoxy(a, a + 3);	printf("##        ######  ## # ##   ####             ##   ##   ##  ##   ####     #####   \n");
	gotoxy(a, a + 4);	printf("##  ###   ##  ##  ##   ##   ##               ##   ##   ##  ##   ##       ####    \n");
	gotoxy(a, a + 5);	printf("##   ##   ##  ##  ##   ##   ##  ##           ##   ##    ####    ##  ##   ## ##   \n");
	gotoxy(a, a + 6);	printf(" #####    ##  ##  ##   ##  #######            #####      ##    #######   ###  ## \n");

	gotoxy(40, 20);
	printf("final score : %4d", tic / 5 * 10); //���� ����
}