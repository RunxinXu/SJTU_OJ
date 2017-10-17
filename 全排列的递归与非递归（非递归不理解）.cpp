#include <iostream>

using namespace std;

//全排列的递归与非递归实现

//递归
void all_range_recur(int k, int n, int a[])  //对数组a从下标k到下标n-1进行全排列
{
	if (k == n - 1)  //递归终止条件
	{
		for (int i = 0; i < n; ++i) cout << a[i];
		cout << endl;
	}

	else
	{
		for (int i = k; i < n; ++i)
		{
			swap(a[k], a[i]); //每一个数字都过来试一下！
			all_range_recur(k + 1, n, a);
			swap(a[k], a[i]);  //复原
		}
	}
}

//非递归 用栈

int main()
{


	return 0;
}