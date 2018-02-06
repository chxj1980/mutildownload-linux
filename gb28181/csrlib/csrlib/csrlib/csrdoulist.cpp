#include "csrdoulist.h"  


void listCreate(list * t_list)
{
	t_list->m_data = -1;
	t_list->next = NULL;
	t_list->prev = NULL;
}

void listHeadInsert(list * t_list, int t_data)
{
	//����һ���ڵ㣬�������ڴ�  
	node t_node = (node)malloc(sizeof(list));

	//�ڵ����ݸ�ֵ  
	t_node->m_data = t_data;
	t_node->next = NULL;
	t_node->prev = NULL;

	//��ӽڵ�  
	t_node->next = t_list->next;
	t_node->prev = t_list;

	if (t_list->next != NULL)
	{
		t_list->next->prev = t_node;
	}
	t_list->next = t_node;

}

void listDisplay(list * t_list)
{
	node t_temp;

	for (t_temp = t_list->next;t_temp != NULL; t_temp = t_temp->next)
	{
		printf("%d ", t_temp->m_data);
	}
	printf("\n");
}