#include <iostream>
#include <queue>

using namespace std;

class tree
{
private:
	int findroot()
	{
		for (int i = 0; i < size; ++i)
		{
			if (table[i]->parent == NULL) return i;
		}
	}
	struct node
	{
		int data;
		node* left, *right;
		node* parent = NULL;
	};
public:
	node** table;
	int root;//根的下标
	int size;

	tree(int n)
	{
		size = n;
		table = new node*[n];
		for (int i = 0; i < n; ++i) table[i] = new node;
		for (int i = 0; i < n; ++i)
		{
			table[i]->data = i + 1;
			table[i]->left = table[i]->right = table[i]->parent = NULL;
		}
		int tmp1,tmp2,tmp3;
		
		while (cin >> tmp1 >> tmp2 >> tmp3)

		{
			table[tmp1 - 1]->left = table[tmp2 - 1]; table[tmp2 - 1]->parent = table[tmp1 - 1];


			table[tmp1 - 1]->right = table[tmp3 - 1]; table[tmp3 - 1]->parent = table[tmp1 - 1];

		}
		
		root = findroot();

		
	}
	~tree()
	{
		for (int i = 0; i < size; ++i) delete table[i];
		delete table;
	}
	void level_print()
	{
		queue<node*> a;
		a.push(table[root]);
		node *tmp;

		while (!a.empty())
		{
			tmp = a.front();
			a.pop();
			cout << tmp->data << endl;
			if (tmp->left) a.push(tmp->left);
			if (tmp->right) a.push(tmp->right);
		}
	}

};

int main()
{
	int n;
	cin >> n;
	tree hehe(n);
	hehe.level_print();

	return 0;
}

