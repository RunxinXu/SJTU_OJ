#include <iostream>
#include <cstring>

using namespace std;

struct nodeint
{
	int n;
	nodeint *next;
};

struct nodedouble
{
	double n;
	nodedouble *next;
};

struct nodechar
{
	char n;
	nodechar *next;
};

nodeint* hehe(nodeint* a, nodeint *b,nodeint*c)
{
	//a为第一个头 b为第一个尾 c为第二个头
	b->next = c;
	return a;
}
nodedouble* hehe(nodedouble* a, nodedouble *b, nodedouble*c)
{
	//a为第一个头 b为第一个尾 c为第二个头
	b->next = c;
	return a;
}
nodechar* hehe(nodechar* a, nodechar *b, nodechar*c)
{
	//a为第一个头 b为第一个尾 c为第二个头
	b->next = c;
	return a;
}
int main()
{
	char* p = new char[10];
	cin >> p;
	int m, n;
	cin >> n >> m;
	int flag;
	switch (p[0])
	{
	case 'i': flag = 1; break;
	case 'd':flag = 2; break;
	case 'c':flag = 3; break;
	}

	switch (flag)
	{
	case 1:
	{

		nodeint* temp = new nodeint;
		nodeint* first = temp;
		nodeint* cur = temp;
		int t;
		for (int i = 0; i < n; ++i)
		{
			cin >> t;
			if (i < n - 1)
			{
				temp->n = t;
				cur = temp;
				temp = new nodeint;
				cur->next = temp;
			}
			else
			{
				temp->n = t;
				cur = temp; 
				temp->next = NULL;//cur temp都指向最后一个
			}

		}
		nodeint* temp2 = new nodeint;
		nodeint* second = temp2;
		nodeint* cur2 = temp2;
		for (int i = 0; i < m; ++i)
		{
			cin >> t;
			if (i < m - 1)
			{
				temp2->n = t;
				cur2 = temp2;
				temp2 = new nodeint;
				cur2->next = temp2;
			}
			else
			{
				temp2->n = t;
				cur2 = temp2;
				temp2->next = NULL;
			}

		}
		nodeint* result = hehe(first, temp, second);
		temp = result;
		while (temp)
		{
			cout << temp->n<<" ";
			temp = temp->next;
		}
		
	}break;
	case 2:
	{
		nodedouble* temp = new nodedouble;
		nodedouble* first = temp;
		nodedouble* cur = temp;
		double t;
		for (int i = 0; i < n; ++i)
		{
			cin >> t;
			if (i < n - 1)
			{
				temp->n = t;
				cur = temp;
				temp = new nodedouble;
				cur->next = temp;
			}
			else
			{
				temp->n = t;
				cur = temp; 
				temp->next = NULL;//cur temp都指向最后一个
			}

		}
		nodedouble* temp2 = new nodedouble;
		nodedouble* second = temp2;
		nodedouble* cur2 = temp2;
		for (int i = 0; i < m; ++i)
		{
			cin >> t;
			if (i < m - 1)
			{
				temp2->n = t;
				cur2 = temp2;
				temp2 = new nodedouble;
				cur2->next = temp2;
			}
			else
			{
				temp2->n = t;
				cur2 = temp2;
				temp2->next = NULL;
			}

		}
		nodedouble* result = hehe(first, temp, second);
		temp = result;
		while (temp)
		{
			cout << temp->n<<" ";
			temp = temp->next;
		}
	}break;
	case 3:
	{
		nodechar* temp = new nodechar;
		nodechar* first = temp;
		nodechar* cur = temp;
		char t;
		for (int i = 0; i < n; ++i)
		{
			cin >> t;
			if (i < n - 1)
			{
				temp->n = t;
				cur = temp;
				temp = new nodechar;
				cur->next = temp;
			}
			else
			{
				temp->n = t;
				cur = temp;  
				temp->next = NULL;//cur temp都指向最后一个
			}

		}
		nodechar* temp2 = new nodechar;
		nodechar* second = temp2;
		nodechar* cur2 = temp2;
		for (int i = 0; i < m; ++i)
		{
			cin >> t;
			if (i < m - 1)
			{
				temp2->n = t;
				cur2 = temp2;
				temp2 = new nodechar;
				cur2->next = temp2;
			}
			else
			{
				temp2->n = t;
				cur2 = temp2;
				temp2->next = NULL;
			}

		}
		nodechar* result = hehe(first, temp, second);
		temp = result;
		while (temp)
		{
			cout << temp->n<<" ";
			temp = temp->next;
		}
	}break;
	}


	return 0;
}