#include <iostream>


using namespace std;

//背包问题
//状态方程见图片笔记

int max(int i, int j)
{
	return (i < j) ? j : i;
}

void zeroonepack(int n, int v, int *weight, int *value)
{
	int **f = new int*[n+1];
	for (int i = 0; i < n+1; ++i)
	{
		f[i] = new int[v+1];
		for (int j = 0; j < v+1; ++j)
			f[i][j] = 0;
	}
	//空出一行一列作为初始条件

	for (int i = 1; i < n + 1; ++i)
	{
		for (int j = 1; j < v + 1; ++j)
		{
			if (j < weight[i - 1]) //已经放不下了  防止数组越界
				f[i][j] = f[i - 1][j];
			else
			{
				f[i][j] = max(f[i - 1][j], f[i - 1][j - weight[i-1]] + value[i-1]);  //这就是状态转移方程
			}
		}
	}
	cout << f[n][v];
}

void completepack(int n, int v, int *weight, int *value)
{
	int **f = new int*[n + 1];
	for (int i = 0; i < n + 1; ++i)
	{
		f[i] = new int[v + 1];
		for (int j = 0; j < v + 1; ++j)
			f[i][j] = 0;
	}
	//空出一行一列作为初始条件

	for (int i = 1; i < n + 1; ++i)
	{
		for (int j = 1; j < v + 1; ++j)
		{
			f[i][j] = f[i - 1][j];
			for (int k = 0; k * weight[i-1]<=j; ++k)
			{
				if (f[i][j] < f[i - 1][j - k*weight[i - 1]] + value[i - 1] * k)
					f[i][j] = f[i - 1][j - k*weight[i - 1]] + value[i - 1] * k;
			}
		}
	}
	cout << f[n][v];
}


void multiplepack(int n, int v, int *weight, int *value,int *num)
{
	int **f = new int*[n + 1];
	for (int i = 0; i < n + 1; ++i)
	{
		f[i] = new int[v + 1];
		for (int j = 0; j < v + 1; ++j)
			f[i][j] = 0;
	}
	//空出一行一列作为初始条件

	for (int i = 1; i < n + 1; ++i)
	{
		for (int j = 1; j < v + 1; ++j)
		{
			f[i][j] = f[i - 1][j];
			for (int k = 0; k*weight[i - 1] <= j && k <= num[i - 1]; ++k)
			{
				if(f[i][j] < f[i - 1][j - k*weight[i - 1]] + value[i - 1] * k)
					f[i][j] = f[i - 1][j - k*weight[i - 1]] + value[i - 1] * k;
			}
		}
	}
	cout << f[n][v];
}


int main()
{
	int weight[] = { 5,4,7,2,6 };
	int value[] = { 12,3,10,3,6 };
	int num[] = { 2,4,1,5,3 };
	multiplepack(5, 15, weight, value,num);

	return 0;
	
}