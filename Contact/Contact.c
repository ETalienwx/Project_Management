#define _CRT_SECURE_NO_WARNINGS 1
#include "Contact.h"

//����ʵ��
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
			printf("���ݳɹ�\n");
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
	printf("������������");
	scanf("%s", pc->date[pc->sz].name);
	printf("���������䣺");
	scanf("%d", &(pc->date[pc->sz].age));
	printf("�������Ա�");
	scanf("%s", pc->date[pc->sz].sex);
	printf("������绰��");
	scanf("%s", pc->date[pc->sz].tele);
	printf("�������ַ��");
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
	return -1;//û�ҵ�
}

void DelContact(pContact pc)
{
	assert(pc);
	int i = 0;
	int j = 0;
	int pos = 0;
	char name[NAME_MAX] = { 0 };
	printf("������Ҫɾ���˵����֣�");
	scanf("%s", name);
	//����
	pos = FindEntry(pc, name);
	//ɾ��
	if (pos != -1)
	{
		for (j = pos; j < pc->sz - 1; j++)
		{
			pc->date[j] = pc->date[j + 1];
		}
		pc->sz--;
		printf("ɾ���ɹ�\n");
	}
	else
	{
		printf("ɾ�����˲�����\n");
	}
}

void SearchContact(pContact pc)
{
	assert(pc);
	char name[NAME_MAX] = { 0 };
	printf("������Ҫ�����˵����֣�");
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
		printf("Ҫ���ҵ��˲�����\n");
	}
}

void ModifyContact(pContact pc)
{
	assert(pc);
	char name[NAME_MAX] = { 0 };
	printf("������Ҫ�޸��˵����֣�");
	scanf("%s", name);
	//��
	int pos = 0;
	pos = FindEntry(pc, name);
	if (pos != -1)
	{
		printf("������������");
		scanf("%s", pc->date[pos].name);
		printf("���������䣺");
		scanf("%d", &(pc->date[pos].age));
		printf("�������Ա�");
		scanf("%s", pc->date[pos].sex);
		printf("������绰��");
		scanf("%s", pc->date[pos].tele);
		printf("�������ַ��");
		scanf("%s", pc->date[pos].addr);
		printf("�޸ĳɹ�\n");
	}
	else
	{
		printf("Ҫ�޸ĵ��˲�����\n");
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
	
	printf("����������ɹ�\n");
}

void EmptyContact(pContact pc)
{
	pc->sz = 0;
	printf("ͨѶ¼�����\n");
}

