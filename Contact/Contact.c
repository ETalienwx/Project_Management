#define _CRT_SECURE_NO_WARNINGS 1
#include "Contact.h"

//函数实现
void InitContact(pContact pc)
{
	pc->sz = 0;
	pc->date = (PeoInfo*)malloc(DEFAULT_SZ * sizeof(PeoInfo));
	pc->capacity = DEFAULT_SZ;
}

void DestroyContact(pContact pc)
{
	assert(pc);
	free(pc->date);
	pc->date = NULL;
	pc->capacity = 0;
	pc->sz = 0;
}

void * check_capacity(pContact pc)
{
	if (pc->capacity == pc->sz)
	{
		PeoInfo* tmp = realloc(pc->date, (pc->capacity + 2)*sizeof(PeoInfo));
		if (tmp != NULL)
		{
			pc->date = tmp;
			pc->capacity += 2;
			printf("增容成功\n");
			return pc->date;
		}
		else
			return NULL;
	}
	return pc->date;
}

void AddContact(pContact pc)
{
	assert(pc);
	check_capacity(pc);
	printf("请输入姓名：");
	scanf("%s", pc->date[pc->sz].name);
	printf("请输入年龄：");
	scanf("%d", &(pc->date[pc->sz].age));
	printf("请输入性别：");
	scanf("%s", pc->date[pc->sz].sex);
	printf("请输入电话：");
	scanf("%s", pc->date[pc->sz].tele);
	printf("请输入地址：");
	scanf("%s", pc->date[pc->sz].addr);
	pc->sz++;
}

void ShowContact(pContact pc)
{
	assert(pc);
	int i = 0;
	printf("%10s\t%4s\t%5s\t%12s\t%20s\n", "name", "age", "sex", "tele", "addr");
	for (i = 0; i < pc->sz; i++)
	{
		printf("%10s\t%4d\t%5s\t%12s\t%20s\n",
			pc->date[i].name,
			pc->date[i].age,
			pc->date[i].sex,
			pc->date[i].tele,
			pc->date[i].addr );
	}
}

int FindEntry(pContact pc, char name[])
{
	assert(pc);
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		if (strcmp(pc->date[i].name, name) == 0)
		{
			return i;
		}
	}
	return -1;//没找到
}

void DelContact(pContact pc)
{
	assert(pc);
	int i = 0;
	int j = 0;
	int pos = 0;
	char name[NAME_MAX] = { 0 };
	printf("请输入要删除人的名字：");
	scanf("%s", name);
	//查找
	pos = FindEntry(pc, name);
	//删除
	if (pos != -1)
	{
		for (j = pos; j < pc->sz - 1; j++)
		{
			pc->date[j] = pc->date[j + 1];
		}
		pc->sz--;
		printf("删除成功\n");
	}
	else
	{
		printf("删除的人不存在\n");
	}
}

void SearchContact(pContact pc)
{
	assert(pc);
	char name[NAME_MAX] = { 0 };
	printf("请输入要查找人的名字：");
	scanf("%s", name);
	int pos = 0;
	pos = FindEntry(pc, name);
	if (pos != -1)
	{
		printf("%10s\t%4s\t%5s\t%12s\t%20s\n", "name", "age", "sex", "tele", "addr");
		printf("%10s\t%4d\t%5s\t%12s\t%20s\t\n",
			pc->date[pos].name,
			pc->date[pos].age,
			pc->date[pos].sex,
			pc->date[pos].tele,
			pc->date[pos].addr);
	}
	else
	{
		printf("要查找的人不存在\n");
	}
}

void ModifyContact(pContact pc)
{
	assert(pc);
	char name[NAME_MAX] = { 0 };
	printf("请输入要修改人的名字：");
	scanf("%s", name);
	//找
	int pos = 0;
	pos = FindEntry(pc, name);
	if (pos != -1)
	{
		printf("请输入姓名：");
		scanf("%s", pc->date[pos].name);
		printf("请输入年龄：");
		scanf("%d", &(pc->date[pos].age));
		printf("请输入性别：");
		scanf("%s", pc->date[pos].sex);
		printf("请输入电话：");
		scanf("%s", pc->date[pos].tele);
		printf("请输入地址：");
		scanf("%s", pc->date[pos].addr);
		printf("修改成功\n");
	}
	else
	{
		printf("要修改的人不存在\n");
	}
}

void SortContact(pContact pc)
{
	assert(pc);
	int i = 0;
	int j = 0;
	int flag = 0;
	for (i = 0; i < pc->sz - 1; i++)
	{
		for (j = 0; j < pc->sz - 1 - i; j++)
		{
			if (strcmp(pc->date[j].name, pc->date[j + 1].name)>0)
			{
				PeoInfo tmp = pc->date[j];
				pc->date[j] = pc->date[j + 1];
				pc->date[j + 1] = tmp;
				flag = 1;
			}
			
		}
		if (flag == 0)
		{
			break;
		}
	}
	
	printf("按姓名排序成功\n");
}

void EmptyContact(pContact pc)
{
	pc->sz = 0;
	printf("通讯录已清空\n");
}

