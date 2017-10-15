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
		cin >> n >> m;  //n辆火车 栈m  可以为0
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
			//p[j]是现在需要几号开过去
			//num是现在是第几辆车在待命(不包括在栈内的)
			if (p[j] == num)
			{
				num++; continue;
			}
			else
			{
				//不可以直接驶过去
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

