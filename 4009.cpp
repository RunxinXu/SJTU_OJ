#include <iostream>
#include <cstring>



using namespace std;


int main()
{
	char*p = new char[100];
	cin.getline(p, 100);
	char *q = new char[100];
	cin.getline(q, 100);
    
	if (strlen(p) != strlen(q))
	{
		cout << "No Solution";
		return 0;
	}
	int size = strlen(q); 
	int a = 2;
	int flag = 1;
	while (a <= size / 2+1)
	{
		if (size%a != 0) { a++; continue; }
		else
		{
			int j = 0;
			int t = 0;
			int k = 0;
			while (j < size)
			{
				if (p[k] != q[j]) {
					flag = 0; break;
				}
				else
				{
					k += a;
					if (k >= size)
					{
						t++;
						k = t;
					}
				}
				j++;
			}
			if (flag) cout << a;
			flag = 1;
			a++;
		}
	}
	
	



	return 0;
}