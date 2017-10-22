#include <iostream>
#include <cstring>
#include <stack>

//完全二叉树 所以可以以二叉堆形式组织  用下标来下功夫
//都是利用到了栈
//前中后序 =》 层次 ： 用下标做栈元素 用栈一次找到s从头到尾实际应该放的result中的位置！！
//层次 =》 前中后序 这个就更简单了 就相当于给你一棵树让你遍历而已 只不过不是用递归+指针 而是栈+下标
//其实关键就是知道树的前中后序的非递归遍历用栈如何实现

using namespace std;

struct node
{
	char key;
	int number;
	int order;
};

struct node2
{
	int key;
	int number;

	node2(int k, int n) :key(k), number(n) {};
};

void level_middleorder(char *s,int n)
{
	node* a = new node[n+1];
	stack<node> hehe;
	for (int i = 1;i <= n; ++i)
	{
		a[i].key = s[i];
		a[i].number = 0;
		a[i].order = i;
	}

	hehe.push(a[1]);
	node tmp;

	while (!hehe.empty())
	{
		tmp = hehe.top();
		hehe.pop();
		if (tmp.number == 0)  
		{
			tmp.number++;
			hehe.push(tmp);
			if (tmp.order * 2 <= n) hehe.push(a[tmp.order * 2]);
			continue;
		}
		if (tmp.number == 1)
		{
			cout << tmp.key;
			if (tmp.order * 2 + 1 <= n) hehe.push(a[tmp.order * 2+1]);
			continue;
		}
	}
	delete a;
}

void level_preorder(char *s, int n)
{
	node* a = new node[n + 1];
	stack<node> hehe;
	for (int i = 1; i <= n; ++i)
	{
		a[i].key = s[i];
		a[i].number = 0;
		a[i].order = i;
	}

	hehe.push(a[1]);
	node tmp;

	while (!hehe.empty())
	{
		tmp = hehe.top();
		hehe.pop();
		cout << tmp.key;
		if (tmp.order * 2 + 1 <= n)hehe.push(a[tmp.order * 2 + 1]);
		if (tmp.order * 2 <= n) hehe.push(a[tmp.order * 2]);
		


	}
	delete a;

}

void level_postorder(char *s, int n)
{
	node* a = new node[n + 1];
	stack<node> hehe;
	for (int i = 1; i <= n; ++i)
	{
		a[i].key = s[i];
		a[i].number = 0;
		a[i].order = i;
	}

	hehe.push(a[1]);
	node tmp;

	while (!hehe.empty())
	{
		tmp = hehe.top();
		hehe.pop();
		if (tmp.number == 0)
		{
			tmp.number++;
			hehe.push(tmp);
			if (tmp.order * 2 <= n) hehe.push(a[tmp.order * 2]);
			continue;

		}
		if (tmp.number == 1)
		{
			tmp.number++;
			hehe.push(tmp);
			if (tmp.order * 2 + 1 <= n) hehe.push(a[tmp.order * 2+1]);
			continue;

		}
		if (tmp.number == 2)
		{
			cout << tmp.key;
		}
	}

}

void middleorder_level(char*s, int n)
{
	char* result = new char[n + 1];
	int count = 1;
	result[0] = '0';
	stack<node2> hehe;
	node2 tmp(0,0);
	tmp.key = 1;
	tmp.number = 0;
	hehe.push(tmp);

	while (!hehe.empty())
	{
		tmp = hehe.top();
		hehe.pop();
		if (tmp.number == 0)
		{
			tmp.number++;
			hehe.push(tmp);
			if (tmp.key * 2 <= n) hehe.push(node2(tmp.key * 2, 0));
			continue;
		}
		if (tmp.number == 1)
		{
			result[tmp.key] = s[count];
			count++;
			if (tmp.key * 2 + 1 <= n) hehe.push(node2(tmp.key * 2 + 1, 0));
			continue;
		}

	}
	for (int i = 1; i <= n; ++i) cout << result[i];
	
}

void preorder_level(char*s, int n)
{
	char* result = new char[n + 1];
	int count = 1;
	result[0] = '0';
	stack<node2> hehe;
	node2 tmp(0, 0);
	tmp.key = 1;
	tmp.number = 0;
	hehe.push(tmp);

	while (!hehe.empty())
	{
		tmp = hehe.top();
		hehe.pop();
		result[tmp.key] = s[count];
		count++;
		if (tmp.key * 2 + 1 <= n) hehe.push(node2(tmp.key * 2 + 1, 0));
		if (tmp.key * 2 <= n) hehe.push(node2(tmp.key * 2, 0));
		
	}
	for (int i = 1; i <= n; ++i) cout << result[i];

}

void postorder_level(char*s, int n)
{
	char* result = new char[n + 1];
	int count = 1;
	result[0] = '0';
	stack<node2> hehe;
	node2 tmp(0, 0);
	tmp.key = 1;
	tmp.number = 0;
	hehe.push(tmp);

	while (!hehe.empty())
	{
		tmp = hehe.top();
		hehe.pop();
		if (tmp.number == 0)
		{
			tmp.number++;
			hehe.push(tmp);
			if (tmp.key * 2 <= n) hehe.push(node2(tmp.key * 2, 0));
			continue;

		}
		if (tmp.number == 1)
		{
			tmp.number++;
			hehe.push(tmp);
			if (tmp.key * 2 + 1 <= n) hehe.push(node2(tmp.key * 2 + 1, 0));
			

			continue;
		}
		if (tmp.number == 2)
		{
			result[tmp.key] = s[count];
			count++;
			continue;
 		}
	}
	for (int i = 1; i <= n; ++i) cout << result[i];

}


int main()
{
	int t;
	cin >> t;
	char*order1 = new char[10];
	char *order2 = new char[10];
	char* s = new char[1000000];
	for (int i = 0; i < t; ++i)
	{
		int n;
		cin >> n;//s的长度
		cin >> order1 >> order2;
		s[0] = '0';
		cin >> s+1 ;//可以这么操作

		if (strcmp(order2, "ENCODE") == 0)
		{
			if (strcmp(order1, "INORDER") == 0)
			{
				level_middleorder(s,n);
				cout << endl;
			}
			if (strcmp(order1, "PREORDER") == 0)
			{
				level_preorder(s,n);
				cout << endl;
			}
			if (strcmp(order1, "POSTORDER") == 0)
			{
				level_postorder(s,n);
				cout << endl;
			}
		}
		else
		{
			if (strcmp(order1, "INORDER") == 0)
			{
				middleorder_level(s,n);
				cout << endl;
			}
			if (strcmp(order1, "PREORDER") == 0)
			{
				preorder_level(s,n);
				cout << endl;
			}
			if (strcmp(order1, "POSTORDER") == 0)
			{
				postorder_level(s,n);
				cout << endl;
			}
		}
	}

	return 0;
}