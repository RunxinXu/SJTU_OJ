#include <iostream>

using namespace std;

//ȫ���еĵݹ���ǵݹ�ʵ��

//�ݹ�
void all_range_recur(int k, int n, int a[])  //������a���±�k���±�n-1����ȫ����
{
	if (k == n - 1)  //�ݹ���ֹ����
	{
		for (int i = 0; i < n; ++i) cout << a[i];
		cout << endl;
	}

	else
	{
		for (int i = k; i < n; ++i)
		{
			swap(a[k], a[i]); //ÿһ�����ֶ�������һ�£�
			all_range_recur(k + 1, n, a);
			swap(a[k], a[i]);  //��ԭ
		}
	}
}

//�ǵݹ� ��ջ

int main()
{


	return 0;
}