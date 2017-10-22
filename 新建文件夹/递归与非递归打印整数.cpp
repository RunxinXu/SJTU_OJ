#include <iostream>
#include <stack>

using namespace std;

//递归打印整数
void print_digui(int num)
{
	if (num < 10) cout << num;
	else
	{
		print_digui(num / 10);
		cout << num % 10;
	}
}

//非递归打印整数
//用一个栈来实现 不断的将栈顶元素弹出并分解 再压入栈
void print_feidigui(int num)
{
	stack<int> hehe;
	hehe.push(num);
	int tmp;
	while (!hehe.empty())
	{
		tmp = hehe.top();
		hehe.pop();
		if (tmp < 10) cout << tmp;
		else
		{
			hehe.push(tmp % 10);
			hehe.push(tmp / 10);
		}
	}
}
int main()
{
	int a = 123456789;
	print_digui(a);
	cout << endl;
	print_feidigui(a);

	return 0;
}

