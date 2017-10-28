#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;
//�������  ʵ��merge
//��������������� ÿ���������϶ѵ����� ���ڵ�С�ڵ��ڶ���

//!!!!!!!!����ţ�ƣ���������������������//
//��������ͨ�����Ƕ����� �㲻֪�������м��� ������֯��ʽ//
//�� ����-����������������� ������б�����������Բۣ�����

//�ϲ���ʱ�� �����㹻��Ĺ�ģ �����Ƕ����Ƶ�ʱ���������
//enqueue���Ǻ�һ��ֻ��һ������merge��
//dequeue��Ҫ�����и��ڵ�������С���߳�ȥ ֮���ǿ����ͱ�ɺܶ�����������������е�λ�� ֮��merge��



struct node
{
	int key;
	node* left, *right;
	node(const int&k, node*l, node *r) :key(k), left(l), right(r) {};
};
class binaryqueue
{
	
public:
	int size;
	vector<node*> trees;
	node* merge(node*t1, node*t2);

	binaryqueue(int n = 1)   
	{
		size = n;
		trees.resize(size);
		trees.reserve(size * 2);
		for (int i = 0; i < size; ++i) trees[i] = nullptr;
	}
	void insert(const int&x);
	void delete_min();
	void merge(const binaryqueue&other);
	int get_min_pos();
	int get_min()
	{
		int pos = get_min_pos();
		return trees[pos]->key;
	}
};
node* binaryqueue::merge(node*t1, node*t2)
{

	//�ϲ�������
	//�㷨˼���� ���ڵ�Ƚϴ���������Ϊ���ڵ�Ƚ�С���������� ������ֱ������
	if (t2->key < t1->key) return merge(t2, t1);
	//��֤t2�ϲ�Ϊt1��������

	//�ϲ� �� �Ժ����ֵ�����ά��
	t2->right = t1->left;
	t1->left = t2;
	return t1;

}

void binaryqueue::merge(const binaryqueue& other)
{
	if (this == &other) return;
	if (other.size == 0) return;

	//����ɭ�ֵĺϲ� ÿ��ɭ�ֶ���һ������
	//�ϲ����������ڵ�ǰ��
	if (other.size > size)
	{
		size = other.size;
	}
	size++;  //�����տ��Խ�λ��
	if(size>trees.size()) trees.resize(size);

	node *carry = nullptr;
	for (int i = 0;i<size;++i)
	{
		node *t1 = trees[i];
		node *t2 = (i < other.trees.size()) ? other.trees[i] : nullptr;

		int whichcase = t1 == nullptr ? 0 : 1;
		whichcase += t2 == nullptr ? 0 : 2;
		whichcase += carry == nullptr ? 0 : 4;
		//���ڸպ�8����� ���Կ��Բ�ȡ�����Ƶ���ʽ���ж�

		switch (whichcase)
		{
		case 0:  //û����
		case 1:break;  //ֻ�е�ǰ��
		case 2://ֻ��other��
			trees[i] = other.trees[i];
			//other.trees[i] = nullptr;
			break;
		case 3://�е�ǰ�ĺ�other��
			carry = merge(t1, t2);
			trees[i] = nullptr;
			//other.trees[i] = nullptr;
			break;
		case 4://ֻ��carry
			trees[i] = carry;
			carry = nullptr;
			break;
		case 5://�е�ǰ�ĺͽ�λ��
			carry = merge(carry, trees[i]);
			trees[i] = nullptr;
			break;
		case 6://��other�ĺͽ�λ��
			carry = merge(carry, other.trees[i]);
			//other.trees[i] = nullptr
			break;
		case 7://�е�ǰ�ĺ�other�ĺ�carry��
			trees[i] = carry;          //carry���� ���������ϲ�����λ
			carry = merge(trees[i], other.trees[i]);
			//other.trees[i] = nullptr;
			break;
		}
	}
	//for (int k = ; k < other.trees.size(); ++k) other.trees[k] = nullptr;
	//other.size = 0;
	while (trees[size - 1] == nullptr) --size;
}
void binaryqueue::insert(const int&x)
{
	binaryqueue tmp(1);
	tmp.trees[0] = new node(x,nullptr,nullptr);
	binaryqueue::merge(tmp);
}

int binaryqueue::get_min_pos()
{
	int min_pos = 0;
	while (trees[min_pos] == nullptr) min_pos++;
	int min = trees[min_pos]->key;
	for (int i = min_pos+1; i < size; ++i)
	{
		if (trees[i] && trees[i]->key < min)
		{
			min = trees[i]->key;
			min_pos = i;
		}
	}
	return min_pos;
}

void binaryqueue::delete_min()
{
	int pos = get_min_pos();
	//ɾ��֮��������0--pos-1����
	binaryqueue tmp(pos);
	node* p = trees[pos]->left;
	for (int i = pos - 1; i >= 0; --i)
	{
		tmp.trees[i] = p;
		p = p->right;
	}
	trees[pos] = nullptr;
	binaryqueue::merge(tmp);

}
int main()
{
	int m;
	cin >> m;
	char *p = new char[10];
	int tmp;
	binaryqueue hehe(0);
	for (int i = 0; i < m; ++i)
	{
		cin >> p;
		if (strcmp(p, "insert") == 0)
		{
			cin >> tmp;
			hehe.insert(tmp);
		}
		if (strcmp(p, "delete") == 0)
		{
			hehe.delete_min();
		}
		if (strcmp(p, "min") == 0)
		{
			cout << hehe.get_min() << endl;
		}
	}
	delete []p;
	return 0;
}