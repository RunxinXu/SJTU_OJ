#include <iostream>

using namespace std;

//用并查集思路 查找结点的最近的共同祖先

//如果是顺序存储的 那么可以不断把层次比较下面的（相同则任意）（即编号较大的）不断向上爬 这样肯定会相遇在同一个结点 那个就是
//最近的共同祖先！！！！

//如果是链表型的树 以孩子兄弟树为例
//我们用递归 且用后序遍历 如果在某个子树同时找到了那就是 如果没有那么再检查下根然后返回上一层

template<class T>
T tree<T>::LCA(node*t, T x, bool& xfind, T y, bool &yfind)
{
	//需要两个标志都为true 返回值才有意义！！！
	bool xtmp, ytmp;
	node *p;
	T lca;

	if (t == nullptr)
	{
		xfind = yfind = false;
		return x;
	}

	p = t->son;
	while (p != nullptr)
	{
		xtmp = ytmp = false;
		lca = LCA(p, x, xtmp, y, ytmp);
		if (xtmp&&ytmp)
		{
			xfind = yfind = true;
			return lca;
		}
		if (xtmp) xfind = true;
		if (ytmp) yfind = true;
		p = p->brother;
	}


	//后序遍历的访问根结点部分！！
	if (t->data == x) xfind = true;
	if (t->data == y)yfind = true;
	return t->data;
}

int main()
{
	
}
