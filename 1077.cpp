#include <iostream>

//OJ 的第一个动态规划 没做出来
using namespace std;

int dp[30][30];
int p[30][30];
int a[30];

//动态规划难点：
//1.意识到应该用动态规划=====》 写出递归式 一般是一个需要局部遍历的递归式然后找最值作为结果
//2.初始化 把已经确定的东西作为初始化资料 用于填表的起步
//3.表有的直接用（return） 没有的就算

int dfs(int i, int j)
{
	if (i > j)
	{
		dp[i][j] = 1;    //设为1是由于空子树是1！！！不是凭空设为1的
		return dp[i][j];
	}
	if (dp[i][j] != -1) return dp[i][j];//已经计算过的
	
	for (int k = i; k <= j; ++k)
	{
		int t1 = dfs(i, k-1);
		int t2 = dfs(k+1 , j);
		if (t1*t2 + a[k] > dp[i][j])
		{
			dp[i][j] = t1*t2 + a[k];
			p[i][j] = k;//保存根节点
		}
	}
	return dp[i][j];
}

void print(int i, int j)
{
	if (i > j) return;
	cout << p[i][j] << " ";
	print(i, p[i][j] - 1);
	print(p[i][j] + 1, j);
}
int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			p[i][j] = -1;
			dp[i][j] = -1;
		}
	}
	for (int i = 1; i <= n; ++i)       //这个是动态规划的初始化
	{
		cin >> a[i];
		dp[i][i] = a[i];   //结点本身就是他的对应的值
		p[i][i] = i;      //结点本身根就是他本身
	}
	dfs(1, n);            //执行动态规划 可以视为 打表的递归
	cout << dp[1][n] << endl;
	print(1, n);


	return 0;

}