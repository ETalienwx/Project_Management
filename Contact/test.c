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

enum Option//枚举可能取值，按照顺序与menu里的值对应
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
	Contact con;//1000个任务信息 + sz个数---通讯录
	InitContact(&con);//初始化通讯录
	do
	{
		menu();
		printf("请选择:");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			AddContact(&con);//1.传地址效率高2.传地址可以改变它
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
			printf("退出通讯录\n");
			break;
		case EMPTY:
			EmptyContact(&con);
		default:
			printf("选择错误\n");
			break;
		}
	} while (input);

}

int main()
{
	test();
	return 0;
}