#include <iostream>
#include <vector>
#include <cmath>

//�ְ�Ҫȥ�ܲ��� �о��������ʵ�������� ��Ҳ���ø��� �����˼��
using namespace std;
//�������  ʵ��merge
//��������������� ÿ���������϶ѵ����� ���ڵ�С�ڵ��ڶ���

//!!!!!!!!����ţ�ƣ���������������������//
//��������ͨ�����Ƕ����� �㲻֪�������м��� ������֯��ʽ//
//�� ����-����������������� ������б�����������Բۣ�����

//�ϲ���ʱ�� �����㹻��Ĺ�ģ �����Ƕ����Ƶ�ʱ���������
//enqueue���Ǻ�һ��ֻ��һ������merge��
//dequeue��Ҫ�����и��ڵ�������С���߳�ȥ ֮���ǿ����ͱ�ɺܶ�����������������е�λ�� ֮��merge��


template<class T>
struct node
{
	T key;
	node* left, *right;
	node(const T&k, node*l, node *r) :key(k), left(l), right(r) {};
};
template<class T>
class binaryqueue
{
	
	int size;   
	vector<node*> trees;
	

	node* merge(node*t1, node*t2);
	int capacity() {
		return pow(2, size+1)-1;
	}//���ؿ��Դ�ŵĽ�������ֵ
public:
	binaryqueue(int n = 100)   //nΪԤ�Ƶ�Ԫ�ظ���
	{
		size = int(log(n) / log(2)) + 1;
		trees = new node*[size];
		for (int i = 0; i < size; ++i) trees[i] = nullptr;
	}
	void enqueue(const T&x);
	void dequeue();
	void merge(const binaryqueue&other);
};

template<class T>
node<T>* binaryqueue<T>::merge(node*t1, node*t2)
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

template<class T>
void binaryqueue<T>::merge(const binaryqueue& other)
{
	if (this == &other) return;

	//����ɭ�ֵĺϲ� ÿ��ɭ�ֶ���һ������
    //�ϲ����������ڵ�ǰ��

	size += other.size;
	if (size > capacity())
	{
		//������ǰvector�ܲ��ܴ����
		int old = trees.size();
		int newa = max(trees.size(), other.trees.size()) + 1;
		trees.resize(newa);
		for (int i = old; i < newa; ++i) trees[i] = nullptr;
	} 

	node *carry = nullptr;
	for (int i = 0, j = 1; j <= size+2; i++, j *= 2)   
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
			 other.trees[i] = nullptr;
			 break;
		 case 3://�е�ǰ�ĺ�other��
			 carry = merge(t1, t2);
			 trees[i] = other.trees[i] = nullptr;
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
			 other.trees[i] = nullptr;
			 break;
		 case 7://�е�ǰ�ĺ�other�ĺ�carry��
			 trees[i] = carry;          //carry���� ���������ϲ�����λ
			 carry = merge(trees[i], other.trees[i]);
			 other.trees[i] = nullptr;
			 break;
		 }
	}
	for (int k = ; k < other.trees.size(); ++k) other.trees[k] = nullptr;
	other.size = 0;
	
}
template<class T>
void enqueue(const T&x);
{

}
int main()
{
	
	return 0;
}