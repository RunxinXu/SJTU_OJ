#include <iostream>

using namespace std;

//实现一个优先队列 即二叉堆类

//其他一些功能未实现 但都比较简单
//改变某个结点的优先度（值） ： 改变之后判断变化 变大则下滤 变小则上滤 不变则直接return
//还有其他等等

template<class T>
class priorityqueue
{
	int size;    //数组中的有效大小(头结点不算进去）
	T *array; //用数组存放完全二叉树 0为头结点 空
	int maxsize;  //数组现在实际大小

	void doublespace();
	void buildheap();
	void percolatedown(int i);
	void percolateup(int i);  //i均为下标
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
	//入队操作是加到最后一个 然后上滤到适当位置
	if (size == maxsize-1) doublespace();
	size++;
	array[size] = x;
	percolateup(size);
}

template<class T>
T priorityqueue<T>::dequeue()
{
	//出队是根节点保存 然后换成最后一个元素 并下滤到适当位置
	T tmp = array[1];
	array[1] = array[size];
	size--;
	percolatedown(1);
	return tmp;
}

template<class T>
void priorityqueue<T>::percolatedown(int i)
{
	//将下标为i的第i个结点下滤
	T tmp = array[i];
	int child;
	for (; i*2 <= size; i = child)   //只要还有儿子
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

template <class T>
void priorityqueue<T>::percolateup(int i)
{
	//将下标为i的第i个结点下滤到适当位置
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
	//建堆的时候不采用一个一个地加入 因为我们并不关心中间的有序状态 只关心最后的
	//我们采取递归的想法左儿子建堆右儿子建堆之后再根节点下滤
	//再抽象其实也可以省去递归 这就是一个从下往上的逐个下滤
	//再简化 由于叶子结点不用 所以其实就是一个从下往上除去叶子之外的下滤
	//如果一个一个加 那么复杂度为nlgn
	//如果第二种 那么最坏情况就是所有结点的高度之和 而满二叉树的高度之和为N-h-1 N为节点数 h为树高
	//所以buildheap的复杂度是O(n) 即为线性时间！！

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
	//这个过程其实就实现了一个堆排序
	//然而由于快排效率搞过堆排序 所以堆不常用于排序
	//最主要的应用还是优先队列


	return 0;
}