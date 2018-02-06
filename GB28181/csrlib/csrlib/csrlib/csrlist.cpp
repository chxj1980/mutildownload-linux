#include "csrlist.h"

ptrList createList()
{
	ptrList pList = (ptrList)malloc(sizeof(ptrList));
	return pList;
}

void insertList(ptrList pList, ptrNode pNode)
{

}

void deleteList(ptrList pList, ptrNode pNode)
{

}

void modifyList(ptrList pList, ptrNode pNode)
{

}

ptrNode findList(ptrList pList, int data)
{
	return pList->head;
}



void listCreate(linuxlist * t_list)
{
	//��ʼ������������
	t_list->m_data = -1;
	t_list->next = NULL;
}

void listHeadInsert(linuxlist * t_list, int t_data)
{
	linuxnode pNode = (linuxnode)malloc(sizeof(linuxlist));
	pNode->m_data = t_data;
	pNode->next = t_list->next;
	t_list->next = pNode;
}

void listTailInsert(linuxlist * t_list, int t_data)
{
	linuxnode pNode = (linuxnode)malloc(sizeof(linuxlist));
	linuxnode pTail = t_list->next;
	while (pTail != NULL)
		pTail = pTail->next;

	pNode->m_data = t_data;
	pNode->next = NULL;

	pTail->next = pNode;
}

void listModify(linuxlist * t_list, int t_old, int t_new)
{
	linuxnode pNode = t_list->next;
	for (; pNode != NULL; pNode = pNode->next)
	{
		if (pNode->m_data == t_old)
			pNode->m_data = t_new;
	}
}

void listDelete(linuxlist * t_list, int t_data)
{
	linuxnode pNode = t_list->next;
	for (; pNode != NULL; pNode = pNode->next)
	{
		if (pNode->m_data == t_data)
		{
			if (pNode == NULL)
			{
				printf("�ڵ㲻����");
				return;
			}
			break;
		}
	}

	linuxnode pPreNode = t_list;
	while (pPreNode->next != pNode)
		pPreNode = pPreNode->next;

	pPreNode->next = pNode->next;

	free(pNode);
	pNode == NULL;
}

linuxnode listFind(linuxlist * t_list, int t_data)
{
	linuxnode pNode;
	for (pNode = t_list->next; pNode != NULL; pNode = pNode->next)
	{
		if (pNode->m_data == t_data)
			return pNode;
	}

	return NULL;
}

void listDisplay(linuxlist * t_list)
{
	linuxnode pNode;
	for (pNode = t_list->next; pNode != NULL; pNode = pNode->next)
		printf("%d ", pNode->m_data);
	printf("\n");
}

void listDestroy(linuxlist * t_list)
{
	linuxnode pNode = t_list->next;
	while (pNode != NULL)
	{
		linuxnode pTmp = pNode;
		pNode = pNode->next;
		free(pTmp);
	}
	printf("all delete over\n");
}

void listReverse(linuxlist * t_list)
{
	linuxnode pNode = NULL, pHead = NULL, pTmp = NULL;
	pHead = t_list->next;								//�洢ͷ���
	pNode = pHead->next;								//��ǰ����ڵ�
	pHead->next = NULL;									// һ��Ҫ��ΪNULL��������ܵ���ѭ��

	while (pNode)
	{
		pTmp = pNode->next;								//�洢�¸�������ڵ�
		pNode->next = pHead;							//����ǰ�ڵ���뵽����ڵ��һ���ڵ�֮ǰ�����ı�headָ��
		pHead = pNode;
		t_list->next = pHead;							//ʹ����ͷָ��ָ�������ĵ�һ���ڵ�
		//t_list->next = pNode;
		pNode = pTmp;									//���������¸�������ڵ�
	}
}

int listLength(linuxlist * t_list)
{
	linuxnode pNode;
	int nLen = 0;
	for (pNode = t_list->next; pNode != NULL; pNode = pNode->next)
		nLen++;
	return nLen;
}

void listBubbleSort(linuxlist * t_list)
{
	linuxnode pNode;
	int nLen = listLength(t_list);
	for (int i = 0; i < nLen; ++i)
	{
		pNode = t_list->next;
		for (int j = 0; j < nLen - i - 1; ++j)
		{
			if (pNode->m_data > pNode->next->m_data)
			{
				int t_data = pNode->m_data;
				pNode->m_data = pNode->next->m_data;
				pNode->next->m_data = t_data;
			}
			pNode = pNode->next;
		}
	}
}

void listQuickSort(linuxlist* t_list)
{

}

