#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;
//二项队列  实现merge
//用数组来放树结点 每棵树都符合堆的性质 根节点小于等于儿子

//!!!!!!!!极其牛逼！！！！！！！！！！！//
//由于是普通树而非二叉树 你不知道儿子有几个 所以组织形式//
//是 孩子-结点树！！！！！！ 向左倾斜！！！！！卧槽！！！

//合并的时候： 申请足够大的规模 亮点是二进制的时间情况处理
//enqueue就是和一个只有一个结点的merge咯
//dequeue就要在所有根节点中找最小的踢出去 之后那棵树就变成很多棵子树（填满了所有低位） 之后merge咯



struct node
{
	int key;
	node* left, *right;
	node(const int&k, node*l, node *r) :key(k), left(l), right(r) {};
};
class binaryqueue
{
	
public:
	int size;
	vector<node*> trees;
	node* merge(node*t1, node*t2);

	binaryqueue(int n = 1)   
	{
		size = n;
		trees.resize(size);
		trees.reserve(size * 2);
		for (int i = 0; i < size; ++i) trees[i] = nullptr;
	}
	void insert(const int&x);
	void delete_min();
	void merge(const binaryqueue&other);
	int get_min_pos();
	int get_min()
	{
		int pos = get_min_pos();
		return trees[pos]->key;
	}
};
node* binaryqueue::merge(node*t1, node*t2)
{

	//合并两棵树
	//算法思想是 根节点比较大的这棵树作为根节点比较小的树的子树 与根结点直接相连
	if (t2->key < t1->key) return merge(t2, t1);
	//保证t2合并为t1的右子树

	//合并 和 对孩子兄弟树的维护
	t2->right = t1->left;
	t1->left = t2;
	return t1;

}

void binaryqueue::merge(const binaryqueue& other)
{
	if (this == &other) return;
	if (other.size == 0) return;

	//两个森林的合并 每个森林都有一个数组
	//合并后结果储存在当前的
	if (other.size > size)
	{
		size = other.size;
	}
	size++;  //留个空可以进位咯
	if(size>trees.size()) trees.resize(size);

	node *carry = nullptr;
	for (int i = 0;i<size;++i)
	{
		node *t1 = trees[i];
		node *t2 = (i < other.trees.size()) ? other.trees[i] : nullptr;

		int whichcase = t1 == nullptr ? 0 : 1;
		whichcase += t2 == nullptr ? 0 : 2;
		whichcase += carry == nullptr ? 0 : 4;
		//由于刚好8种情况 所以可以采取二进制的形式来判断

		switch (whichcase)
		{
		case 0:  //没有树
		case 1:break;  //只有当前的
		case 2://只有other的
			trees[i] = other.trees[i];
			//other.trees[i] = nullptr;
			break;
		case 3://有当前的和other的
			carry = merge(t1, t2);
			trees[i] = nullptr;
			//other.trees[i] = nullptr;
			break;
		case 4://只有carry
			trees[i] = carry;
			carry = nullptr;
			break;
		case 5://有当前的和进位的
			carry = merge(carry, trees[i]);
			trees[i] = nullptr;
			break;
		case 6://有other的和进位的
			carry = merge(carry, other.trees[i]);
			//other.trees[i] = nullptr
			break;
		case 7://有当前的和other的和carry的
			trees[i] = carry;          //carry留下 另外两个合并并进位
			carry = merge(trees[i], other.trees[i]);
			//other.trees[i] = nullptr;
			break;
		}
	}
	//for (int k = ; k < other.trees.size(); ++k) other.trees[k] = nullptr;
	//other.size = 0;
	while (trees[size - 1] == nullptr) --size;
}
void binaryqueue::insert(const int&x)
{
	binaryqueue tmp(1);
	tmp.trees[0] = new node(x,nullptr,nullptr);
	binaryqueue::merge(tmp);
}

int binaryqueue::get_min_pos()
{
	int min_pos = 0;
	while (trees[min_pos] == nullptr) min_pos++;
	int min = trees[min_pos]->key;
	for (int i = min_pos+1; i < size; ++i)
	{
		if (trees[i] && trees[i]->key < min)
		{
			min = trees[i]->key;
			min_pos = i;
		}
	}
	return min_pos;
}

void binaryqueue::delete_min()
{
	int pos = get_min_pos();
	//删了之后填满了0--pos-1所有
	binaryqueue tmp(pos);
	node* p = trees[pos]->left;
	for (int i = pos - 1; i >= 0; --i)
	{
		tmp.trees[i] = p;
		p = p->right;
	}
	trees[pos] = nullptr;
	binaryqueue::merge(tmp);

}
int main()
{
	int m;
	cin >> m;
	char *p = new char[10];
	int tmp;
	binaryqueue hehe(0);
	for (int i = 0; i < m; ++i)
	{
		cin >> p;
		if (strcmp(p, "insert") == 0)
		{
			cin >> tmp;
			hehe.insert(tmp);
		}
		if (strcmp(p, "delete") == 0)
		{
			hehe.delete_min();
		}
		if (strcmp(p, "min") == 0)
		{
			cout << hehe.get_min() << endl;
		}
	}
	delete []p;
	return 0;
}