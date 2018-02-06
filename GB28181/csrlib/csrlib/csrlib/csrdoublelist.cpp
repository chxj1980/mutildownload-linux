#include "csrdoublelist.h"

void csrdoulistCreate(list * t_list)
{
	//���������ݳ�ʼ��  
	t_list->m_data = -1;
	//˫��ѭ�������ʼ��ʱnext,prev��ָ���Լ�  
	t_list->next = t_list;
	t_list->prev = t_list;
}

void csrdoulistHeadInsert(list * t_list, int t_data)
{
	//����һ����㣬�������ڴ�  
	node t_node = (node)malloc(sizeof(list));
	//�ڵ����ݸ�ֵ  
	t_node->m_data = t_data;

	//�Ӵ���prev��nextָ��ֵ  
	t_node->prev = t_list;
	t_node->next = t_list->next;

	//���������ӽڵ�  
	t_list->next->prev = t_node;
	t_list->next = t_node;
}

void csrdoulistTailInsert(list * t_list, int t_data)
{
	//����һ���ڵ�  
	node t_node = (node)malloc(sizeof(list));

	//�ڵ����ݸ�ֵ  
	t_node->m_data = t_data;

	//�ڵ�prev��nextָ��ֵ  
	t_node->next = t_list;
	t_node->prev = t_list->prev;

	t_list->prev->next = t_node;
	t_list->prev = t_node;

}


node csrdoulistFind(list * t_list, int t_data)
{
	node t_node = NULL;
	//��������  
	node t_temp;

	for (t_temp = t_list->next;t_temp != t_list;t_temp = t_temp->next)
	{
		//����ڵ����  
		if (t_temp->m_data == t_data)
		{
			//��¼���˳�  
			t_node = t_temp;
			break;
		}
	}
	return t_node;
}

void csrdoulistModify(list * t_list, int t_old, int t_new)
{
	//���ҽڵ�  
	node t_node = csrdoulistFind(t_list, t_old);

	//��������ڸ����ݽڵ�  
	if (NULL == t_node)
	{
		//ֱ�ӽ�������  
		return;
	}
	//�ڵ����ݸ�ֵ  
	t_node->m_data = t_new;
}

void csrdoulistDelete(list * t_list, int t_data)
{
	//���ҽڵ�  
	node t_node = csrdoulistFind(t_list, t_data);

	//��������ڸ����ݽڵ�  
	if (NULL == t_node)
	{
		//ֱ�ӽ����ú���  
		return;
	}
	//��ǰ�ڵ��ǰһ���ڵ��next��ָ��ǰ�ڵ����һ��  
	t_node->prev->next = t_node->next;
	//��ǰ�ڵ����һ�ڵ��prevָ��ǰ�ڵ����һ��  
	t_node->next->prev = t_node->prev;
}

void csrdoulistDestroy(list * t_list)
{
	//���������ڵ�  
	node t_temp, t_node;
	//��ȡ��ǰ�ڵ�ĺ�һ�ڵ�  
	t_temp = t_list->next;

	while (t_temp != t_list)
	{
		t_node = t_temp;

		t_temp = t_temp->next;

		free(t_node);
	}
	t_node = NULL;
}

void csrdoulistDisplayAsc(list * t_list)
{
	node t_temp;

	for (t_temp = t_list->next;t_temp != t_list;t_temp = t_temp->next)
	{
		printf("%d ", t_temp->m_data);
	}
	printf("\n");
}


void csrdoulistDisplayDesc(list * t_list)
{
	node t_temp;


	for (t_temp = t_list->prev;t_temp != t_list;t_temp = t_temp->prev)
	{
		printf("%d ", t_temp->m_data);
	}
	printf("\n");
}