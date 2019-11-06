#ifndef __GAME_H__
#define __GAME_H__

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ROW 9
#define COL 9

#define ROWS ROW+2
#define COLS COL+2

#define EASY_COUNT 10//简单版本
//初始化棋盘
void InitBoard(char board[ROWS][COLS], int row, int col, int set);
//设置雷
void SetMine(char board[ROWS][COLS], int row, int col);
//打印棋盘
void PrintBoard(char board[ROWS][COLS], int row, int col);
//排雷
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row,int col);
//计算周围雷的个数
int GetMineCount(char mine[ROWS][COLS], int x, int y);
#endif //__GAME_H__