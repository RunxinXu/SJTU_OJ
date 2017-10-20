#include <iostream>
#include <vector>
#include <cmath>

//爸爸要去跑步了 感觉书上这个实现有问题 我也懒得改了 就这个思想
using namespace std;
//二项队列  实现merge
//用数组来放树结点 每棵树都符合堆的性质 根节点小于等于儿子

//!!!!!!!!极其牛逼！！！！！！！！！！！//
//由于是普通树而非二叉树 你不知道儿子有几个 所以组织形式//
//是 孩子-结点树！！！！！！ 向左倾斜！！！！！卧槽！！！

//合并的时候： 申请足够大的规模 亮点是二进制的时间情况处理
//enqueue就是和一个只有一个结点的merge咯
//dequeue就要在所有根节点中找最小的踢出去 之后那棵树就变成很多棵子树（填满了所有低位） 之后merge咯


template<class T>
struct node
{
	T key;
	node* left, *right;
	node(const T&k, node*l, node *r) :key(k), left(l), right(r) {};
};
template<class T>
class binaryqueue
{
	
	int size;   
	vector<node*> trees;
	

	node* merge(node*t1, node*t2);
	int capacity() {
		return pow(2, size+1)-1;
	}//返回可以存放的结点数最大值
public:
	binaryqueue(int n = 100)   //n为预计的元素个数
	{
		size = int(log(n) / log(2)) + 1;
		trees = new node*[size];
		for (int i = 0; i < size; ++i) trees[i] = nullptr;
	}
	void enqueue(const T&x);
	void dequeue();
	void merge(const binaryqueue&other);
};

template<class T>
node<T>* binaryqueue<T>::merge(node*t1, node*t2)
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

template<class T>
void binaryqueue<T>::merge(const binaryqueue& other)
{
	if (this == &other) return;

	//两个森林的合并 每个森林都有一个数组
    //合并后结果储存在当前的

	size += other.size;
	if (size > capacity())
	{
		//看看当前vector能不能存的下
		int old = trees.size();
		int newa = max(trees.size(), other.trees.size()) + 1;
		trees.resize(newa);
		for (int i = old; i < newa; ++i) trees[i] = nullptr;
	} 

	node *carry = nullptr;
	for (int i = 0, j = 1; j <= size+2; i++, j *= 2)   
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
			 other.trees[i] = nullptr;
			 break;
		 case 3://有当前的和other的
			 carry = merge(t1, t2);
			 trees[i] = other.trees[i] = nullptr;
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
			 other.trees[i] = nullptr;
			 break;
		 case 7://有当前的和other的和carry的
			 trees[i] = carry;          //carry留下 另外两个合并并进位
			 carry = merge(trees[i], other.trees[i]);
			 other.trees[i] = nullptr;
			 break;
		 }
	}
	for (int k = ; k < other.trees.size(); ++k) other.trees[k] = nullptr;
	other.size = 0;
	
}
template<class T>
void enqueue(const T&x);
{

}
int main()
{
	
	return 0;
}