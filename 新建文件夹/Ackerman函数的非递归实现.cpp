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
		if (a.empty()) return n; //ʣһ�� Ϊ���

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

//�ݹ鱾�����һ��ջ~ ��������ǵݹ���һ��ջ��ʵ�֣��

int main()
{


	return 0;
}