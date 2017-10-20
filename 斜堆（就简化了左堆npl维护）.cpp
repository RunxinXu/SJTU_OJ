#include <iostream>

using namespace std;


//-----------***----------------//
//б�ѣ�б�ѿ��Կ�����ѵļ�  ͬ������ʵ��merge merge�㷨Ҳ��ͬ ����
//������ά��һ��nplֵ ������ÿ��merge֮��ֱ��swapnode
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

	node<T> *root; //�ѵĸ��ڵ�ָ��

	void swapnode(node<T> *&x, node<T> *&y); //ָ�������� ����ָ�뱾��Ҫ�ı�
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
	//����ָ��ľ���
	node<T> *tmp = x;
	x = y;
	y = tmp;
}


template<class T>
node<T>* leftheap<T>::merge(node<T>*&x, node<T>*&y)
{
	if (x == nullptr) return y;
	if (y == nullptr)return x;

	//�ϲ��뷨�ǵݹ� �ҳ��Ƚ�С�ĸ��ڵ� Ȼ�󽫽ϴ���ڵ���Ǹ���
	//���С���ڵ���������ϲ�
	if (x->key > y->key)
	{
		swapnode(x, y);
	}
	//��֤һ����xС��y
	x->right = merge(x->right, y);

	swapnode(x->left,x->right);   //�����б�ѵļ򵥴ֱ���

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