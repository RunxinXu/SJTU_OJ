#include <iostream>
#include <stack>

using namespace std;

int Ac(int m, int n)
{
	stack<int> a;
	a.push(m);
	a.push(n);

	while (1)
	{
		n = a.top();
		a.pop();
		if (a.empty()) return n; //剩一个 为结果

		m = a.top();
		a.pop();

		if (m != 0 && n != 0)
		{
			a.push(m - 1);
			a.push(m);
			a.push(n);
		}
		else
		{
			if (m != 0 && n == 0)
			{
				a.push(m - 1);
				a.push(1);
			}
			else a.push(n + 1);
		}
	}
}

//递归本身就是一个栈~ 所以这个非递归用一个栈来实现！妙！

int main()
{


	return 0;
}