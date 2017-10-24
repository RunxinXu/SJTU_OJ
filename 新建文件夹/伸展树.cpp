#include <iostream>

using namespace std;
//伸展树类
//伸展树类的查找和插入 先与BST一样 之后再伸展到根
//而删除就与BST完全一样了
enum type { X, ZIG, ZAG, FALSE };//分别代表伸展节点是当前树的树根，树根的左儿子，树根的右儿子，以及没有找到结点

//用一个枚举类型type来传递信息真的是很精妙了！！！
//伸展时的旋转一般都是两个一组 所以到最后可能需要离变成根节点还差一步！！
//所以公有函数中还是要加以讨论

//总的来说都是四种情况：是根节点 是根节点的儿子 是根节点的左左或右右 是根节点的左右或右左


template<class T>
class splaytree
{
	struct node
	{
		T data;
		node *left, *right;

		node(const T&d, node*l = nullptr, node*r = nullptr) :data(d), left(l), right(r) {};
	};

	node *root;
	
	type find(const T&x, node *&t);
	type insert(const T&x, node*&t);
	void remove(const T&x, node *&t);
	void makeempty(node *t)
	{
		if (t == nullptr) return;
		makeempty(t->left);
		makeempty(t->right);
		delete t;
	}
	void print(node *t)
	{
		if (t == nullptr) return;
		print(t->left);
		cout << t->data << endl;
		print(t->right);
	}
	
	void zigzig(node *&t);
	void zigzag(node *&t);
	void zagzig(node *&t);
	void zagzag(node *&t);
public:
	splaytree(node *t = nullptr) :root(t) {};
	~splaytree() { makeempty(root); }
	void print() { print(root); }
	bool find(const T&x);
	void insert(const T&x);
	void remove(const T&x) { remove(x, root); }
};

template<class T>
void splaytree<T>::remove(const T&x, node* &t) //指针的引用是精髓！！！！
{
	if (t == nullptr) return;
	if (x < t->data) remove(x, t->left);
	else
		if (x > t->data) remove(x, t->right);
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

template<class T>
type splaytree<T>::find(const T&x, node *&t)
{
	type rn;
	if (t == nullptr) return FALSE;  //如果没找到
	if (t->data == x) return X;      //如果这个就是所要找的结点
	if (x > t->data)
	{
		rn = find(x, t->right);
		switch (rn)
		{
		case X:return ZAG;                  //就是t所指结点的右儿子 那么这是一个ZAG 但是不进行旋转！！
			                                //伸展树的旋转一般都是两步的 只有到最后根节点时（公有函数）才可能出现一步的！
		case ZIG:zagzig(t); return X;      //所找的是t所指结点的右儿子的左儿子那么一个zagzig把它选上来 返回就是这个结点的信息
		case ZAG:zagzag(t); return X;      //同上
		case FALSE:return FALSE;           //没找到
		}
	}
	else
	{
		rn = find(x, t->left);;            //与上面类似
		switch (rn)
		{
		case X:return ZIG;
		case ZIG:
		{zigzig(t); return X; }
		case ZAG:
		{zigzag(t); return X; }
		case FALSE:return FALSE;
		}
	}
}
template<class T>
bool splaytree<T>::find(const T&x)
{
	node *tmp;
	type rn = find(x, root);
	//公有为什么还要处理 就是处理那种伸展不到根的（因为说过都是两次两次的）
	switch (rn)
	{
	case X:return true; //就是根节点 不用做其他事
	case ZIG:
	{
		//执行一个单旋转 这里就不单独弄成函数了
		tmp = root->left;
		root->left = tmp->right;
		tmp->right = root;
		root = tmp;
		return true;
	}
	case ZAG:
	{
		//也是一个单旋转
		tmp = root->right;
		root->right = tmp->left;
		tmp->left = root;
		root = tmp;
		return true;
	}
	case FALSE:
		return false;
	}
}

//接下来是zigzig,zigzag,zagzig,zagzag的实现
template<class T>
void splaytree<T>::zigzig(node *&t)
{
	//这个LL情况与AVL一样 但是情况一样操作不一样！！
	//AVL是只执行一个单旋转
	//但是splaytree是两次同一位置的单旋转！！！

	//这里没有写成两次 而是一次到位
	node *tmp = t->left;
	node *tmptmp = t->left->left;
	tmp->left = tmptmp->right;
	t->left = tmp->right;
	tmp->right = t;
	tmptmp->right = tmp;
	t = tmptmp;
}

template<class T>
void splaytree<T>::zigzag(node *&t)
{
	node *tmp = t->left;
	node *tmptmp = tmp->right;

	t->left = tmptmp->right;
	tmp->right = tmptmp->left;
	tmptmp->left = tmp;
	tmptmp->right = t;
	t = tmptmp;
}

template<class T>
void splaytree<T>::zagzig(node *&t)
{
	node *tmp = t->right;
	node *tmptmp = tmp->left;

	t->right = tmptmp->right;
	tmp->left = tmptmp->right;
	tmptmp->right = tmp;
	tmptmp->left = t;
	t = tmptmp;
}
template<class T>
void splaytree<T>::zagzag(node *&t)
{
	node *tmp = t->right;
	node *tmptmp = t->right->right;
	tmp->right = tmptmp->left;
	t->right = tmp->left;
	tmp->left = t;
	tmptmp->left = tmp;
	t = tmptmp;
}

//插入
template<class T>
type splaytree<T>::insert(const T&x, node *&t)
{
	type rn;
	if (t == nullptr)
	{
		t = new node(x);
		return X;
	}
	if (x < t->data)
	{
		rn = insert(x, t->left);
		switch (rn)
		{
		case X:return ZIG;
		case ZIG:zigzig(t); return X;
		case ZAG:zigzag(t); return X;
		}
	}
	else
	{
		rn = insert(x, t->right);
		switch (rn)
		{
		case X:return ZAG;
		case ZIG: {zagzig(t); return X; }
		case ZAG: {zagzag(t); return X; }
		}
	}
	//这个操作基本上就和find的伸展差不多了 其实就是一样
	//因为find是查找+伸展 插入是插入+伸展 其实后面都是伸展 同个过程！！
}

template<class T>
void splaytree<T>::insert(const T&x)
{
	type rn = insert(x, root);
	node*tmp;
	switch (rn)
	{
	case ZIG:
		tmp = root->left;
		root->left = tmp->right;
		tmp->right = root;
		root = tmp;
	case ZAG:
		tmp = root->right;
		root->right = tmp->left;
		tmp->left = root;
		root = tmp;
	}
}
int main()
{
	splaytree<int> hehe;
	hehe.insert(5);
	hehe.insert(25);
	hehe.insert(45);
	hehe.insert(55);
	hehe.insert(15);
	hehe.insert(10);
	hehe.remove(25);
	hehe.print();
	
	
	return 0;
}