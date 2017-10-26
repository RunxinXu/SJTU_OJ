#include <iostream>

using namespace std;

//�������� ʱ�临�Ӷ�O(n) �ռ临�Ӷ�O(n)
//�ȶ����򣡣���Ϊ��ʵ���ȶ� �����a�����ǴӺ�����ǰ�������ԭ�򰡣�����
template<class T>
void countsort(T a[], int size,int m) //���ݴ�0��m
{
	T*b=new T[size]; //��������õ�
	T*c=new T[m + 1];  //���  ��ʵ�������൱�ڴ��֮���� �Կռ任ʱ��
	for (int i = 0; i < m + 1; ++i) c[i] = 0;

	//ͳ��ÿ�������ֵĴ���
	for (int i = 0; i < size; ++i)
	{
		c[a[i]]++;  
	}

	//����� ʹ�����ݱ�ʾ С�ڵ����±�����ĸ���
	for (int i = 1; i < m + 1; ++i)
	{
		c[i] = c[i - 1] + c[i];
	}

	for (int i = size - 1; i >= 0; --i)
	{
		//ɨ��A ��ÿ��������ŵ����ʵ�λ��
		T value = a[i];
		int pos = c[a[i]] - 1;
		b[pos] = value;
		c[a[i]]--;  //����һ��֮��ǵôӱ���ȥ�� �������Դ�������������ظ���ʱ����Լ�������ȥ��ͬ��λ�� ������ɺ�ǿŶ����
	}
	delete[]c;
	for (int i = 0; i < size; ++i) a[i] = b[i];
	delete[]b;
}

struct node
{
	int data;
	node* next;
	node() :next(nullptr) {};
	node(int data) :data(data), next(nullptr) {};
};
//�������� �ӵ�λ��ʼ �Ž���Ӧ�� ֮������ �ٰ�˳��ŵڶ�λ ֱ����λ����
//��֯������
template<class T>
void bucketsort(node *&p, int d)
{
	//p����������ͷ d������λ��
	node *bucket[10], *last[10], *tail; //last��ÿ��bucket�Ĺ���ָ��
	int i, j, k, base = 1;

	for (i = 1; i <= d; ++i)
	{
		for (j = 0; j <= 9; ++j) bucket[j] = last[j] = nullptr; //��ʼ��ÿ��bucket
		while (p != nullptr)
		{
			k = p->data / base % 10; //��ǰ����λ����Ӧ������
			if (bucket[k] == nullptr) bucket[k] = last[k] = p;
			else last[k]->next = p;
			p = p->next; //��һλ
		}
		p = nullptr;
		//������������
		for (j = 9; j >= 0; --j)
		{
			if (bucket[j] == nullptr) continue;
			if (p == nullptr) p = bucket[j];
			else tail->next = bucket[j];
			tail = last[j];  //���ù��м� ��ֻҪͷβ�͹��������� 
		}
		tail->next = nullptr;
		base *= 10;
	}
}




int main()
{
	int a[] = { 2,1,5,3,6,9,5,5,4,1,2,3 };
	countsort(a, 12, 9);
	for (int i = 0; i < 12; ++i) cout << a[i] << endl;

	
	return 0;
}