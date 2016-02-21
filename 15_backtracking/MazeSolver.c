#include "MazeSolver.h"

int Solve(MazeInfo* Maze)
{
	int i = 0;
	int j = 0;
	int StartFound = FAIL;
	int Result = FAIL;

	Position Start;

	// 미로의 시작점 구하기
	for ( i = 0; i<Maze->RowSize; i++)
	{
		for (j=0; j<Maze->ColumnSize; j++)
		{
			if (Maze->Data[i][j] == START)
			{
				Start.X = j;
				Start.Y = i;
				StartFound = SUCCEED;
				break;
			}	
		}
	}

	if (StartFound == FAIL)
	{
		return FAIL;
	}

	// 시작점에서 동,서,남,북으로 이동하며 이동
	// 책의 샘플은 여기서 동,서,남,북으로 분기를 해놨는데, MoveTo 안에서 재귀로 시작점부터 길을 찾고 있음.
	// MoveTo 의 Direction 파라미터와 아래쪽 else if 로직 제거함.
	if (MoveTo(Maze, &Start))
	{
		Result = SUCCEED;
	}
	// 아래 로직 필요 없고, MoveTo 메소드의 Direction 도 필요없어서 제거.
	// else if (MoveTo(Maze, &Start, SOUTH))
	// {
	// 	Result = SUCCEED;
	// }
	// else if (MoveTo(Maze, &Start, EAST))
	// {
	// 	Result = SUCCEED;
	// }
	// else if (MoveTo(Maze, &Start, WEST))
	// {
	// 	Result = SUCCEED;
	// }

	// 시작점에 'S' 표시
	Maze->Data[Start.Y][Start.X] = START;

	return Result;
}


// 길 찾기
int MoveTo(MazeInfo* Maze, Position* Current)
{
	int i = 0;

	int Dirs[] = {NORTH, SOUTH, WEST, EAST};

	Position Next;

	// 현재 촤표가 도착점이라면
	if (Maze->Data[Current->Y][Current->X] == GOAL)
	{
		return SUCCEED;
	}
	
	// 도착점이 아니라면

	// 지나온 길이라는 걸 표시
	Maze->Data[Current->Y][Current->X] = MARKED;

	// 현 좌표에서 동,서,남,북 으로 이동하며 길을 찾는다.
	for (i=0; i<4; i++)
	{
		// 동,서,남,북 방향별로 다음 좌표(길)를 구한다. 벽이나 이미 갔던길 (MARKED) 이면 FAIL
		if (GetNextStep(Maze, Current, Dirs[i], &Next) == FAIL)
		{
			continue;
		}

		// GetNextStep 에서 찾은 다음 좌표가 길이라면 
		// 다음 길로 이동. 다음 길이 도착점이면 성공.
		if (MoveTo(Maze, &Next) == SUCCEED)
		{
			return SUCCEED;
		}
	}

	// 도착점을 찾지 못 한 경우 현재 좌표를 길로 다시 설정(이미 앞에서 MARKED 로 표시 했었기 때문에)
	Maze->Data[Current->Y][Current->X] = WAY;

	return FAIL;
}

// 다음 길 찾기 (동,서,남,북 방향의)
int GetNextStep(MazeInfo* Maze, Position* Current, int Direction, Position* Next)
{
	switch (Direction)
	{
		case NORTH:
			Next->X = Current->X;
			Next->Y = Current->Y - 1;

			if (Next->Y == -1)
			{
				return FAIL;
			}

			break;
		case SOUTH:
			Next->X = Current->X;
			Next->Y = Current->Y + 1;

			if (Next->Y == Maze->RowSize)
			{
				return FAIL;
			}

			break;
		case WEST:
			Next->X = Current->X - 1;
			Next->Y = Current->Y;

			if (Next->X == -1)
			{
				return FAIL;
			}

			break;
		case EAST:
			Next->X = Current->X + 1;
			Next->Y = Current->Y;

			if (Next->X == Maze->ColumnSize)
			{
				return FAIL;
			}

			break;
	}

	if (Maze->Data[Next->Y][Next->X] == WALL)
	{
		return FAIL;
	}
	if (Maze->Data[Next->Y][Next->X] == MARKED)
	{
		return FAIL;
	}

	return SUCCEED;
}

// 파일에서 미로를 가져온다.
int GetMaze(char* FilePath, MazeInfo* Maze)
{
	int i = 0;
	int j = 0;
	int RowSize = 0;
	int ColumnSize = INIT_VALUE;

	FILE* fp;
	char buffer[MAX_BUFFER];

	if ((fp = fopen(FilePath, "r")) == NULL)
	{
		printf("Cannot open file:%s\n", FilePath);
		return FAIL;
	}

	// 미로의 가로세로(행,열) 확인
	while (fgets(buffer, MAX_BUFFER, fp) != NULL)
	{
		RowSize++;

		if (ColumnSize == INIT_VALUE)
		{
			ColumnSize = strlen(buffer) - 1;
		}
		else if (ColumnSize != strlen(buffer) - 1)
		{
			printf("Maze data in file:%s is not valid. %lu\n", FilePath, strlen(buffer));
			fclose(fp);
			return FAIL;
		}
	}

	Maze->RowSize = RowSize;
	Maze->ColumnSize = ColumnSize;
	Maze->Data = (char**)malloc(sizeof(char*) * RowSize);

	// 미로의 가로세로에 대한 좌표 data 
	for (i=0; i<RowSize; i++)
	{
		Maze->Data[i] = (char*)malloc(sizeof(char) * ColumnSize);
	}

	rewind(fp);

	// 좌표 data 에 미로의 데이터 입력. (즉, 벽과 길, 출발점, 도착점 등을 각 좌표에 입력)
	for (i =0; i<RowSize; i++)
	{
		fgets(buffer, MAX_BUFFER, fp);

		for (j=0; j<ColumnSize;j++)
		{
			Maze->Data[i][j] = buffer[j];
		}
	}

	fclose(fp);
	return SUCCEED;
}