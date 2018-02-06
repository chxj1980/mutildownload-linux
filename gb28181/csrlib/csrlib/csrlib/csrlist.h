#pragma once

#include "comheader.h"

typedef struct _Node {
	struct _Node* next;
	int data;
}Node, *ptrNode;

typedef struct _List {
	struct _Node* head;
}List, *ptrList;
/*
	��ɾ�Ĳ�
*/

//��������
ptrList createList();

//����ڵ�
void insertList(ptrList pList, ptrNode pNode);

//ɾ���ڵ�
void deleteList(ptrList pList, ptrNode pNode);

//�޸Ľڵ���Ϣ
void modifyList(ptrList pList, ptrNode pNode);

ptrNode findList(ptrList pList, int data);

//list���� ����
//List*���� �ڵ�
typedef struct _linuxlist
{
	int m_data;//��Ա����
	struct _linuxlist * next;//�ṹ������Լ�������
}linuxlist, *linuxnode;

// ��������
void listCreate(linuxlist * t_list);

//ͷ�巨
void listHeadInsert(linuxlist * t_list, int t_data);
//β�巨
void listTailInsert(linuxlist * t_list, int t_data);

//�޸�����
void listModify(linuxlist * t_list, int t_old, int t_new);

//ɾ������
void listDelete(linuxlist * t_list, int t_data);

//��������
linuxnode listFind(linuxlist * t_list, int t_data);

//��ӡ����
void listDisplay(linuxlist * t_list);

//��������
void listDestroy(linuxlist * t_list);

//��ת
void listReverse(linuxlist * t_list);

//�󳤶�
int listLength(linuxlist * t_list);

//����
void listBubbleSort(linuxlist * t_list);

void listQuickSort(linuxlist* t_list);