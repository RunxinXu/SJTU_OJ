#include <iostream>
#include <string>


using namespace std;

//哈夫曼树有n个叶子结点 由于除了叶子结点其他都是度为2的结点 所以由n0=n2+1 得总结点树为2n-1
//由于量不变 所以可以采取静态存储 用一个数组来实现 规模为2n （0不用）
//由于要上溯 所以得有parent

template<class type>
class hfTree
{
private:
	struct node
	{
		type data;
		int weight;//权值
		int parent = 0, left = 0, right = 0; //用下标形式存储
	};

	node *elem; //存储结点的数组
	int length;
public:
	struct hfcode
	{
		type data;
		string code;
	};

	hfTree(const type*xx, const int *w, int size);
	void getcode(hfcode[]);
	~hfTree() { delete[]elem; }
};

template<class type>
hfTree<type>::hfTree(const type*xx, const int *w, int size)   //x为待编码的东西的数组 w为权值数组
{
	const int max_int = 32767;
	int min1,min2;
	int x, y;//两待合并树的下标

	length = 2 * size;  //size个叶子结点 则一共有
	elem = new node[length];

	for (int i = size; i < length; ++i)
	{
		elem[i].weight = w[i - size];
		elem[i].data = xx[i - size];
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

template <class type>
void hfTree<type>::getcode(hfcode result[])
{
	int size = length / 2; //length绝对是偶数
	int p, s;

	for (int i = size; i < length; ++i)
	{
		result[i - size].data = elem[i].data;
		result[i - size].code = "";
		p = elem[i].parent; s = i;

		while (p != 0)
		{
			if (elem[p].left == s) result[i - size].code = "0" + result[i - size].code;
			if (elem[p].right == s) result[i - size].code = "1" + result[i - size].code;
			s = p; p = elem[s].parent;
		}
	}
}


int main()
{
	char ch[] = { "aeistdn" };
	int w[] = { 10,15,12,3,4,13,1 };

	hfTree<char> tree(ch, w, 7);
	hfTree<char> ::hfcode result[7];
	tree.getcode(result);
	for (int i = 0; i < 7; ++i)
	{
		cout << result[i].data << " ->  " << result[i].code;
		cout << endl;
	}
	return 0;
}

