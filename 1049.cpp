#include <iostream>
#include<stack>


using namespace std;


int main()
{
	
	int a;
	cin >> a;
	bool* xixi = new bool[a];
	
	for (int i = 0; i < a; ++i)
	{
		int n, m;
		cin >> n >> m;  //n���� ջm  ����Ϊ0
		stack<int> hehe;
		int *p = new int[n];
		int flag = 0;
		for (int j = 0; j < n; ++j)
		{
			cin >> p[j];
		}
		int num = 0;
		for (int j = 0; j < n; ++j)
		{
			//p[j]��������Ҫ���ſ���ȥ
			//num�������ǵڼ������ڴ���(��������ջ�ڵ�)
			if (p[j] == num)
			{
				num++; continue;
			}
			else
			{
				//������ֱ��ʻ��ȥ
				if (!hehe.empty()&&hehe.top() == p[j])
				{
					hehe.pop();
					continue;
				}
				else
				{
						while(hehe.size() <= m && num!=p[j])
						{
							hehe.push(num);
							num++;
						}
						if (hehe.size() > m)
						{
							flag = 1;
							break;
						}
						else
						{
							num++;
							continue;
						}
				
				}
			}
		}
		if (flag)
		{
			xixi[i] = false;
			delete[]p;
			continue;
		}
		else
		{
			xixi[i] = true;
			delete[]p;
			continue;
		}
	}

	for (int i = 0; i < a; ++i)
	{
		if (xixi[i]) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	delete[]xixi;

	return 0;
}

