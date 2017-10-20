#include <iostream>

using namespace std;

//ʵ��һ�����ȶ��� ���������

//����һЩ����δʵ�� �����Ƚϼ�
//�ı�ĳ���������ȶȣ�ֵ�� �� �ı�֮���жϱ仯 ��������� ��С������ ������ֱ��return
//���������ȵ�

template<class T>
class priorityqueue
{
	int size;    //�����е���Ч��С(ͷ��㲻���ȥ��
	T *array; //����������ȫ������ 0Ϊͷ��� ��
	int maxsize;  //��������ʵ�ʴ�С

	void doublespace();
	void buildheap();
	void percolatedown(int i);
	void percolateup(int i);  //i��Ϊ�±�
public:
	priorityqueue(int capacity = 100) :maxsize(capacity)
	{
		array = new T[capacity];
		size = 0;
	}
	priorityqueue(const T data[], int s);
	~priorityqueue() { delete[]array; }

	bool isempty() { return size == 0; }
	void enqueue(const T&x);
	T dequeue();
	T gethead() const { return array[1]; }

};

template<class T>
void priorityqueue<T>::enqueue(const T&x)
{
	//��Ӳ����Ǽӵ����һ�� Ȼ�����˵��ʵ�λ��
	if (size == maxsize-1) doublespace();
	size++;
	array[size] = x;
	percolateup(size);
}

template<class T>
T priorityqueue<T>::dequeue()
{
	//�����Ǹ��ڵ㱣�� Ȼ�󻻳����һ��Ԫ�� �����˵��ʵ�λ��
	T tmp = array[1];
	array[1] = array[size];
	size--;
	percolatedown(1);
	return tmp;
}

template<class T>
void priorityqueue<T>::percolatedown(int i)
{
	//���±�Ϊi�ĵ�i���������
	T tmp = array[i];
	int child;
	for (; i*2 <= size; i = child)   //ֻҪ���ж���
	{
		child = 2 * i;
		if (child < size && array[child + 1] < array[child]) child++; //�ҳ��������ӽ�С��һ��
		if (array[child] < tmp)
		{
			array[i] = array[child];
		}
		else break;
	}
	array[i] = tmp;
}

template <class T>
void priorityqueue<T>::percolateup(int i)
{
	//���±�Ϊi�ĵ�i��������˵��ʵ�λ��
	T tmp = array[i];
	int parent = i / 2;

	for (; i/2 >= 1; i = parent)
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

template<class T>
void priorityqueue<T>::buildheap()
{
	//���ѵ�ʱ�򲻲���һ��һ���ؼ��� ��Ϊ���ǲ��������м������״̬ ֻ��������
	//���ǲ�ȡ�ݹ���뷨����ӽ����Ҷ��ӽ���֮���ٸ��ڵ�����
	//�ٳ�����ʵҲ����ʡȥ�ݹ� �����һ���������ϵ��������
	//�ټ� ����Ҷ�ӽ�㲻�� ������ʵ����һ���������ϳ�ȥҶ��֮�������
	//���һ��һ���� ��ô���Ӷ�Ϊnlgn
	//����ڶ��� ��ô�����������н��ĸ߶�֮�� �����������ĸ߶�֮��ΪN-h-1 NΪ�ڵ��� hΪ����
	//����buildheap�ĸ��Ӷ���O(n) ��Ϊ����ʱ�䣡��

	for (int i = size / 2; i >= 0; --i)
	{
		percolatedown(i);
	}
}

template<class T>
priorityqueue<T>::priorityqueue(const T* items, int s)
{
	size = s;
	maxsize = size + 10;
	array = new T[maxsize];
	for (int i = 1; i <= size; ++i) array[i] = items[i - 1];
	buildheap();
}

template<class T>
void priorityqueue<T>::doublespace()
{
	maxsize *= 2;
	T *tmp = new T[maxsize];
	for (int i = 1; i <= size; ++i) tmp[i] = array[i];
	delete array;
	array = tmp;
}
int main()
{
	int a[] = { 8,10,21,4,3,5,79,21 };

	priorityqueue<int> hehe(a,8);
	for (int i = 0; i < 8; ++i)
	{
		int tmp = hehe.dequeue();
		cout << tmp << endl;
	}
	//���������ʵ��ʵ����һ��������
	//Ȼ�����ڿ���Ч�ʸ�������� ���ԶѲ�����������
	//����Ҫ��Ӧ�û������ȶ���


	return 0;
}