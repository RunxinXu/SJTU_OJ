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
		node* left, *right;
		node* parent=NULL;
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
		int tmp;
		for (int i = 0; i < n; ++i)
		{
			cin >> tmp;
			if (tmp == 0) table[i]->left = NULL;
			else {
				table[i]->left = table[tmp - 1]; table[tmp - 1]->parent = table[i];
			}
			cin >> tmp;
			if (tmp == 0) table[i]->right = NULL;
			else { table[i]->right = table[tmp - 1]; table[tmp - 1]->parent = table[i]; }

		}
		root = findroot();
	}
	~tree()
	{
		for (int i = 0; i < size; ++i) delete table[i];
		delete table;
	}
	bool istwo()
	{
		queue<node*> hehe;
		node* tmp;
		int count = 0;
		hehe.push(table[root]);

		while (!hehe.empty())
		{
			tmp = hehe.front();
			hehe.pop();
			if (tmp != NULL)
			{
				count++;
				if (count >= size) return true;
				else
				{
					hehe.push(tmp->left);
					hehe.push(tmp->right);
				}
			}
			else
			{
				if (count < size) return false;
			}
		}
	}
};

int main()
{
	int n;
	cin >> n;
	tree hehe(n);
	if (hehe.istwo()) cout << "Y";
	else cout << "N";

	return 0;
}

