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

//定义人物信息结构体
typedef struct PeoInfo
{
	char name[NAME_MAX];
	int age;
	char sex[SEX_MAX];
	char tele[TELE_MAX];
	char addr[ADDR_MAX];
}PeoInfo;

////定义通讯录结构体(静态版本)
//typedef struct Contact
//{
//	PeoInfo date[MAX];//存放数据
//	int sz;//当前已有信息的个数
//}Contact,*pContact;//pContact就是一个结构体指针类型

//定义通讯录结构体(动态版本)
typedef struct Contact
{
	PeoInfo * date;//指向一块空间
	int sz;//当前已有信息的个数
	int capacity;
}Contact, *pContact;//pContact就是一个结构体指针类型

//函数声明
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