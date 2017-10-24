#include <iostream>

using namespace std;
//����������ʵ��һ��AVI�� ���Ļ��ǵ���ת��˫��ת
//�㷨��ϸ���ʼ�ͼ


//����˵ ���������Ҫ�����Ͳ���Ҫ���� ��������LL LR RL RR
//��ɾ������
//1.ԭ��ƽ��ɾ����ʧ��߶�Ҳ����
//2.ɾ����ʧ�⵫�߶ȸı� ��Ҫ���ϼ��
//3.ɾ����ʧ�� ��ôҲ�൱�ڲ���ʱʧ���LL LR RL RR���
//��ͬ������Щ�߶Ȼ�ı� ��Ҫ���ϼ��
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
	//������ָ�����λ�����ʧ�����λ��
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
{    //�ڿ����в���
	if (t == nullptr) t = new node(x, nullptr, nullptr, 0);
	else
	{
		//����x==t->data ����� ������û�� �������ù��� ���Ѿ������ˣ���
		if (x < t->data)
		{
			insert(x,t->left);
			if (height(t->left) - height(t->right) == 2) //tʧ��
			{
				if (x < t->left->data) LL(t);   
				//��������ʧ����t������ӵ��������ϣ���ע���Ƕ��ӵ����� ���Ƕ��ӵĶ��ӣ�����һ���Ƕ��ӵĶ��ӣ���
				//��ô��ʱ��LL��� ����һ������ת
				else LR(t); //��ʱ��������ʧ����t������ӵ��������� ����˫��ת
				//ע�ⲻ���ܳ���x==t->left->data ������ ����������height(t->left) - height(t->right) == 2
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
	//t->height = max(height(t->left), height(t->right)) + 1;//���¸߶�ֵ ���͸������nplֵһ���ǵü�ʱά��������

}

template<class T>
void avltree<T>::LL(node *&t)
{
	node *tmp = t->left;
	t->left = tmp->right;
	tmp->right = t;
	//�ǵø��¸߶ȱ��˵Ľ���heightֵ
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
	RR(t->left); //˫��ת��һ����RR���һ�� ע����봫t->left���� ��Ϊ������ ��tmp�ʹ��������ˣ�����
	LL(t);
}

template<class T>
void avltree<T>::RL(node *&t)
{
	LL(t->right);
	RR(t);
}

template<class T>
bool avltree<T>::remove(const T&x, node *&t)   //�����bool���Ǳ�ʾɾ���Ƿ�ɹ� �����Ƿ���Ҫ���ϼ�������������
{
	bool stop = false;
	int subtree = 0; //subtree��1��ʾɾ������������ 2Ϊ������

	if (t == nullptr) return true;  //ûɶ���� Ҳ�Ͳ������𸸽ڵ�ʧ�� ���Բ������ݵ��� 
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
			//���t��ָ����Ҫɾ����
			if (t->left && t->right)//������������� �����Ͷ��������һ��
			{
				node *tmp = t->right;
				while (tmp->left) tmp = tmp->left;
				t->data = tmp->data;
				stop = remove(x, t->right);
				subtree = 2;
			}
			else
			{
				//����ɾ������Ҷ�ӽ�������ֻ��һ�����ӵĽ�� Ҳ����ͨ������һ��
				//���ǿ��ܻ����𸸽ڵ��ʧ�� ��˷���false
				node *old = t;
				t = (t->left) ? t->left : t->right;
				delete old;
				return false;
				
			}
		}
	}

	if (stop) return true;
	int bf;
	//subtree����������Ե���t��ָ�Ľ��
	//Ȼ��һֱ�ݹ��������� ֮�����ϵ��� һ����������true �������϶���true���õ����ˣ���
	switch (subtree)
	{
		//��ʱ��t�������ĸ���height�����Ѿ����¹���
	case 1: //���ɾ���ĵ���t��ָ����������
		bf = height(t->left) - height(t->right) + 1;
		if (bf == 0) return true;  //ԭ��ƽ������ɾȥһ�� �߶Ȳ��䣡���������޸�
		if (bf == 1) return false;//ɾȥ�˽ϸߵ������е� �߶ȼ��� ��Ҫ�����޸�
		if (bf == -1)
		{
			//ɾ���ϰ������� ��Ҫ��ת
			int bfr = height(t->right->left) - height(t->right->right);
			switch (bfr)
			{
			case 0://���t��һ�ߵĶ���ƽ���Ϊ0ֻ��Ҫһ������ ֮���������޸�
				RR(t);
				return true;
			case -1://���t��һ�ߵĶ���ƽ��Ⱥ�tһ�� ͬ��ֻ��Ҫһ������ ���Ǹ߶ȸı� ��Ҫ�����޸�
				RR(t);
				return false;
			case 1://���t��һ�ߵĶ���ƽ��Ⱥ�t�෴ ��ô��Ҫ˫�� ��ͬʱ�߶ȸı� ��Ҫ�����޸�
				RL(t);
				return false;
			}
		}
		break;
	case 2://ɾ���Ľ����t��ָ����������
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