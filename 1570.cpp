#include <iostream>
using namespace std;
void acc(int, int*, int);
int main()
{
	int *N = NULL, *T = NULL, n = 0, t = 0;
	cin >> n >> t;
	N = new int[n];
	T = new int[t];
	for (int i = 0; i<n; i++)
	{
		cin >> N[i];
	}
	for (int i = 0; i<t; i++)
	{
		cin >> T[i];
	}
	for (int i = 0; i<t; ++i)
	{
		acc(T[i], N, n);
	}
	return 0;
}
void acc(int x, int *p, int n)
{
	int low = 0, high, mid;
	high = n - 1;
	while (high - low>1)
	{
		mid = (low + high) / 2;
		if (x == p[mid]) { high = mid + 1; break; }
		if (x<p[mid]) high = mid;
		else low = mid;
	}
	if (p[high] == x || ((high == n - 1) && (p[high]<x)))
		++high;
	if (low == 0 && x<p[0])
		--high;
	cout << n - high << '\n';
}