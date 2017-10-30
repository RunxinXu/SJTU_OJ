#include <iostream>


using namespace std;

//��ɢ�б� ƽ��̽�ⷨ


//����һ����ƽ��Ϊ�˷�
//��������ж����� ���������Ǳ����� i*i>n ����
//������������һ���������ȱ������ ֮�����һ��+2���ң�����
template<class T>
class closehashtable
{
	struct node
	{
		T data;
		int state;
		node() :state(0) {};
	};
	node *array;
	int size;
	int load;  //��ЧԪ���� 
	int(*key)(const T&x);
	static int defaultkey(const int &k) { return k; }

	void doublespace();
	bool isprime(int n);
	int nextprime(int n);  //��������֮�� ��Ҫ�ҵ���һ����������Ϊ���Ĵ�С��������

public:
	closehashtable(int length = 101, int(*f)(const T&x) = defaultkey)
	{
		size = length;
		key = f;
		array = new node[length];
		load = 0;
	}

	closehashtable() { delete[]array;}
	bool find(const T&x)const;
	bool insert(const T&x);
	bool remove(const T&x);
	void rehash();
};

//�ж�һ�����Ƿ�Ϊ�����ķ�����������
template<class T>
bool closehashtable<T>::isprime(int n)
{
	if (n == 2 || n == 3) return true;
	if (n == 1 || n % 2 == 0)return false;
	for (int i = 3; i*i <= n; i += 2)         //���i*i<=n ����˵��ɧ�ˣ�����Ϊ���һ����i ����һ�����С��i ��ô��Ӧ����֮ǰ�ͱ��������ˣ�
	{
		if (n%i == 0) return false;
	}
	return true;
}


//�������һ�������ķ���Ҳͦǿ  ���Ȱ�n������� �����Ϳ���ÿ��+2�����������Ѱ���ٶȣ���������һ�ʣ���
template<class T>
int closehashtable<T>::nextprime(int n)
{
	if (n % 2 == 0) n++;
	while (!isprime(n)) n+=2;   
	return n;
}

template<class T>
void closehashtable<T>::rehash()
{
	node *tmp = array;
	array = new node[size];
	for (int i = 0; i < size; ++i)
		if (tmp[i].state == 1)insert(tmp[i].data);
	delete[]tmp;
}

template<class T>
void closehashtable<T>::doublespace()
{
	node *tmp = array;
	int oldsize = size;
	size = nextprime(oldsize * 2);
	load = oldsize;        //????

	array = new node[size];
	for (int i = 0; i < oldsize; ++i)
		if (tmp[i].state == 1) insert(tmp[i].data);
	delete[]tmp;
}

template<class T>
bool closehashtable<T>::find(const T&x)const
{
	int initpos, pos;
	int i = 0;  

	initpos = pos = key(x) % size;
	do
	{
		if (array[pos].state == 0) return false;
		if (array[pos].state == 1 && array[pos].data == x) return true;
		pos = (pos + 2 * (++i) - 1) % size;   //��ƽ��Ϊ�� ����2ֻ��һ����λ
	} while (pos != initpos);
	return false;
}

template<class T>
bool closehashtable<T>::insert(const T&x)
{
	int initpos, pos;
	int i = 0;
	if (load * 2 >= size) doublespace();
	initpos = pos = key(x) % size;
	do
	{
		if (array[pos].state != 1)
		{
			array[pos].state = 1;
			array[pos].data = x;
			++load;
			return true;
		}
		if (array[pos].state == 1 && array[pos].data == x) return true;//�Ѿ�����
		pos = (pos + 2 * (++i) - 1) % size;

	} while (pos != initpos);
	return false;
}

template<class T>
bool closehashtable<T>::remove(const T&x)
{
	int initpos, pos;
	int i = 0;

	initpos = pos = key(x) % size;
	do
	{
		if (array[pos].state == 0) return false;
		if (array[pos].state == 1 && array[pos].data == x)
		{
			array[pos].state = 2;
			--load;
			return true;
		}
		pos = (pos + 2 * (++i) - 1) % size;
	} while (pos != initpos);

	return false;
}

int main()
{
	closehashtable<int>*p = new closehashtable<int>(101);
	p->insert(5);
	p->insert(100);
	p->insert(20);
	p->insert(121);
	cout << boolalpha << p->find(121) << endl;
	p->remove(20);
	cout << boolalpha << p->find(121) << endl;
	cout << boolalpha << p->find(20) << endl;

	return 0;
}
