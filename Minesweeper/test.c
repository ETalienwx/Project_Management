#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void test()
{
  //������Ϸ
	char mine[ROWS][COLS];//����׵���Ϣ
	char show[ROWS][COLS];//����Ų鵽�׵���Ϣ
	InitBoard(mine, ROWS, COLS, '0');//��ʼ��mine����Ϊ0
	InitBoard(show, ROWS, COLS, '*');//��ʼ��show����Ϊ*
	//������
	SetMine(mine,ROW,COL);//���׷���9��9�е�����mine��
	PrintBoard(show,ROW,COL);//��ӡshow����
	//����
	FindMine(mine,show,ROW,COL);
}
int main()
{
	srand((unsigned int)time(NULL));
	test();
	system("pause");
	return 0;
}