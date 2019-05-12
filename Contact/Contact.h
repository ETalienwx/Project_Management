#ifndef __CONTACT_H__
#define __CONTACT_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define NAME_MAX 20
#define SEX_MAX 5
#define TELE_MAX 12
#define ADDR_MAX 30
#define MAX 1000
#define DEFAULT_SZ 3

//����������Ϣ�ṹ��
typedef struct PeoInfo
{
	char name[NAME_MAX];
	int age;
	char sex[SEX_MAX];
	char tele[TELE_MAX];
	char addr[ADDR_MAX];
}PeoInfo;

////����ͨѶ¼�ṹ��(��̬�汾)
//typedef struct Contact
//{
//	PeoInfo date[MAX];//�������
//	int sz;//��ǰ������Ϣ�ĸ���
//}Contact,*pContact;//pContact����һ���ṹ��ָ������

//����ͨѶ¼�ṹ��(��̬�汾)
typedef struct Contact
{
	PeoInfo * date;//ָ��һ��ռ�
	int sz;//��ǰ������Ϣ�ĸ���
	int capacity;
}Contact, *pContact;//pContact����һ���ṹ��ָ������

//��������
void InitContact(pContact pc);//pContact=Contact*
void AddContact(pContact pc);
void ShowContact(pContact pc);
void DelContact(pContact pc);
void SearchContact(pContact pc);
void ModifyContact(pContact pc);
void SortContact(pContact pc);
void EmptyContact(pContact pc);
void DestroyContact(pContact pc);


#endif //__CONTACT_H__