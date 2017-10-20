#include <iostream>

using namespace std;


//-----------***----------------//
//斜堆：斜堆可以看成左堆的简化  同样可以实现merge merge算法也相同 但是
//他不再维护一个npl值 而是在每次merge之后都直接swapnode
template<class T>
struct node
{
	T key;
	node* left, *right;

	node(T value, node*l, node*r) :key(value), left(l), right(r) {};
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

	swapnode(x->left,x->right);   //这就是斜堆的简单粗暴！

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