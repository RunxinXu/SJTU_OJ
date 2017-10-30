#include <iostream>


using namespace std;

//闭散列表 平方探测法


//亮点一：化平方为乘法
//亮点二：判断素数 结束条件是遍历到 i*i>n 结束
//亮点三：找下一个素数：先变成奇数 之后可以一次+2来找！！！
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
	int load;  //有效元素数 
	int(*key)(const T&x);
	static int defaultkey(const int &k) { return k; }

	void doublespace();
	bool isprime(int n);
	int nextprime(int n);  //扩大数组之后 需要找到下一个是素数作为他的大小！！！！

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

//判断一个数是否为素数的方法！！！！
template<class T>
bool closehashtable<T>::isprime(int n)
{
	if (n == 2 || n == 3) return true;
	if (n == 1 || n % 2 == 0)return false;
	for (int i = 3; i*i <= n; i += 2)         //这个i*i<=n 可以说很骚了！！因为如果一个是i 而另一个如果小于i 那么他应该在之前就被检测出来了！
	{
		if (n%i == 0) return false;
	}
	return true;
}


//这个找下一个素数的方法也挺强  首先把n变成奇数 这样就可以每次+2！！！！提高寻找速度！！！留的一笔！！
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
		pos = (pos + 2 * (++i) - 1) % size;   //化平方为乘 而乘2只是一个移位
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
		if (array[pos].state == 1 && array[pos].data == x) return true;//已经有了
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
