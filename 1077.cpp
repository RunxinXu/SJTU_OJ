#include <iostream>

//OJ �ĵ�һ����̬�滮 û������
using namespace std;

int dp[30][30];
int p[30][30];
int a[30];

//��̬�滮�ѵ㣺
//1.��ʶ��Ӧ���ö�̬�滮=====�� д���ݹ�ʽ һ����һ����Ҫ�ֲ������ĵݹ�ʽȻ������ֵ��Ϊ���
//2.��ʼ�� ���Ѿ�ȷ���Ķ�����Ϊ��ʼ������ ����������
//3.���е�ֱ���ã�return�� û�еľ���

int dfs(int i, int j)
{
	if (i > j)
	{
		dp[i][j] = 1;    //��Ϊ1�����ڿ�������1����������ƾ����Ϊ1��
		return dp[i][j];
	}
	if (dp[i][j] != -1) return dp[i][j];//�Ѿ��������
	
	for (int k = i; k <= j; ++k)
	{
		int t1 = dfs(i, k-1);
		int t2 = dfs(k+1 , j);
		if (t1*t2 + a[k] > dp[i][j])
		{
			dp[i][j] = t1*t2 + a[k];
			p[i][j] = k;//������ڵ�
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
	for (int i = 1; i <= n; ++i)       //����Ƕ�̬�滮�ĳ�ʼ��
	{
		cin >> a[i];
		dp[i][i] = a[i];   //��㱾��������Ķ�Ӧ��ֵ
		p[i][i] = i;      //��㱾�������������
	}
	dfs(1, n);            //ִ�ж�̬�滮 ������Ϊ ���ĵݹ�
	cout << dp[1][n] << endl;
	print(1, n);


	return 0;

}