#include "csrtree.h"

int CreateTree(ptrToNode* eletree)
{
	ElementType ele;
	ElementType tmp;
	scanf("%d", &ele);	//��ȡԪ��
	tmp = getchar();
	if (ele == -1)
		*eletree = NULL;
	else
	{
		*eletree = (ptrToNode)malloc(sizeof(TreeNode));
		if (!(*eletree)) exit(-1);
		(*eletree)->Element = ele;
		cout << "����%d������Ҷ�ڵ�:" << ele << endl;
		CreateTree(&(*eletree)->LeftChild);
		cout << "����%d������Ҷ�ڵ�:" << ele << endl;
		CreateTree(&(*eletree)->rightChild);
	}
	return 1;
}

void TranverseHeadTree(ptrToNode eletree)
{

}


