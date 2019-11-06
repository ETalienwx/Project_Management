#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

//��ʼ������mine��show
void InitBoard(char board[ROWS][COLS], 
	           int row, int col, int set)
{
	memset(board, set, row*col*sizeof(board[0][0]));
	//row*col*sizeof(board[0][0])�����ܴ�С
	//memset����ַ��board�����ַ���0��*����Ҫ�ı�ĳ��ȣ��������̵Ĵ�С����
} 

//�����ף����׷���9*9��mine�����
void SetMine(char board[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int count = EASY_COUNT;
	
	while (count)
	{
		x = rand() % row + 1;
		y = rand() % col + 1;
        //mine���̸ոճ�ʼ��Ϊ0��������Ҫ����Ϊ�׵ĵط�����Ϊ1
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}

}

//��ӡ����
void PrintBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
    //��ǰ���ӡ�к�
	for (i = 0; i <= col; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	//��ӡ���о���
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

//����
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS],
	int row, int col)
{
	//1.��������
	//2.�ж�����ĺϷ�
	//a�Ƿ� b�Ϸ�
	//3.�ж��Ƿ�Ϊ��
	//a���ף���Ϸ����
	//b�����ף�ͳ����Χ�׵ĸ���������¼
	int win = 0;
	while (win < row*col - EASY_COUNT)
	{
		int x = 0;
		int y = 0;
		printf("������Ҫ�Ų������:>");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			//�Ϸ�
			if (mine[x][y] == '1')//����
			{
				printf("���ź����㱻ը���ˣ�\n");
				PrintBoard(mine, ROW, COL);
				break;
			}
			else//�����ף�ͳ����Χ�׵ĸ�����
			{
				int count = GetMineCount(mine, x, y);
				show[x][y] = count + '0';
				win++;
				PrintBoard(show, ROW, COL);

			}
		}
		else
		{
			printf("����Ƿ������������룡\n");
		}
	}
	if (win >= (row*col - EASY_COUNT))
	{
		printf("��ϲ�㣬���׳ɹ�\n");
		PrintBoard(mine, ROW, COL);
	}
}
//������Χ�׵ĸ���
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