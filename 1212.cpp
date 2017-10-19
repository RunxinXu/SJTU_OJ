#include <iostream>
#include <queue>

using namespace std;

//如何判断是否为完全二叉树？？-》用队列呗！！！
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
			cin >> tmp;
			table[i]->data = tmp;

		}
		root = findroot();
	}
	~tree()
	{
		for (int i = 0; i < size; ++i) delete table[i];
		delete table;
	}
	void level_order()
	{
		queue<node*> a;
		a.push(table[root]);
		node *tmp;

		while (!a.empty())
		{
			tmp = a.front();
			a.pop();
			cout << tmp->data << " ";
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
	hehe.level_order();

	return 0;
}

