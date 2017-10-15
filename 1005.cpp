#include <iostream>


using namespace std;

bool check(int* p)
{
	bool hehe[9];
	for (int i = 0; i < 9; ++i) hehe[i] = false;
	for (int i = 0; i < 9; ++i)
	{
		if (hehe[p[i]-1] == true) return false;
		else  hehe[p[i]-1] = true;
	}
	return true;
}


int main()
{
	int n; cin >> n;
	int flag = 0;
	int tmp[9];
	bool *result = new bool[n];
	
	for (int i = 0; i < n; ++i)
	{
		int **p = new int*[9];
		for (int j = 0; j < 9; ++j) p[j] = new int[9];
		for (int m = 0; m < 9; ++m)
		{
			for (int n = 0; n < 9; ++n)
			{
				cin >> p[m][n];
			}
			if (flag)
			{
				if (!check(p[m]))
				{
					cout << "Wrong" << endl;
					flag = 1;
					break;
				}
			}
	
		}
		if (!flag)
		{
			for (int j = 0; j < 9; ++j) 
			{
				for (int n = 0, m = 0; n < 9; ++n, ++m)
				{
					tmp[n] = p[m][j];
				}
				if (!check(tmp)) { flag = 1; break; }
			}
		}
		if (!flag)
		{
			for (int m = 0; m < 3; ++m)
			{
				for (int n = 0; n < 3; ++n)
				{
					tmp[0] = p[0 + m*3][0 + n*3];
					tmp[1] = p[0 + m * 3][1 + n * 3];
					tmp[2] = p[0 + m * 3][2 + n * 3];
					tmp[3] = p[1 + m * 3][0 + n * 3];
					tmp[4] = p[1 + m * 3][1 + n * 3];
					tmp[5] = p[1 + m * 3][2 + n * 3];
					tmp[6] = p[2 + m * 3][0 + n * 3];
					tmp[7] = p[2 + m * 3][1 + n * 3];
					tmp[8] = p[2 + m * 3][2 + n * 3];
					if (!check(tmp)) { flag = 1; break; }
				}
				if (flag) break;
			}
		}
		if (flag) result[i] = false;
		else result[i] = true;
		flag = 0;

		for (int i = 0; i < 9; ++i) delete[]p[i];
		delete[]p;

	}
	for (int i = 0; i < n; ++i)
	{
		if (result[i]) cout << "Right" << endl;
		else cout << "Wrong" << endl;
	}
	delete[]result;
	
	return 0;
}

