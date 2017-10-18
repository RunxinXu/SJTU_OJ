#include <iostream>

using namespace std;

int a, b;
int maze[1000][1000];
int tmp[1000];

int sum_lie(int m, int n)
{
	//块的行上线是下标m 计算块的第n列的和
	int num = 0;
	if (m > 0)
	{
		num = tmp[n] - maze[m - 1][n] + maze[m + a - 1][n];
		//用上一行缓存的tmp[n]来计算
		return num;
	}
	//如果是第一行
	for (int i = 0; i < a; ++i)
	{
		num += maze[i][n];
	}
	return num;
}

int main()
{
	int l, w;
	int max = -1;
	cin >> l >> w;
	int body = 0;
	for (int i = 0; i < l; ++i)
	{
		for (int j = 0; j < w; ++j) cin >> maze[i][j];
	}
	cin >> a >> b;

	for (int i = 0; i <= l - a; ++i)
	{
		//行
		body = 0;
		for (int m = 0; m < b; m++)
		{
			tmp[m] = sum_lie(i, m);
			body += tmp[m];
		}
		
		if (body > max) max = body;

		for (int j = b; j < w; ++j)
		{
			tmp[j] = sum_lie(i, j);
			body = body + tmp[j] - tmp[j - b];
			if (body > max) max = body;
		}
	}
	cout << max;
	return 0;
}