#ifndef _CSR_ORDER_H_
#define _CSR_ORDER_H_

#include "comheader.h"

using namespace std;

//template <class T>
#define SwapData(T1, T2) float tmp = T1; \
                           T1 = T2;  \
                           T2 = tmp; \

//��������
template <class T>
void SwapDataT(T& t1, T& t2)
{
	T tmp = t1;
	t1 = t2;
	t2 = t1;
}

//ð������
template <class T>
void SortBubble(T tinfo[], int arrNum, bool bLToS = true)
{
	for(auto varOutter = 0; varOutter < arrNum; ++varOutter)
	{
		for (auto varInner = 0; varInner < arrNum - varOutter - 1; ++varInner)
		{
			if (bLToS)
			{
				if (tinfo[varInner] < tinfo[varInner + 1])
				{
					SwapData(tinfo[varInner], tinfo[varInner + 1]);
				}
					
			}
			else
			{
				if (tinfo[varInner] > tinfo[varInner + 1])
				{
					SwapData(tinfo[varInner], tinfo[varInner + 1]);
				}
					
			}
		}
	}
}

template <class T>
void DisplayData(T tinfo[], int arrNum)
{
	for (auto varData = 0; varData < arrNum; ++varData)
	{
		cout << tinfo[varData] << " ";
	}
	cout << endl;
}

/*
	�ڼ������ѧ��ʹ�õ������㷨ͨ��������Ϊ��
	�����ʱ�临�Ӷȣ���ƽ������������ܣ��������б�list���Ĵ�С(n)��һ����ԣ��õ�������O(n log n)���һ���������O(n2)������һ�����������������O(n)��
	��ʹ��һ������ؼ��Ƚ�����������㷨��ƽ��������������ҪO(n logn)��
	�洢��ʹ�������Լ�����������Դ��ʹ�ã�
	�ȶ��ԣ��ȶ������㷨����ԭ������ȼ�ֵ�ļ�¼ά����Դ���Ҳ�������һ�������㷨���ȶ��ģ�����������ȼ�ֵ�ļ�¼R��S������ԭ�����б���R������S֮ǰ������������б���RҲ��������S֮ǰ��
	��������ķ��������롢������ѡ�񡢺ϲ��ȵȡ�

	1���ȶ�������
	ð������bubble sort���� O(n2)
	��β������cocktail sort����O(n2)
	��������insertion sort����O(n2)
	Ͱ����bucket sort����O(n);��ҪO(k)����ռ�
	��������counting sort����O(n+k);��ҪO(n+k)����ռ�
	�鲢����merge sort����O(n log n);��ҪO(n)����ռ�
	ԭ�ع鲢���� O(n2)
	��������������binary tree sort���� O(n log n)����ʱ��; O(n2)�ʱ��;��ҪO(n)����ռ�
	�볲����pigeonhole sort����O(n+k);��ҪO(k)����ռ�
	��������radix sort����O(n��k);��ҪO(n)����ռ�
	٪������gnome sort���� O(n2)
	ͼ�������library sort���� ʱ�临�Ӷ�ͨ����O(n log n),��Ҫ(1+��)n����ռ�

	2�����ȶ�������
	ѡ������selection sort����O(n2)
	ϣ������shell sort����O(n log2 n)���ʹ����ѵ����ڰ汾
	Clover�����㷨��Clover sort����O(n)����ʱ�䣬O��n^2/2������
	������ O(n log n)
	������heap sort����O(n log n)
	ƽ������smooth sort���� O(n log n)
	��������quick sort����O(n log n)����ʱ��, O(n2)����;���ڴ�ġ������б�һ��������������֪����
	��ʡ����introsort����O(n log n)
	��������patience sort����O(n log n + k)����ʱ�䣬��Ҫ�����O(n + k)�ռ䣬Ҳ��Ҫ�ҵ���ĵ��������У�longest increasing subsequence��

	3��ʱ�临�Ӷ�
	ð������O(n2)
	ѡ������O(n2)
	��������O(n2)
	ϣ������O(n1.25)
	������O(n log n)
	�鲢����O(n log n)
	��������O(n log n)
	��������O(n)

	��Ȼ��ȫ���������£���������ή��ѡ��������ٶȣ������Ӹ��ʽǶ���˵���ο���Ϣѧ���ۣ��͸���ѧ���������㷨��������Ż�ʱ�����������ƽ���ٶȱȶ�����Ҫ��һЩ��

	4����ʵ�õ�����
	Bogo���� O(n �� n!)��������������ʱ��Ϊ���
	Stupid����O(n3);�ݹ�汾��ҪO(n2)����洢��
	������bead sort���� O(n) or O(��n),����Ҫ�ر��Ӳ��
	�������O(n),����Ҫ�ر��Ӳ��
	��Ƥ������stooge sort���㷨�򵥣�����ҪԼn^2.7��ʱ��
*/

//��������
int csrswapdata(int *a, int *b);

void csrswapdata(int &a, int &b);

//��ӡ����
void csrdisplay(int arr[], int num);

void csrdisplay(int arr[], long maxlen, int nbegin, int nend);

//ð��
void BubbleSort(int arrNum[], int nLen, bool bLToS);

//����
void QuickSort(int arrNum[], int maxLen, int nbegin, int nend, bool bToS = false);

//���뷨����
void InsertSort(int arrNum[], bool bToS);

#endif
