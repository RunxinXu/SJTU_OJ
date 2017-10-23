#include <iostream>

using namespace std;
//实现了一个普通的二叉查找树类
//基本操作是 查找 插入 删除 其中删除比前两个复杂 但也不难 一般都用递归完成
//增加了三个删除 lessthan morethan bound 的函数 算法也挺不错的
//对于查找  插入 删除 的非递归实现 想到用栈 但是用栈的话 要找parent非常难 所以还是直接来
//查找插入还比较简单 删除的时候就要注意维护被删结点的parent了
//因为递归时候可以用一个指针的引用来实现修改parent属性
//然而如果是非递归就没有了 所以一定要时刻注意可以找到他的parent便于修改！！

//最牛逼的还是指针的引用！！！
template<class T>
class binarysearchtree
{
	struct node
	{
		T data;
		node*left, *right;
		node(const T &a, node*l, node*r) :data(a), left(l), right(r) {};

	};

	node* root;
	void insert(const T&x, node*&t);
	void remove(const T&x, node*&t);
	bool find(const T&x, node*t) const;
	void makeempty(node*t);
	void print(node *t)
	{
		if (t == nullptr) return;
		print(t->left);
		cout << t->data << endl;
		print(t->right);
	}
	bool check(node *t,T & min,T & max) const;
	void remove_less_than(const T&x, node*&t);
	void remove_more_than(const T&x, node *&t);
	void remove_bound(const T&x, const T&y, node *&t);


public:
	binarysearchtree(node *a = nullptr) { root = a; }
	~binarysearchtree() { makeempty(root); }
	bool find(const T&a) const;
	void insert(const T&x);
	void remove(const T&x);
	void print() { print(root); }
	bool check() const; //检查是否为查找二叉树

	void remove_less_than(const T&x);
	void remove_more_than(const T&x);
	void remove_bound(const T&x, const T&y);
};

template<class T>
void binarysearchtree<T>::insert(const T&x)
{
	insert(x, root);
}

template<class T>
void binarysearchtree<T>::remove(const T&x)
{
	remove(x, root);
}
template<class T>
bool binarysearchtree<T>::find(const T&x) const
{
	return find(x, root);
}
template<class T>
void binarysearchtree<T>::makeempty(node *t)
{
	if (t == nullptr) return;
	makeempty(t->left);
	makeempty(t->right);
	delete t;
}

template<class T>
bool binarysearchtree<T>::find(const T&x, node* t) const
{
	if (t == nullptr) return false;
	if (t->data == x) return true;
	else
	{
		if (x < t->data) return find(x, t->left);
		else return find(x, t->right);
	}
}

template<class T>
void binarysearchtree<T>::insert(const T&x, node* &t)  //这个指针的引用是关键 因为指针的改变是要保持回返回的地方的！！
{
	if (t == nullptr) t = new node(x, nullptr, nullptr);
	else
	{
		if (x < t->data) insert(x, t->left);
		else
			if (x > t->data) insert(x, t->right);
		//x==t->data不用处理 反正已经有了 让他自动中断返回即可
	}
}

template<class T>
void binarysearchtree<T>::remove(const T&x, node* &t) //指针的引用是精髓！！！！
{
	if (t == nullptr) return;
	if (x < t->data) remove(x, t->left);
	else
		if (x > t->data) remove(x, t-> right);
		else
		{
			//t所指就是所要删除的结点
			//如果他是叶子结点那么直接删除
			//如果他只有一个儿子 那么儿子代替他
			//如果他有两个儿子 找到右子树的最小的结点代替他 并删除那个最小的结点

			if (!t->left && !t->right)
			{
				//如果没有儿子
				node *tmp = t;
				t = nullptr;
				delete tmp;
			}
			else
			{
				if (t->left && !t->right)
				{
					node *tmp = t;
					t = t->left;
					delete tmp;
				}
				else
				{
					if (t->right && !t->left)
					{
						node *tmp = t;
						t = t->right;
						delete tmp;
					}
					else
					{
						//如果是两个儿子
						node *tmp = t->right;
						while (tmp->left) tmp = tmp->left;
						t->data = tmp->data;
						remove(tmp->data, t->right);
						//！！！！很坑！！！
						//这里不能用remove(tmp->data,tmp)因为tmp指针是外部的 并不是树内部指针
						//而指针用的是引用 你把tmp改了没什么卵用！！树没连起来！！！666！！！
					}
				}
			}
		}
}


//检查是否保持二叉查找树性质方法：
//检查左子树是否符合 并返回其最大值 检查右子树是否符合 并返回其最小值
//如果两个子树一个不符合 或者左子树最大值大于根值 或者右子树最小值小于根值 都是false
//否则true
template<class T>
bool binarysearchtree<T>::check() const
{
	T min, max;
	bool flag;
	if (root == nullptr) return true;
	if (root->left)
	{
		flag = check(root->left, min, max);
		if (!flag || max > root->data) return false;
	}
	if (root->right)
	{
		flag = check(root->right, min, max);
		if (!flag || min < root->data) return false;
	}
	return true;
}

template<class T>
bool binarysearchtree<T>::check(node *t, T &min, T & max) const
{
	T min, max;
	bool flag;
    
	if (t == nullptr) return true;
	if (t->left)
	{
		flag = check(t->left, min, max);
		if (!flag || max > t->data) return false;
	}
	else min = t->data;     //关键！！！  如果有左子树 那肯定是从左子树返回的min更小
	if (t->right)
	{
		flag = check(t->right, min, max);
		if (!flag || min < t->data) return false;
	}
	else max = t->data; //同上！
	return true;

}

//公有的和私有的check函数区别是 私有的还要维护min max 以向上返回
//而公有的只需要用就行了！！！


template<class T>
void binarysearchtree<T>::remove_less_than(const T&x)
{
	remove_less_than(x, root);
}

template<class T>
void binarysearchtree<T>::remove_more_than(const T&x)
{
	remove_more_than(x, root);
}

template<class T>
void binarysearchtree<T>::remove_bound(const T&x, const T&y)
{
	if(x<=y) remove_bound(x, y, root);
}

template<class T>
void binarysearchtree<T>::remove_less_than(const T&x, node *&t)
{
	if (t == nullptr) return;
	//如果x比t所指结点还小 那么递归左子树
	if (x <= t->data) remove_less_than(x, t->left);  //因为是删除比x小的所以t所指的并不用删！！
	else
	{
		//t的右子树可能也有点要删 所以先删掉左边的和t所指的
		//然后继续对t递归调用
		node *tmp = t;
		t = t->right;
		makeempty(tmp->left);
		delete tmp;
		remove_less_than(x, t);

	}
}

template<class T>
void binarysearchtree<T>::remove_more_than(const T&x, node*&t)
{

	//思想基本同上
	if (t == nullptr) return;
	if (t->data <= x) remove_more_than(x, t->right);
	else
	{
		node *tmp = t;
		t = t->left;
		makeempty(tmp->right);
		delete tmp;
		remove_more_than(x, t);
	}
}

template<class T>
void binarysearchtree<T>::remove_bound(const T&x, const T&y, node *&t)
{
	if (t == nullptr) return;
	//如果t所指结点小于x或者大于y 那么对子树递归调用
	if (t->data < x) remove_bound(x, y, t->right);
	else
		if (t->data > y) remove_bound(x, y, t->left);
		else
		{
			//t所指就在范围之内 那么把t所指去除 然后继续对这个位置进行调用
			remove(t->data, t);
			remove_bound(x, y, t);
		}
}

int main()
{
	binarysearchtree<int> a;
	a.insert(2);
	a.insert(5);
	a.insert(80);
	a.insert(1);
	a.insert(2);
	a.insert(50);
	a.remove_bound(4,56);
	a.print();
	return 0;
}