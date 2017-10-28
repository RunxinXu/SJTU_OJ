#include <cstdio>
#include <iostream>

using namespace std;


//LIS 最长递增序列 
//动态规划解法 O(n^2)
//设f(i) 表示以下标i 结尾的最长递增序列长度  =============》状态
//状态转移方程： f(i)= max( f(j)+1 ) if ( j < i && a[j] < a[i] )

/*int main()
{

	int f[10000000];
	int a[10000000];
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);

	}
	f[0] = 1;
	int m = 1;
	for (int i = 1; i < n; ++i)
	{
		f[i] = 1;
		for (int j = 0; j < i; ++j)
		{
			if (a[j] < a[i] && f[j] + 1>f[i]) f[i] = f[j] + 1;

		}
		if (f[i] > m) m = f[i];
	}
	
	printf("%d", m);
	
	return 0;
}*/


//更优的LIS 解法 时间复杂度O(nlgn)
//做法是 先弄一个长也为n的表
//b[n] 表示的是 目前为止长为n+1的递增子序列 的最后一个元素的最小值
//从a【0】顺序扫描到a[n-1]
//对于每个值 从数组b中已经有数据的序列查找 
//先用数学归纳法分析 如果a[k]比某个b[j]大 那么我可以接在其后面 递增子序列长度也可以从j+1变成j+2 
//                                        而a[k]也就作为长度j+2递增子序列的最小元素即b[j+1]=a[k]
//                   如果a[k]比b[j]小 那肯定不可能放在b[m](m>j) 因为b[j]已经是那个递增子序列的最后一个元素尽量小的值了！
//因此 b中已经有数据的序列一定是递增的！！！！  这很重要！！！！

//所以做法是：扫描到a[k] 在b中找到他的位置 可以用二分查找
//            如果b[position]==a[k] 那么返回j 等下相等覆盖即可
//            否则就找一个position使得b[position-1]<a[k]<b[position]
//            这样可以拿a[k]跟 b[position]比（如果它有数据）
//            及时更新最小值
//核心思想就是我要保持 每个长度的递增子序列的最后一个元素尽量小 这样才可以继续往上接！！！！

//扫描n 查找lgn 那么 O(nlgn)  漂亮得一逼！！！
//优化了一个数量级！！

int binary_search(int *b, int num,int right) 
{
	//从0到下标right中二分查找num应该插入的位置
	//如果right==-1 说明是第一个 那么直接返回0
	//else
	//如果找到值b[position]==num  返回 position
	//否则 b[position-1]<num<b[position] 返回position

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

int main()
{
	int n;
	cin >> n;
	int *b = new int[n];
	int *a = new int[n];
	int k = -1;
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
		b[i] = -1;
	}

	for (int i = 0; i < n; ++i)
	{
		int position = binary_search(b, a[i],k);
		//如果相等 那么同样插进该位置 不破坏性质 
		if (b[position] == -1)
		{
			b[position] = a[i];
			k = position;
		}
		else
			if (b[position] > a[i])
				b[position] = a[i];
	}
	
	cout << k + 1;


	return 0;
}