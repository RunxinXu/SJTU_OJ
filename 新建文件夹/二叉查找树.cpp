#include <iostream>

using namespace std;
//ʵ����һ����ͨ�Ķ����������
//���������� ���� ���� ɾ�� ����ɾ����ǰ�������� ��Ҳ���� һ�㶼�õݹ����
//����������ɾ�� lessthan morethan bound �ĺ��� �㷨Ҳͦ�����
//���ڲ���  ���� ɾ�� �ķǵݹ�ʵ�� �뵽��ջ ������ջ�Ļ� Ҫ��parent�ǳ��� ���Ի���ֱ����
//���Ҳ��뻹�Ƚϼ� ɾ����ʱ���Ҫע��ά����ɾ����parent��
//��Ϊ�ݹ�ʱ�������һ��ָ���������ʵ���޸�parent����
//Ȼ������Ƿǵݹ��û���� ����һ��Ҫʱ��ע������ҵ�����parent�����޸ģ���

//��ţ�ƵĻ���ָ������ã�����
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
	bool check() const; //����Ƿ�Ϊ���Ҷ�����

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
void binarysearchtree<T>::insert(const T&x, node* &t)  //���ָ��������ǹؼ� ��Ϊָ��ĸı���Ҫ���ֻط��صĵط��ģ���
{
	if (t == nullptr) t = new node(x, nullptr, nullptr);
	else
	{
		if (x < t->data) insert(x, t->left);
		else
			if (x > t->data) insert(x, t->right);
		//x==t->data���ô��� �����Ѿ����� �����Զ��жϷ��ؼ���
	}
}

template<class T>
void binarysearchtree<T>::remove(const T&x, node* &t) //ָ��������Ǿ��裡������
{
	if (t == nullptr) return;
	if (x < t->data) remove(x, t->left);
	else
		if (x > t->data) remove(x, t-> right);
		else
		{
			//t��ָ������Ҫɾ���Ľ��
			//�������Ҷ�ӽ����ôֱ��ɾ��
			//�����ֻ��һ������ ��ô���Ӵ�����
			//��������������� �ҵ�����������С�Ľ������� ��ɾ���Ǹ���С�Ľ��

			if (!t->left && !t->right)
			{
				//���û�ж���
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
						//�������������
						node *tmp = t->right;
						while (tmp->left) tmp = tmp->left;
						t->data = tmp->data;
						remove(tmp->data, t->right);
						//���������ܿӣ�����
						//���ﲻ����remove(tmp->data,tmp)��Ϊtmpָ�����ⲿ�� ���������ڲ�ָ��
						//��ָ���õ������� ���tmp����ûʲô���ã�����û������������666������
					}
				}
			}
		}
}


//����Ƿ񱣳ֶ�����������ʷ�����
//����������Ƿ���� �����������ֵ ����������Ƿ���� ����������Сֵ
//�����������һ�������� �������������ֵ���ڸ�ֵ ������������СֵС�ڸ�ֵ ����false
//����true
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
	else min = t->data;     //�ؼ�������  ����������� �ǿ϶��Ǵ����������ص�min��С
	if (t->right)
	{
		flag = check(t->right, min, max);
		if (!flag || min < t->data) return false;
	}
	else max = t->data; //ͬ�ϣ�
	return true;

}

//���еĺ�˽�е�check���������� ˽�еĻ�Ҫά��min max �����Ϸ���
//�����е�ֻ��Ҫ�þ����ˣ�����


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
	//���x��t��ָ��㻹С ��ô�ݹ�������
	if (x <= t->data) remove_less_than(x, t->left);  //��Ϊ��ɾ����xС������t��ָ�Ĳ�����ɾ����
	else
	{
		//t������������Ҳ�е�Ҫɾ ������ɾ����ߵĺ�t��ָ��
		//Ȼ�������t�ݹ����
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

	//˼�����ͬ��
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
	//���t��ָ���С��x���ߴ���y ��ô�������ݹ����
	if (t->data < x) remove_bound(x, y, t->right);
	else
		if (t->data > y) remove_bound(x, y, t->left);
		else
		{
			//t��ָ���ڷ�Χ֮�� ��ô��t��ָȥ�� Ȼ����������λ�ý��е���
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