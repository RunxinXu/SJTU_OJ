#include <iostream>
#include <queue>

using namespace std;

class tree
{
private:
	struct node
	{
		node* left = NULL, *right = NULL;
		node* parent = NULL;
		int n;
		int flagtofindroot = 0;
	};
	node* findroot()
	{
		for (int i = 0; i < size; ++i)
		{
			if (table[i]->flagtofindroot == 0)
			{
				return table[i];
			}
		}
		return table[size - 1];
	}
	
public:
	node** table;
	node* root;//根
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
				table[tmp - 1]->flagtofindroot = 1;
			}
			cin >> tmp;
			if (tmp == 0) table[i]->right = NULL;
			else { table[i]->right = table[tmp - 1]; table[tmp - 1]->flagtofindroot = 1; }
			cin >> tmp;
			table[i] ->n= tmp;

		}
		root = findroot();
	}
	~tree()
	{
		for (int i = 0; i < size; ++i) delete table[i];
		delete table;
	}

	void print_qianxu(node*t)
	{
		if (t == NULL) return;
		cout << t->n << " ";
		print_qianxu(t->left);
		print_qianxu(t->right);

	}
	void print_houxu(node*t)   //孩子-兄弟法的树后序遍历等价于 二叉树的中序遍历方法（网上说的）
	{
		if (t != NULL)
		{
			print_houxu(t->left);
			cout << t->n << " ";
			print_houxu(t->right);
		}
		
	}
	void print_cengci(node*p)
	{
		queue<node*> haha;
		haha.push(root);
		node* tmp;
		while (!haha.empty())
		{
			tmp = haha.front();
			haha.pop();
			cout << tmp->n << " ";
			if (tmp->left != NULL)
			{
				tmp = tmp->left;
				while (tmp != NULL)
				{
					haha.push(tmp);
					tmp = tmp->right;
				}
			}
			
		}
		
	}
	void qianxu()
	{
		print_qianxu(root);
		cout << endl;
	}
	void houxu()
	{
		print_houxu(root);
		cout << endl;
	}
	void cengci()
	{
		print_cengci(root);
		cout << endl;
	}
};

int main()
{
	int n;
	cin >> n;
	tree hehe(n);
	
	hehe.qianxu();
	hehe.houxu();
	hehe.cengci();
	

	return 0;
}

