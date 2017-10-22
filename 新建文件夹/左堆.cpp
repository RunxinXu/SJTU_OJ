#include <iostream>

using namespace std;


//--------------------****---------------------//
//左堆 ：组织成树 由于不是完全二叉树 所以不能用数组了！

//零路径长Npl(X)：结点X到   一个没有两个儿子的结点  的  最短路径的  长度。这里我们定义没有两个儿子的结点的Npl(x) = 0；Npl(NULL) = -1。
//左堆的结构性质是指：对于堆中的每一个结点X，它的  左儿子的零路径长 要  不小于  其右儿子的零路径长。 即npl（左儿子）》=npl（右儿子）


//左堆关键在于merge merge算法下面已经说了 注意要判断左堆性质是否被破坏以及更新npl值
//而dequeue enqueue都可以通过merge实现
//嗯enqueue相当于 与一个只有一个结点的堆merge
//而dequeue相当于删掉根节点后两个子堆的merge
template<class T>
struct node
{
	T key;
	int npl;//储存npl信息
	node* left, *right;

	node(T value, node*l, node*r) :key(value), left(l), right(r), npl(0) {};
};
template<class T>
class leftheap
{

	node<T> *root; //堆的根节点指针

	void swapnode(node<T> *&x, node<T> *&y); //指针用引用 由于指针本身要改变
	node<T>* merge(node<T> * &x, node<T> *&y);
    
public:
	leftheap() :root(nullptr) {};
	leftheap(const T* data, int size)
	{
		node<T> *tmp;
		for (int i = 0; i < size; ++i)
		{
			tmp = new node<T>(data[i], nullptr, nullptr);
			root = merge(root, tmp);
		}

	}
	void merge(node<T>* other);
	void enqueue(T key);
	T dequeue();
};

template<class T>
void leftheap<T>::swapnode(node<T>*&x, node<T>*&y)
{
	//引用指针的精髓
	node<T> *tmp = x;
	x = y;
	y = tmp;
}


template<class T>
node<T>* leftheap<T>::merge(node<T>*&x, node<T>*&y)
{
	if (x == nullptr) return y;
	if (y == nullptr)return x;

	//合并想法是递归 找出比较小的根节点 然后将较大根节点的那个树
	//与较小根节点的右子树合并
	if (x->key > y->key)
	{
		swapnode(x, y);
	}
	//保证一定是x小于y
	x->right = merge(x->right, y);

	//合并之后要维持左堆的性质 即检查npl
	//如果右边npl大于左边npl 那么交换
	//之后更新npl 根节点npl为右儿子npl+1

	if (x->left == nullptr || x->left->npl < x->right->npl)
	{
		swapnode(x->left, x->right);
	}

	if (x->right == nullptr || x->right == nullptr) x->npl = 0;
	else
		x->npl = x->right->npl + 1;

	return x;
}

template<class T>
void leftheap<T>::merge(node<T>* other)
{
	root = merge(root, other->root);
}

template<class T>
void leftheap<T>::enqueue(T key)
{
	node* tmp = new node(key, nullptr, nullptr);
	root = merge(root, tmp);
}

template<class T>
T leftheap<T>::dequeue()
{
	T tmp = root->key;
	node<T> * a = root;
	root = merge(root->left, root->right);
	delete a;
	return tmp;
}

int main()
{
	int a[] = { 8,10,21,4,3,5,79 };
	leftheap<int> hehe(a, 7);
	for (int i = 0; i < 7; ++i)
	{
		int tmp = hehe.dequeue();
		cout << tmp << endl;

	}

	return 0;
}