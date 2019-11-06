#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void test()
{
  //测试游戏
	char mine[ROWS][COLS];//存放雷的信息
	char show[ROWS][COLS];//存放排查到雷的信息
	InitBoard(mine, ROWS, COLS, '0');//初始化mine棋盘为0
	InitBoard(show, ROWS, COLS, '*');//初始化show棋盘为*
	//布置雷
	SetMine(mine,ROW,COL);//把雷放在9行9列的棋盘mine里
	PrintBoard(show,ROW,COL);//打印show棋盘
	//排雷
	FindMine(mine,show,ROW,COL);
}
int main()
{
	srand((unsigned int)time(NULL));
	test();
	system("pause");
	return 0;
}