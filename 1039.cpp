#include <iostream>
#include <queue>
using namespace std;

class tree
{
private:
	
	struct node
	{
		int data;
		node* left, *right;
		node* parent;
	};
	void post_print(node *t)
	{
		if (t == nullptr) return;
		if (t->left) post_print(t->left);
		if (t->right) post_print(t->right);
		cout << t->data << " ";
	}
public:
	node** table;
	int size;
	int* log;

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
		int tmp1, tmp2, tmp3;

		while (cin >> tmp1 >> tmp2 >> tmp3)

		{
			if (tmp2 != -1)
			{
				table[tmp1 - 1]->left = table[tmp2 - 1]; table[tmp2 - 1]->parent = table[tmp1 - 1];
			}
			else
			{
				table[tmp1 - 1]->left = NULL;
			}

			if (tmp3 != -1)
			{
				table[tmp1 - 1]->right = table[tmp3 - 1]; table[tmp3 - 1]->parent = table[tmp1 - 1];
			}
			else
			{
				table[tmp1 - 1]->right = NULL;
			}

		}
	
		log = new int[n];
		for (int i = 0; i < n; ++i)
		{
			log[i] = 0;
		}


	}
	~tree()
	{
		for (int i = 0; i < size; ++i) delete table[i];
		delete table;
	}
	void post_print()
	{
		post_print(table[0]);
	}
	void level_print()

	{
		queue<node*> a;
		a.push(table[0]);
		node *tmp;
		int count = 1;
		int real_count = 1;
		while (real_count <= size)
		{
			tmp = a.front();
			a.pop();
			if (tmp != NULL)
			{
				log[tmp->data - 1] = count;
				count++;
				real_count++;

			}
			else
			{
				count++;
				a.push(NULL);
				a.push(NULL);
				continue;
			}
			if (tmp->left) a.push(tmp->left);
			else a.push(NULL);
			if (tmp->right) a.push(tmp->right);
			else a.push(NULL);
		}

		for (int i = 0; i < size; ++i)
		{
			cout << log[i] << " ";
		}
		cout << endl;

	}
};

int main()
{
	int n;
	cin >> n;
	tree hehe(n);

	hehe.level_print();

	hehe.post_print();


	return 0;
}

