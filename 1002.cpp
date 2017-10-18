#include <iostream>

using namespace std;

int a, b;
int maze[1000][1000];
int tmp[1000];

int sum_lie(int m, int n)
{
	//������������±�m �����ĵ�n�еĺ�
	int num = 0;
	if (m > 0)
	{
		num = tmp[n] - maze[m - 1][n] + maze[m + a - 1][n];
		//����һ�л����tmp[n]������
		return num;
	}
	//����ǵ�һ��
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
		//��
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