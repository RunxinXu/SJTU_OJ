#include <iostream>

using namespace std;
//��չ����
//��չ����Ĳ��ҺͲ��� ����BSTһ�� ֮������չ����
//��ɾ������BST��ȫһ����
enum type { X, ZIG, ZAG, FALSE };//�ֱ������չ�ڵ��ǵ�ǰ��������������������ӣ��������Ҷ��ӣ��Լ�û���ҵ����

//��һ��ö������type��������Ϣ����Ǻܾ����ˣ�����
//��չʱ����תһ�㶼������һ�� ���Ե���������Ҫ���ɸ��ڵ㻹��һ������
//���Թ��к����л���Ҫ��������

//�ܵ���˵��������������Ǹ��ڵ� �Ǹ��ڵ�Ķ��� �Ǹ��ڵ����������� �Ǹ��ڵ�����һ�����


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
void splaytree<T>::remove(const T&x, node* &t) //ָ��������Ǿ��裡������
{
	if (t == nullptr) return;
	if (x < t->data) remove(x, t->left);
	else
		if (x > t->data) remove(x, t->right);
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

template<class T>
type splaytree<T>::find(const T&x, node *&t)
{
	type rn;
	if (t == nullptr) return FALSE;  //���û�ҵ�
	if (t->data == x) return X;      //������������Ҫ�ҵĽ��
	if (x > t->data)
	{
		rn = find(x, t->right);
		switch (rn)
		{
		case X:return ZAG;                  //����t��ָ�����Ҷ��� ��ô����һ��ZAG ���ǲ�������ת����
			                                //��չ������תһ�㶼�������� ֻ�е������ڵ�ʱ�����к������ſ��ܳ���һ���ģ�
		case ZIG:zagzig(t); return X;      //���ҵ���t��ָ�����Ҷ��ӵ��������ôһ��zagzig����ѡ���� ���ؾ������������Ϣ
		case ZAG:zagzag(t); return X;      //ͬ��
		case FALSE:return FALSE;           //û�ҵ�
		}
	}
	else
	{
		rn = find(x, t->left);;            //����������
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
	//����Ϊʲô��Ҫ���� ���Ǵ���������չ�������ģ���Ϊ˵�������������εģ�
	switch (rn)
	{
	case X:return true; //���Ǹ��ڵ� ������������
	case ZIG:
	{
		//ִ��һ������ת ����Ͳ�����Ū�ɺ�����
		tmp = root->left;
		root->left = tmp->right;
		tmp->right = root;
		root = tmp;
		return true;
	}
	case ZAG:
	{
		//Ҳ��һ������ת
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

//��������zigzig,zigzag,zagzig,zagzag��ʵ��
template<class T>
void splaytree<T>::zigzig(node *&t)
{
	//���LL�����AVLһ�� �������һ��������һ������
	//AVL��ִֻ��һ������ת
	//����splaytree������ͬһλ�õĵ���ת������

	//����û��д������ ����һ�ε�λ
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

//����
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
	//������������Ͼͺ�find����չ����� ��ʵ����һ��
	//��Ϊfind�ǲ���+��չ �����ǲ���+��չ ��ʵ���涼����չ ͬ�����̣���
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