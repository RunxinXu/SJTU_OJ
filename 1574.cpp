#include <iostream>


using namespace std;

//核心是大整数取模  采用算竖式的方法
//这里是10的幂所以可以乘10取余迭代

//减少时间的重要是！！！如果k为偶数 那么可以每次用100而不是10 ！！！我去！！！

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
	
	//carry为实际等价次数
	
	int haha = (m*carry) % n;

	int curnum = n - haha;  //curnum号助教现在是0号题
	//那么x号是几号题？？

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

