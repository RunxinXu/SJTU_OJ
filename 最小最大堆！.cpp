#include <iostream>
#include <cmath>

using namespace std;

//ʵ��һ����С����  
//������С�� or ���� ��ֻ�ܸ�����Сֵ �����ֵ ������
//����С���ѿ������ֲ������ڶ���ʱ�������
//���Ľṹ�� �����㣨���ڵ�Ϊ��һ�㣩Ϊ��С�� ż����Ϊ����
//��С��Ľ��<=����Ľ�� ����Ľ��>=����Ľ��
//�и��ǳ���Ҫ��˳�������С���ѵ�˳���С���������С����ϵ��� Ȼ������ ������µ��� �ǳ�vivid������


//���˺������ǹؼ�~������
//����ʱҪ������~ : ������������� �Ǿ�ֱ���� ˵���Ѿ������ˣ��� ������������� ��Ҫ���Ͷ��ӹ�ϵ ��ʱ����������С�㻹��������
//���Ҫ������ͬ��С�� ��ʱ���� ���ҽ����˵Ķ����ֵ���и��ģ���������������
//����������С��1 �˵����²�2 ���Ƿ����ұȸ�������1�Ľ��Ҫ�� ��ô�Ҽ�ʱ��ȥ������Ľ�� ���Ǹ�����Ľ�㻻������С�� Ȼ�����ڸ�Ϊ����������
//��Ϊ���ո�������С�� ��һ����ʤ�ι�������һ���������ҪС����

//����ʱ�����˼� ��ֱ�ӿ���Ӧ����������С��Ļ�������� Ȼ��֮��Ͳ��ø���  һֱ�������˼��ɣ���

//������ɾ��Ԫ�ص��뷨�����ѻ��ǲ���
//���ӣ����ӵ���� Ȼ����� ����Ӧ������С�㻹������ Ȼ������
//ɾ�������һ���ŵ����ڵ� Ȼ������ �������ͨ�������ȫһ������Ȼ���˹��̲�һ����
//����������ȫ������������Ȼ��֯��˳��ṹ���洢

template <class T>
class minmaxheap
{
	T *data; //���������
	int length;//��Ч���� (������0��
	int size;//���鳤��

	int level(int p)
	{
		int lvl = (int)(log(p) / log(2));  //�����ǰ�߶�
		return lvl % 2;
	}; //p�����㷵��1 ��С�㷵��0
	void percolatedownmin(int p);
	void percolatedownmax(int p);
	void percolateupmin(int p,T x);
	void percolateupmax(int p,T x);
	int findminsonorgrandson(int n);
	int findmaxsonorgrandson(int n);  //�ҵ����n�Ķ��Ӻ������е���С�ڵ�  ��Ȼ����������ǿ϶����ص������� û�����Ӿͷ��ض���

public:
	minmaxheap(int n = 100) :size(n + 1), length(0)
	{
		data = new T[size];
	}
	~minmaxheap() { delete[]data; };
	void enqueue(T x);
	T getmax() { if (length > 1)return data[2] < data[3] ? data[3] : data[2]; else return data[1]; }
	T getmin() { return data[1]; }
	T dequeuemin();
	T dequeuemax();
	bool isempty() { return length == 0; }

};

template<class T>
T minmaxheap<T>::dequeuemin()
{
	//���һ��Ԫ�ص����ڵ� Ȼ������
	T tmp = data[1];
	data[1] = data[length];
	length--;
	percolatedownmin(1);
	return tmp;
}

template<class T>
T minmaxheap<T>::dequeuemax()
{
	if (length == 1)
	{
		return dequeuemin(1);
	}
	else
	{
		int max = 2;
		if (max + 1 <= length && data[max + 1] > data[max]) max++;
		data[max] = data[length];
		length--;
		percolatedownmax(max);
		return data[max];
	}
}

template<class T>
void minmaxheap<T>::percolatedownmin(int i)     //����С�������
{
	int last = length / 2;
	int x = data[i];
	while (i <= last)    //��p�ж��ӵ�ʱ��
	{
		int min = findminsonorgrandson(i);
		if (x <= data[min]) break;    //������ ����
		else
		{
			data[i] = data[min];
			if (min <= 2 * i + 1)
			{
				//���min��i�Ķ��� ��ôֻ��Ҫ��Ȼ�����
				i = min;
				break;
			}
			else //����������
			{
				int p = min / 2;//����һ��Ƚ�
				if (data[p] < x)
				{
					T  tmp = data[p];
					data[p] = x;
					x = tmp;          //�ⲿ�൱���� �����ı������˵�Ŀ����󣡣�����ֵ����
				}
				 i = min;
			}
		}
	}
	data[i] = x;
}

template<class T>
void minmaxheap<T>::percolatedownmax(int i)   //�����������
{
	int last = length / 2;
	int x = data[i];
	while (i <= last)    //��p�ж��ӵ�ʱ��
	{
		int max = findmaxsonorgrandson(i);
		if (x >=data[max]) break;
		else
		{
			data[i] = data[max];
			if (max <= 2 * i + 1)
			{
				//���min��i�Ķ��� ��ôֻ��Ҫ��Ȼ�����
				i = max;
				break;
			}
			else //����������
			{
				int p = max / 2;//����һ��Ƚ�
				if (data[p] > x)
				{
					T tmp = data[p];
					data[p] = x;
					x = tmp;
				}
				i = max;
			}
		}
	}
	data[i] = x;
}

template<class T>
int minmaxheap<T>::findminsonorgrandson(int n)
{
	int min = 2 * n;
	if (min + 1 <= length && data[min + 1] < data[min]) ++min;
	for (int k = 4 * n; k <= length&&k < 4 * (n + 1); ++k)
		if (data[k] < data[min]) min = k;
	return min;
}

template<class T>
int minmaxheap<T>::findmaxsonorgrandson(int n)
{
	int max = 2 * n;
	if (max + 1 <= length && data[max + 1] > data[max]) ++max;
	for (int k = 4 * n; k <= length&&k < 4 * (n + 1); ++k)
		if (data[k] > data[max]) max = k;
	return max;
}

template<class T>
void minmaxheap<T>::percolateupmax(int i,T x)  //�����������
{
	//�Ѿ��������� ֻ��Ҫ�����������
	
	for (int j = i / 4; j && (x > data[j]); j /= 4)
	{
		data[i] = data[j];
		i = j;
	}
	data[i] = x;

	
}

template<class T>
void minmaxheap<T>::percolateupmin(int i,T x)  //����С�������
{
	//�Ѿ��������� ֻ��Ҫ�����������
	
	for (int j = i / 4; j && (x < data[j]); j /= 4)
	{
		data[i] = data[j];
		i = j;
	}
	data[i] = x;


}
template<class T>
void minmaxheap<T>::enqueue(T x)
{
	//���뵽���Ȼ�����Ȼ������
	if (length == size - 1) { cout << "��" << endl; return; }
	++length;
	int p = length / 2;
	if (p == 0) { data[1] = x; return; } //��
	switch (level(p))
	{
	case 0:
		if (x < data[p])
		{
			data[length] = data[p];
			percolateupmin(p,x);
		}
		else
			percolateupmax(length,x);
		break;
	case 1:
		if (x > data[p])
		{
			data[length] = data[p];
			percolateupmax(p,x);
		}
		else
			percolateupmin(length,x);
	}

}

int main()
{
	minmaxheap<int> hehe(10);
	hehe.enqueue(20);
	hehe.enqueue(2);
	hehe.enqueue(15);
	hehe.enqueue(17);
    hehe.enqueue(28);
	hehe.enqueue(0);

	for (int i = 0; i < 6; ++i)

	{
		cout << hehe.dequeuemin() << endl;
	}
	return 0;

}