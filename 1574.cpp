#include <iostream>


using namespace std;

//�����Ǵ�����ȡģ  ��������ʽ�ķ���
//������10�������Կ��Գ�10ȡ�����

//����ʱ�����Ҫ�ǣ��������kΪż�� ��ô����ÿ����100������10 ��������ȥ������

int main()
{
	int n, m, k, x;
	cin >> n >> m >> k >> x;

	int carry = 0;
	if (k == 0)
		carry= 1;
	else 
	{
		if (k % 2 != 0) {
			int tmp = 10 % n;
			for (int i = 0; i < k - 1; i++)
			{
				tmp = (10 * tmp) % n;
			}
			carry = tmp;
		}
		else
		{
			int tmp = 100 % n;
			for (int i = 0; i < k /2-1; i++)
			{
				tmp = (100 * tmp) % n;
			}
			carry = tmp;
		}
	}
	
	//carryΪʵ�ʵȼ۴���
	
	int haha = (m*carry) % n;

	int curnum = n - haha;  //curnum������������0����
	//��ôx���Ǽ����⣿��

	int xixi = x - curnum;
	if (xixi < 0)
	{
		cout << xixi + n;
	}
	if (xixi == 0) cout << "0";
	if (xixi > 0)
	{
		cout << xixi;
	}

	return 0;
}

