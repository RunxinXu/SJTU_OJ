#include <cstdio>

using namespace std;


int main()
{

	int n;
	scanf("%d", &n);
	int *f = new int[n];
	int *a = new int[n];
	int *g = new int[n];
	int ans1 = 0;
	int ans2 = 0;
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
	}

	for (int i = 0; i < n; ++i)
	{
		f[i] = 1;
		g[i] = 1;
	}
	for (int i = 1; i < n; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (a[j] >= a[i] && f[j] + 1 > f[i])
				f[i] = f[j] + 1;
			if (a[j]<a[i] && g[i] < g[j] + 1)
		        g[i] = g[j] + 1;
		}
		if (f[i] > ans1) ans1 = f[i];
		if (g[i] > ans2) ans2 = g[i];
	}

	printf("%d", ans1);
	printf("\n");
	printf("%d", ans2);
	

	//上面是解决第一个问题 其实就是一个LIS问题 小case 动态规划
	

	

	//上面这个解决需要多少个LIS来覆盖全部
	//这里就厉害了 它求的是最长上升子序列的长度
	//有什么卵联系？？
	//有的！！！！ 离散数学 偏序集与dilworth定理！！！
	//具体可以搜 dilworth定理 偏序集 链 反链
	//本题链 是 >= 关系 
	//而反链是 < 关系 因其不可比较 

	//最长反链长度=链数量！！


	return 0;
}




