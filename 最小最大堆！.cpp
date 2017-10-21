#include <iostream>
#include <cmath>

using namespace std;

//实现一个最小最大堆  
//由于最小堆 or 最大堆 都只能根据最小值 或最大值 来操作
//而最小最大堆可以两种操作都在对数时间内完成
//他的结构是 奇数层（根节点为第一层）为最小层 偶数层为最大层
//最小层的结点<=下面的结点 最大层的结点>=下面的结点
//有个非常重要的顺序就是最小最大堆的顺序从小到大就是最小层从上到下 然后到最大层 最大层从下到上 非常vivid！！！


//上滤和下滤是关键~！！！
//下滤时要跳着来~ : 如果是跳到儿子 那就直接跳 说明已经到底了！！ 如果是跳到孙子 还要检查和儿子关系 及时调整是在最小层还是在最大层
//如果要跳到不同大小层 则及时交换 并且将下滤的对象和值进行更改！！！！继续下滤
//比如我在最小层1 滤到最下层2 但是发现我比父亲最大层1的结点要大 那么我及时地去做最大层的结点 把那个最大层的结点换下来最小层 然后现在改为下滤这个结点
//因为它刚刚来到最小层 不一定能胜任工作即不一定比下面的要小！！

//上滤时比下滤简单 先直接看他应该是属于最小层的还是最大层的 然后之后就不用改了  一直隔代上滤即可！！

//但增加删除元素的想法与二叉堆还是差不多的
//增加：增加到最后 然后调整 看看应该在最小层还是最大层 然后上滤
//删除：最后一个放到根节点 然后下滤 这个和普通二叉堆完全一样（虽然下滤过程不一样）
//由于它是完全二叉树所以仍然组织成顺序结构来存储

template <class T>
class minmaxheap
{
	T *data; //储存的数组
	int length;//有效长度 (不包括0）
	int size;//数组长度

	int level(int p)
	{
		int lvl = (int)(log(p) / log(2));  //算出当前高度
		return lvl % 2;
	}; //p在最大层返回1 最小层返回0
	void percolatedownmin(int p);
	void percolatedownmax(int p);
	void percolateupmin(int p,T x);
	void percolateupmax(int p,T x);
	int findminsonorgrandson(int n);
	int findmaxsonorgrandson(int n);  //找到结点n的儿子和孙子中的最小节点  显然如果有孙子那肯定返回的是孙子 没有孙子就返回儿子

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
	//最后一个元素到根节点 然后下滤
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
void minmaxheap<T>::percolatedownmin(int i)     //在最小层的下滤
{
	int last = length / 2;
	int x = data[i];
	while (i <= last)    //当p有儿子的时候
	{
		int min = findminsonorgrandson(i);
		if (x <= data[min]) break;    //满足了 返回
		else
		{
			data[i] = data[min];
			if (min <= 2 * i + 1)
			{
				//如果min是i的儿子 那么只需要换然后结束
				i = min;
				break;
			}
			else //是它的孙子
			{
				int p = min / 2;//与上一层比较
				if (data[p] < x)
				{
					T  tmp = data[p];
					data[p] = x;
					x = tmp;          //这部相当精髓 ！！改变了下滤的目标对象！！包括值！！
				}
				 i = min;
			}
		}
	}
	data[i] = x;
}

template<class T>
void minmaxheap<T>::percolatedownmax(int i)   //在最大层的下滤
{
	int last = length / 2;
	int x = data[i];
	while (i <= last)    //当p有儿子的时候
	{
		int max = findmaxsonorgrandson(i);
		if (x >=data[max]) break;
		else
		{
			data[i] = data[max];
			if (max <= 2 * i + 1)
			{
				//如果min是i的儿子 那么只需要换然后结束
				i = max;
				break;
			}
			else //是它的孙子
			{
				int p = max / 2;//与上一层比较
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
void minmaxheap<T>::percolateupmax(int i,T x)  //在最大层的上滤
{
	//已经调整好了 只需要负责隔代上滤
	
	for (int j = i / 4; j && (x > data[j]); j /= 4)
	{
		data[i] = data[j];
		i = j;
	}
	data[i] = x;

	
}

template<class T>
void minmaxheap<T>::percolateupmin(int i,T x)  //在最小层的上滤
{
	//已经调整好了 只需要负责隔代上滤
	
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
	//插入到最后然后调整然后上滤
	if (length == size - 1) { cout << "满" << endl; return; }
	++length;
	int p = length / 2;
	if (p == 0) { data[1] = x; return; } //空
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