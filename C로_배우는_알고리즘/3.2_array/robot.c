#include <dos.h>
#include <conio.h>
#include <bios.h>
#include <stdlib.h>

#define MAZE_SIZE 19
#define ROBOT 2


int maze[MAZE_SIZE][MAZE_SIZE] = 
	{	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

int sx = MAZE_SIZE -1 , sy = MAZE_SIZE -2; //생쥐의 출발 위치

int *rec; // 최단 경로 계산을 위해 생쥐가 움직인 경로를 저장

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

int get_shape(int m[][MAZE_SIZE], int x, int y)
{
	static shape[] = 
		{32, 179, 196, 192, 179, 179, 218, 195, 196, 217, 196, 193, 191, 180, 194, 197};

		int s = 0;
		if (m[y][x])
		{
			if (y > 0 && m[y-1][x]) s |= UP;
			if (y < MAZE_SIZE - 2 && m[y+1][x]) s |= DOWN;
			if (y > 0 && m[y][x-1]) s |= LEFT;
			if (y < MAZE_SIZE - 2 && m[y][x+1]) s |= RIGHT;

		}

		return shape[s];
}

void draw_maze(int m[][MAZE_SIZE])
{
	int i, j;
	for(j=0; j<MAZE_SIZE; j++)
	{
		for (i = 0; i <MAZE_SIZE; i++)
		{
			gotoxy(i + 1, j + 1);
			putch(get_shape(m, i, j));
		}
	}
}

int main(void)
{
	rec = (int*)malloc(MAZE_SIZE * MAZE_SIZE);

	if (rec == NULL)
	{
		cputs("\r\n Memory allocation error !");
		exit(1);
	}

	clrscr();
	draw_maze(maze);

	gotoxy(40, 5);
	cputs("Simulation of Micro Mouse");
	gotoxy(40, 10);
	cputs("Press any key to start...");
	bioskey(0);
	right_hand(maze, sx, sy, LEFT); // 생쥐 1차 시도

	gotoxy(40, 10);
	cputs(" Press any key to see shortest path...");
	bioskey(0);
	shortest_path(); // 생쥐 2차 시도, 최단 경로

	gotoxy(40, 10);
	cputs("Press any key to end program...");
	bioskey(0);
}