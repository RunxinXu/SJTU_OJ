#include <iostream>

using namespace std;
//现在我们来实现一个AVI树 核心还是单旋转与双旋转
//算法详细见笔记图


//简单来说 插入就是需要调整和不需要调整 调整就有LL LR RL RR
//而删除就有
//1.原来平衡删除后不失衡高度也不变
//2.删除后不失衡但高度改变 需要向上检查
//3.删除后失衡 那么也相当于插入时失衡的LL LR RL RR情况
//不同的是有些高度会改变 需要向上检查
template<class T>
class avltree
{
	struct node
	{
		T data;
		node *left;
		node *right;
		int height;

		node(const T&d, node *l = nullptr, node *r = nullptr, int h = 0) :data(d), left(l), right(r), height(h) {};

	};
	node *root;

	void insert(const T&x, node *&t);
	bool remove(const T&x, node *&t);
	void makeempty(node *t);
	bool find(const T&x, node *t);
	int height(node*t)
	{
		return t == nullptr ? -1 : t->height;
	}
	void LL(node *&t);
	void RR(node *&t);
	void LR(node *&t);
	void RL(node *&t);
	//这里是指插入的位置相对失衡结点的位置
	int max(int a, int b) { return a > b ? a : b; }
	void print(node *t)
	{
		if (t == nullptr) return;
		print(t->left);
		cout << t->data << endl;
		print(t->right);
	}
public:
	avltree(node *t = nullptr) { root = t; }
	~avltree() { makeempty(root); }
	bool find(const T&x)
	{
		return find(x, root);
	}
	void insert(const T&x)
	{
		insert(x, root);
	}
	void remove(const T&x)
	{
		remove(x, root);
	}
	void print()
	{
		print(root);
	}

};

template<class T>
bool avltree<T>::find(const T&x, node *t)
{
	if (t == nullptr) return false;
	if (x == t->data) return true;
	if (x < t->data) return find(x, t->left);
	else
		return find(x, t->right);
}

template<class T>
void avltree<T>::makeempty(node *t)
{
	if (t == nullptr) return;
	makeempty(t->left);
	makeempty(t->right);
	delete t;

}

template<class T>
void avltree<T>::insert(const T&x, node*&t)
{    //在空树中插入
	if (t == nullptr) t = new node(x, nullptr, nullptr, 0);
	else
	{
		//对于x==t->data 的情况 连处理都没有 反正不用管他 他已经在那了！！
		if (x < t->data)
		{
			insert(x,t->left);
			if (height(t->left) - height(t->right) == 2) //t失衡
			{
				if (x < t->left->data) LL(t);   
				//插入结点在失衡结点t的左儿子的左子树上！！注意是儿子的子树 不是儿子的儿子！！不一定是儿子的儿子！！
				//那么此时是LL情况 进行一个单旋转
				else LR(t); //此时插入结点在失衡结点t的左儿子的右子树上 进行双旋转
				//注意不可能出现x==t->left->data ！！！ 这样不可能height(t->left) - height(t->right) == 2
			}
		}
		else
		{
			if (x > t->data)
			{
				insert(x, t->right);
				if (height(t->right) - height(t->left) == 2)
				{
					if (x > t->right->data) RR(t);
					else RL(t);
				}
			}
		}
	}
	//t->height = max(height(t->left), height(t->right)) + 1;//更新高度值 （和更新左堆npl值一样记得及时维护！！）

}

template<class T>
void avltree<T>::LL(node *&t)
{
	node *tmp = t->left;
	t->left = tmp->right;
	tmp->right = t;
	//记得更新高度变了的结点的height值
	tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
	t->height = max(height(t->left), height(t->right)) + 1;
	
	t = tmp;
	
}

template<class T>
void avltree<T>::RR(node *&t)
{
	node *tmp = t->right;
	t->right = tmp->left;
	tmp->left = t;
	tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
	t->height = max(height(t->left), height(t->right)) + 1;

	t = tmp;

}

template<class T>
void avltree<T>::LR(node *&t)
{
	RR(t->left); //双旋转第一步和RR情况一样 注意必须传t->left！！ 因为是引用 传tmp就串不起来了！！！
	LL(t);
}

template<class T>
void avltree<T>::RL(node *&t)
{
	LL(t->right);
	RR(t);
}

template<class T>
bool avltree<T>::remove(const T&x, node *&t)   //这里的bool不是表示删除是否成功 而是是否需要向上继续调整！！！
{
	bool stop = false;
	int subtree = 0; //subtree是1表示删除的是左子树 2为右子树

	if (t == nullptr) return true;  //没啥事做 也就不会引起父节点失衡 所以不用上溯调整 
	if (x < t->data)
	{
		stop = remove(x, t->left);
		subtree = 1;
	}
	else
	{
		if (x > t->data)
		{
			stop = remove(x, t->right);
			subtree = 2;
		}
		else
		{
			//如果t所指就是要删除的
			if (t->left && t->right)//如果有两个儿子 做法和二叉查找树一样
			{
				node *tmp = t->right;
				while (tmp->left) tmp = tmp->left;
				t->data = tmp->data;
				stop = remove(x, t->right);
				subtree = 2;
			}
			else
			{
				//对于删除的是叶子结点或者是只有一个儿子的结点 也和普通二叉树一样
				//但是可能会引起父节点的失衡 因此返回false
				node *old = t;
				t = (t->left) ? t->left : t->right;
				delete old;
				return false;
				
			}
		}
	}

	if (stop) return true;
	int bf;
	//subtree是左是右相对的是t所指的结点
	//然后一直递归向下至底 之后向上调整 一旦过程有了true 他就向上都是true不用调整了！！
	switch (subtree)
	{
		//此时的t的子树的各个height都是已经更新过的
	case 1: //如果删除的点在t所指结点的左子树
		bf = height(t->left) - height(t->right) + 1;
		if (bf == 0) return true;  //原来平衡现在删去一个 高度不变！不用上溯修改
		if (bf == 1) return false;//删去了较高的子树中的 高度减少 需要上溯修改
		if (bf == -1)
		{
			//删除较矮子树的 需要旋转
			int bfr = height(t->right->left) - height(t->right->right);
			switch (bfr)
			{
			case 0://如果t另一边的儿子平衡度为0只需要一个单旋 之后不用上溯修改
				RR(t);
				return true;
			case -1://如果t另一边的儿子平衡度和t一样 同样只需要一个单旋 但是高度改变 需要上溯修改
				RR(t);
				return false;
			case 1://如果t另一边的儿子平衡度和t相反 那么需要双旋 且同时高度改变 需要上溯修改
				RL(t);
				return false;
			}
		}
		break;
	case 2://删除的结点在t所指结点的右子树
		bf = height(t->left) - height(t->right) - 1;
		if (bf == 0) return true;
		if (bf == -1) return false;
		if (bf == 1)
		{
			int bfr = height(t->left->left) - height(t->left->right);
			switch (bfr)
			{
			case 0:
				LL(t);
				return true;
			case 1:
				LL(t);
				return false;
			case -1:
				LR(t);
				return false;
			}
		}

	}

}

int main()
{
	avltree<int> hehe;
	hehe.insert(1);
	hehe.insert(100);
	hehe.insert(50);
	hehe.insert(40);
	hehe.insert(200);
	hehe.insert(8);
	hehe.remove(50);
	hehe.print();
	
	
	return 0;
}