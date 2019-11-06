#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

//初始化数组mine和show
void InitBoard(char board[ROWS][COLS], 
	           int row, int col, int set)
{
	memset(board, set, row*col*sizeof(board[0][0]));
	//row*col*sizeof(board[0][0])棋盘总大小
	//memset（地址（board），字符（0或*），要改变的长度（整个棋盘的大小））
} 

//设置雷（把雷放在9*9的mine棋盘里）
void SetMine(char board[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int count = EASY_COUNT;
	
	while (count)
	{
		x = rand() % row + 1;
		y = rand() % col + 1;
        //mine棋盘刚刚初始化为0，将我们要设置为雷的地方设置为1
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}

}

//打印棋盘
void PrintBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
    //给前面打印列号
	for (i = 0; i <= col; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	//打印九行九列
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//排雷
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS],
	int row, int col)
{
	//1.输入坐标
	//2.判断坐标的合法
	//a非法 b合法
	//3.判断是否为雷
	//a是雷，游戏结束
	//b不是雷，统计周围雷的个数，并记录
	int win = 0;
	while (win < row*col - EASY_COUNT)
	{
		int x = 0;
		int y = 0;
		printf("请输入要排查的坐标:>");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			//合法
			if (mine[x][y] == '1')//是雷
			{
				printf("很遗憾，你被炸死了！\n");
				PrintBoard(mine, ROW, COL);
				break;
			}
			else//不是雷（统计周围雷的个数）
			{
				int count = GetMineCount(mine, x, y);
				show[x][y] = count + '0';
				win++;
				PrintBoard(show, ROW, COL);

			}
		}
		else
		{
			printf("坐标非法，请重新输入！\n");
		}
	}
	if (win >= (row*col - EASY_COUNT))
	{
		printf("恭喜你，排雷成功\n");
		PrintBoard(mine, ROW, COL);
	}
}
//计算周围雷的个数
int GetMineCount(char mine[ROWS][COLS], int x, int y)
{
	    return mine[x - 1][y] +
		mine[x - 1][y - 1] +
		mine[x][y - 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] +
		mine[x][y + 1] +
		mine[x - 1][y + 1]-8*'0';
}