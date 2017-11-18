#include <iostream>

using namespace std;

void print(int i, int *numofcoins, int *use)
{
	cout << "如果要凑齐" << i << "元，至少需要" << numofcoins[i] << "个硬币，他们分别是：" << endl;
	int *count = new int[5];
	for (int j = 0; j < 5; ++j) count[j] = 0;
	while (i - use[i] >= 0)
	{
		switch (use[i])
		{
		case 1:count[0]++; break;
		case 2:count[1]++; break;
		case 5:count[2]++; break;
		case 21:count[3]++; break;
		case 25:count[4]++; break;
		}
		if(i!=use[i]) i = i - use[i];
		else break;
	}
	
	cout << "1元硬币" << count[0] << "个" << endl;
	cout << "2元硬币" << count[1] << "个" << endl;
	cout << "5元硬币" << count[2] << "个" << endl;
	cout << "21元硬币" << count[3] << "个" << endl;
	cout << "25元硬币" << count[4] << "个" << endl;

}

int main()
{
	int n;
	cin >> n;

	int coins[] = { 1,2,5,21,25 };

	int *numofcoins = new int[n+1];
	int *use = new int[n+1];

	numofcoins[0] = 0;
	numofcoins[1] = 1;
	use[1] = 1;
	use[0] = 0;

	for (int i = 2; i < n + 1; ++i)
	{
		int max = 1000000;
		use[i] = -1;
		for (int j = 0; j < 5; ++j)
		{
			if (i - coins[j] >= 0 && numofcoins[i - coins[j]] + 1 < max)
			{
				max = numofcoins[i - coins[j]] + 1;
				use[i] = coins[j];
			}
		}
		numofcoins[i] = max;
	}
	
	for (int i = 1; i < n + 1; ++i)
	{
		print(i,numofcoins,use);
	}

	return 0;
	
}