#include <iostream>

using namespace std;

//计数排序 时间复杂度O(n) 空间复杂度O(n)
//稳定排序！！！为了实现稳定 这就是a数组是从后面向前面遍历的原因啊！！！
template<class T>
void countsort(T a[], int size,int m) //数据从0到m
{
	T*b=new T[size]; //储存排序好的
	T*c=new T[m + 1];  //打表  其实本来就相当于打表之后查表 以空间换时间
	for (int i = 0; i < m + 1; ++i) c[i] = 0;

	//统计每个数出现的次数
	for (int i = 0; i < size; ++i)
	{
		c[a[i]]++;  
	}

	//处理表 使其数据表示 小于等于下标的数的个数
	for (int i = 1; i < m + 1; ++i)
	{
		c[i] = c[i - 1] + c[i];
	}

	for (int i = size - 1; i >= 0; --i)
	{
		//扫描A 把每个数查表后放到合适的位置
		T value = a[i];
		int pos = c[a[i]] - 1;
		b[pos] = value;
		c[a[i]]--;  //放了一个之后记得从表中去掉 这样可以处理如果有数据重复的时候可以继续放下去不同的位置 这个技巧很强哦！！
	}
	delete[]c;
	for (int i = 0; i < size; ++i) a[i] = b[i];
	delete[]b;
}

struct node
{
	int data;
	node* next;
	node() :next(nullptr) {};
	node(int data) :data(data), next(nullptr) {};
};
//基数排序 从低位开始 放进对应袋 之后串起来 再按顺序放第二位 直至高位结束
//组织成链表
template<class T>
void bucketsort(node *&p, int d)
{
	//p是数据链表头 d是最大的位数
	node *bucket[10], *last[10], *tail; //last是每个bucket的工作指针
	int i, j, k, base = 1;

	for (i = 1; i <= d; ++i)
	{
		for (j = 0; j <= 9; ++j) bucket[j] = last[j] = nullptr; //初始化每个bucket
		while (p != nullptr)
		{
			k = p->data / base % 10; //当前所排位数对应的数字
			if (bucket[k] == nullptr) bucket[k] = last[k] = p;
			else last[k]->next = p;
			p = p->next; //下一位
		}
		p = nullptr;
		//接下来串起来
		for (j = 9; j >= 0; --j)
		{
			if (bucket[j] == nullptr) continue;
			if (p == nullptr) p = bucket[j];
			else tail->next = bucket[j];
			tail = last[j];  //不用管中间 我只要头尾就够串起来了 
		}
		tail->next = nullptr;
		base *= 10;
	}
}




int main()
{
	int a[] = { 2,1,5,3,6,9,5,5,4,1,2,3 };
	countsort(a, 12, 9);
	for (int i = 0; i < 12; ++i) cout << a[i] << endl;

	
	return 0;
}