#include <iostream>
#include <cstring>

using namespace std;

class priorityqueue
{
	int size;    //数组中的有效大小(头结点不算进去）
	int *array; //用数组存放完全二叉树 0为头结点 空
	int maxsize;  //数组现在实际大小

	void doublespace();
	void percolatedown(int i);
	void percolateup(int i);  //i均为下标
public:
	priorityqueue(int capacity = 100) :maxsize(capacity)
	{
		array = new int[capacity];
		size = 0;
	}
	~priorityqueue() { delete[]array; }

	bool isempty() { return size == 0; }
	void enqueue(const int&x);

	void decrease(int i, int tmp);

	void find(int x);	

};


void priorityqueue::enqueue(const int&x)
{
	//入队操作是加到最后一个 然后上滤到适当位置
	if (size == maxsize - 1) doublespace();
	size++;
	array[size] = x;
	percolateup(size);
}

void priorityqueue::percolatedown(int i)
{
	//将下标为i的第i个结点下滤
	int tmp = array[i];
	int child;
	for (; i * 2 <= size; i = child)   //只要还有儿子
	{
		child = 2 * i;
		if (child < size && array[child + 1] < array[child]) child++; //找出两个儿子较小的一个
		if (array[child] < tmp)
		{
			array[i] = array[child];
		}
		else break;
	}
	array[i] = tmp;
}


void priorityqueue::percolateup(int i)
{
	//将下标为i的第i个结点下滤到适当位置
	int tmp = array[i];
	int parent = i / 2;

	for (; i / 2 >= 1; i = parent)
	{
		parent = i / 2;
		if (array[parent] > tmp)
		{
			array[i] = array[parent];
		}
		else break;
	}
	array[i] = tmp;
}



void priorityqueue::doublespace()
{
	maxsize *= 2;
	int *tmp = new int[maxsize];
	for (int i = 1; i <= size; ++i) tmp[i] = array[i];
	delete array;
	array = tmp;
}
void priorityqueue::decrease(int i, int tmp)
{
	array[i] -= tmp;
	percolateup(i);
}

void priorityqueue::find(int x)
{
	int i = 1;
	for (i = 1; i <= size; ++i)
	{
		if (array[i] > x)break;
	}
	cout << i << endl;
}

int main()
{
	priorityqueue hehe(100);

	int m;
	cin >> m;
	char*p = new char[10];
	int tmp;
	for (int i = 0; i < m; ++i)
	{
		cin >> p >> tmp;
		if (strcmp(p, "insert") == 0)
		{
			hehe.enqueue(tmp);
		}
		if (strcmp(p, "decrease") == 0)
		{
			int tmp2;
			cin >> tmp2;
			hehe.decrease(tmp, tmp2);   //第tmp1个结点值减少tmp2
		}
		if (strcmp(p, "find") == 0)
		{
			hehe.find(tmp);
		}
	}


	return 0;
}