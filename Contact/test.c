#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include "Contact.h"

void menu()
{
	printf("***************************************\n");
	printf("********   1.add      2.del    ********\n");
	printf("********   3.search   4.modify ********\n");
	printf("********   5.show     6.sort   ********\n");
	printf("********   0.exit     7.empty  ********\n");
	printf("***************************************\n");

}

enum Option//ö�ٿ���ȡֵ������˳����menu���ֵ��Ӧ
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT,
	EMPTY
};

void test()
{
	int input = 0;
	Contact con;//1000��������Ϣ + sz����---ͨѶ¼
	InitContact(&con);//��ʼ��ͨѶ¼
	do
	{
		menu();
		printf("��ѡ��:");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			AddContact(&con);//1.����ַЧ�ʸ�2.����ַ���Ըı���
			break;
		case DEL:
			DelContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;
		case SHOW:
			ShowContact(&con);
			break;
		case SORT:
			SortContact(&con);
			break;
		case EXIT:
			DestroyContact(&con);
			printf("�˳�ͨѶ¼\n");
			break;
		case EMPTY:
			EmptyContact(&con);
		default:
			printf("ѡ�����\n");
			break;
		}
	} while (input);

}

int main()
{
	test();
	return 0;
}