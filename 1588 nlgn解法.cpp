#include <cstdio>


int binary_search(int *b, int num, int right)
{
	if (right == -1) return 0;

	int left = 0;
	int middle;
	while (left < right)
	{
		middle = (left + right) / 2;
		if (num > b[middle]) left = middle + 1;
		else
			if (num == b[middle]) return middle;
			else  right = middle - 1;
	}
	if (num > b[left]) return left + 1;
	else return left;
}
int binary_search_second(int *b, int num, int right)
{
	if (right == -1) return 0;

	int left = 0;
	int middle;
	while (left < right)
	{
		middle = (left + right) / 2;
		if (num < b[middle]) left = middle + 1;
		else
			if (num == b[middle]) return middle;
			else  right = middle - 1;
	}
	if (num < b[left]) return left + 1;
	else return left;
}

int main()
{

	int n;
	scanf("%d", &n);
	int *f = new int[n];
	int *a = new int[n];
	int ans1 = 0;
	int ans2 = 0;
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
	}

	int k = -1;
	int count = 0;
	for (int i = 0; i < n; ++i) f[i] = -1;
	for (int i = 0; i < n; ++i)
	{
		int position = binary_search_second(f, a[i], k);
		//如果相等 那么同样插进该位置 不破坏性质 
		if (f[position] == -1)
		{
			f[position] = a[i];
			k = position;
		}
		else {
			if (f[position] == a[i]) count++;
			if (f[position] < a[i])
				f[position] = a[i];
			
		}
	}
	printf("%d",count);
	ans1 = k + 1+ count;


	//上面是解决第一个问题 其实就是一个LIS问题 小case 动态规划

	k = -1;
	for (int i = 0; i < n; ++i) f[i] = -1;
	for (int i = 0; i < n; ++i)
	{
		int position = binary_search(f, a[i], k);
		//如果相等 那么同样插进该位置 不破坏性质 
		if (f[position] == -1)
		{
			f[position] = a[i];
			k = position;
		}
		else
			if (f[position] > a[i])
				f[position] = a[i];
	}

	ans2 = k + 1;


	printf("%d", ans1);
	printf("\n");
	printf("%d", ans2);
	


	

	

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





