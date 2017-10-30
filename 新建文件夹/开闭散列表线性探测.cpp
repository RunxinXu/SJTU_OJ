#include <iostream>


using namespace std;

//常用散列函数
//1.直接定址法
//2.除留余数法：取模 常选素数
//3.数字分析法
//4.平方取中法：平方之后取中间几位
//5.折叠法：多位切割成几个低位加起来等等

//闭散列表与开散列表（常用链表）
//对于闭散列表碰撞的解决：
//1.线性探测法：碰撞了就顺序往前探测
//2.二次探测法：探测变成一次加1 2^2 3^2 4^2 ……
//这种方法一般要求表的大小是素数 而且负载因子 也就是非空单元的比例要低于0.5
// 而公式Hi=H0+i*i mod M  Hi-1=H0+(i-1)^2 mod M 相减可以得到 Hi=Hi-1  + (2*i-1)mod M
// 如果出现负载因子超过0.5 那么就需要再散列 把表的规模变成二倍大小


//所以散列表首先要有一个计算的散列函数 同时如果是闭散列表还需要确定一个解决碰撞的方法

template <class T>
class hashtable
{
protected:
	int (*key)(const T&x);  //取出元素x的键并转换成整型 函数指针
	static int defaultkey(const int &k) { return k; }
	//如果是int就不用转咯 直接用
public:
	virtual bool find(const T&x)const = 0;
	virtual bool insert(const T&x) = 0;
	virtual bool remove(const T&x) = 0;
};

//实现一个闭散列表
template<class T>
class closehashtable :public hashtable<T>
{
	struct node
	{
		T data;
		int state;  //当前结点状态 0为空1为有2为已删除
		node() { state = 0; };
	};

	node* array;
	int size;

public:
	closehashtable(int length = 101, int(*f)(const T&x) = defaultkey)
	{
		size = length;
		key = f;   //如果不是整型数 那就要传递一个函数指针！！！
		array = new node[size];
	}
	~closehashtable() { delete[]array; }
	bool find(const T&x)const;
	bool insert(const T&x);
	bool remove(const T&x);
	void rehash(); //再散列
};

template<class T>
bool closehashtable<T>::insert(const T&x)
{
	int initpos, pos;
	initpos = pos = key(x) % size; //使用取模的方法
	do
	{
		if (array[pos].state != 1)
		{
			//如果可以放进去
			array[pos].data = x;
			array[pos].state = 1;
			return true;
		}
		if (array[pos].state == 1 && array[pos].data == x)
			return true;//相同
		pos = (pos + 1) % size; //线性探测法
	} while (pos != initpos);

	return false; //已经没空可以插了
}

template<class T>
bool closehashtable<T>::remove(const T&x)
{
	int initpos, pos;
	initpos = pos = key(x) % size;
	do
	{
		if (array[pos].state == 0) return false;
		if (array[pos].state == 1 && array[pos].data == x)
		{
			array[pos].state = 2; return true;
		}
		pos = (pos + 1) % size;  //继续向前找
	} while (pos != initpos);

	return false;
}

template<class T>
bool closehashtable<T>::find(const T&x) const
{
	int initpos, pos;
	initpos = pos = key(x) % size;
	do
	{
		if (array[pos].state == 0) return false;
		if (array[pos].state == 1 && array[pos].data == x) return true;
		pos = (pos + 1) % size;

	} while (pos != initpos);

	return false;
}

template<class T>
void closehashtable<T>::rehash()
{
	//将表中state为2的真正除去！！
	node*tmp = array;
	array = new node[size];
	
	for (int i = 0; i < size; ++i)
	{
		if (array[i].state == 1) insert(tmp[i].data);
	}
	delete[]tmp;

}

//实现开散列表
//开散列表有一个头结点！！！
template<class T>
class openhashtable :public hashtable<T>
{
	struct node
	{
		T data;
		node *next;
		node(const T&d) :data(d), next(nullptr) {};
		node() :next(nullptr) {};
	};
	node **array; //指针数组
	int size;

public:
	openhashtable(int length = 101, int(*f)(const T&x) = defaultkey)
	{
		size = length;
		key = f;
		array = new node*[size];
		for (int i = 0; i < size; ++i) array[i] = new node;
	}
	~openhashtable()
	{
		node*tmp1,tmp2;
		for (int i = 0; i < size; ++i)
		{
			tmp1 = array[i];
			tmp2 = tmp1->next;
			while (tmp2 != nullptr)
			{
				delete tmp1;
				tmp1 = tmp2;
				tmp2 = tmp2->next;
			}
			delete tmp1;
		}
		delete[]array;
	}
	bool find(const T&x) const;
	bool insert(const T&x);
	bool remove(const T&x);
};

template<class T>
bool openhashtable<T>::insert(const T&x)
{
	int pos;
	node* p;

	pos = key(x) % size;
	p = array[pos]->next;
	//看看是不是已经有了 没有重复元素的话再插入到最前面
	while (p != nullptr && p->data != x) p = p->next;
	if (p == nullptr)
	{
		//插在最前面哦！
		p = new node(x);
		p->next = array[pos]->next;
		array[pos]->next = p;
		return true;
	}
	return false;
}

template<class T>
bool openhashtable<T>::remove(const T&x)
{
	int pos;
	node *p, *q;
	pos = key(x) % size;

	p = array[pos];
	while (p->next != nullptr && p->next->data != x) p = p->next;
	if (p->next == nullptr)
	{
		return false;
	}
	else
	{
		q = p->next;
		p->next = q->next;
		delete q;
		return true;
	}
}

template<class T>
bool openhashtable<T>::find(const T&x) const
{
	int pos = key(x) % size;
	node *p;
	p = array[pos];
	while (p->next && p->next->data != x) p = p->next;
	if (p->next == nullptr) return false;
	else return true;
}
int main()
{
	/*hashtable<int>*p = new closehashtable<int>;
	p->insert(5);
	p->insert(100);
	p->insert(20);
	p->insert(121);
	cout << boolalpha << p->find(121) << endl;
	p->remove(20);
	cout << boolalpha << p->find(121) << endl;
	cout << boolalpha << p->find(20) << endl;*/

	hashtable<int>* p = new openhashtable<int>;
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
