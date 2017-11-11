#include <iostream>


using namespace std;

class hfTree
{
private:
	struct node
	{
		int weight;//权值
		int parent = 0, left = 0, right = 0; //用下标形式存储
	};
	int s;
	node *elem; //存储结点的数组
	int length;
public:
	hfTree(const int *w, int size);
	~hfTree() { delete[]elem; }
	void xixixi()const
	{
		int sum = 0;
		for (int i = 1; i < s; ++i)
		{
			sum += elem[i].weight;
		}
		cout << sum;
	}
};

hfTree::hfTree(const int *w, int size)   //x为待编码的东西的数组 w为权值数组
{
	const int max_int = 32767;
	int min1, min2;
	int x, y;//两待合并树的下标

	s = size;
	length = 2 * size;  //size个叶子结点 则一共有
	elem = new node[length];

	for (int i = size; i < length; ++i)
	{
		elem[i].weight = w[i - size];
		elem[i].parent = elem[i].left = elem[i].right = 0;
	}
	//初始化 结点放在下标n 到 2n-1中 之后不断选两个权值最小的组成一个权值之和新节点放到空余位置的最后一个(也是有数据的前一位)并更新父子关系

	for (int i = size - 1; i >= 0; --i)
	{
		min1 = min2 = max_int; x = y = 0;
		for (int j = i + 1; j < length; ++j)
		{
			if (elem[j].parent == 0)
			{
				//需要未被合并的 也就是作为根节点的
				if (elem[j].weight < min1)
				{
					min2 = min1;
					min1 = elem[j].weight;
					y = x;
					x = j;
					//min1 永远比 min2 要小 
				}
				else
				{
					//比不过min1 那么就和min2比比
					if (elem[j].weight < min2)
					{
						min2 = elem[j].weight;
						y = j;
					}
				}
			}
		}

		elem[i].weight = min1 + min2;
		elem[i].left = x;
		elem[i].right = y;
		elem[x].parent = i;
		elem[y].parent = i;
		elem[i].parent = 0;
	}

}


int main()
{
	
	int n;
	cin >> n;
	int *xx = new int[n];
	for (int i = 0; i < n; ++i) cin >> xx[i];

	hfTree hehe(xx, n);
	hehe.xixixi();



	return 0;
}

