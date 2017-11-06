#include <iostream>
#include <cstring>

using namespace std;


class binarysearchtree
{
	struct node
	{
		int data;
		int size;
		node*left, *right;
		node(const int &a, node*l, node*r) :data(a), left(l), right(r), size(1) {};

	};

	node* root;

	void insert(const int&x, node*&t);
	void remove(const int&x, node*&t);
	bool find(const int&x, node*t) const;
	void print(node *t)
	{
		if (t == nullptr) return;
		print(t->left);
		cout << t->data << endl;
		print(t->right);
	}
	void remove_less_than(const int&x, node*&t);
	void remove_more_than(const int&x, node *&t);

	int update_size(node*t)
	{
		if (t == nullptr) return 0;
		int a = update_size(t->left);
		int b = update_size(t->right);
		t->size = a + b + 1;
		return t->size;
	}
	void findth(int x, node *t);
	void makeempty(node *t)
	{
		if (t == nullptr) return;
		makeempty(t->left);
		makeempty(t->right);
		delete t;
	}
	void remove_bound(const int&x, const int&y, node *&t);
public:
	binarysearchtree(node *a = nullptr) { root = a; }
	bool find(const int&a) const;
	void insert(const int&x);
	void remove(const int&x);
	void print() { print(root); }
	void remove_less_than(const int&x);
	void remove_more_than(const int&x);
	void remove_bound(const int&x, const int&y);
	void findth(int x) { findth(x, root); }

};

void binarysearchtree::insert(const int&x)
{
	insert(x, root);
	update_size(root);
}

void binarysearchtree::remove(const int&x)
{
	remove(x, root);
	update_size(root);
}

bool binarysearchtree::find(const int&x) const
{
	return find(x, root);
}


bool binarysearchtree::find(const int&x, node* t) const
{
	if (t == nullptr) return false;
	if (t->data == x) return true;
	else
	{
		if (x < t->data) return find(x, t->left);
		else return find(x, t->right);
	}
}

void binarysearchtree::insert(const int&x, node* &t)  //这个指针的引用是关键 因为指针的改变是要保持回返回的地方的！！
{
	if (t == nullptr) t = new node(x, nullptr, nullptr);
	else
	{
		if (x < t->data) insert(x, t->left);
		else
			if (x >= t->data) insert(x, t->right);
	}
}

void binarysearchtree::remove(const int&x, node* &t) //指针的引用是精髓！！！！
{
	if (t == nullptr) return;
	if (x < t->data) remove(x, t->left);
	else
		if (x > t->data) remove(x, t->right);
		else
		{

			if (!t->left && !t->right)
			{
				//如果没有儿子
				node *tmp = t;
				t = nullptr;
				delete tmp;
			}
			else
			{
				if (t->left && !t->right)
				{
					node *tmp = t;
					t = t->left;
					delete tmp;
				}
				else
				{
					if (t->right && !t->left)
					{
						node *tmp = t;
						t = t->right;
						delete tmp;
					}
					else
					{
						//如果是两个儿子
						node *tmp = t->right;
						while (tmp->left) tmp = tmp->left;
						t->data = tmp->data;
						remove(tmp->data, t->right);

					}
				}
			}
		}
}


void binarysearchtree::remove_less_than(const int&x)
{
	remove_less_than(x, root);
	update_size(root);
}

void binarysearchtree::remove_more_than(const int&x)
{
	remove_more_than(x, root);
	update_size(root);
}


void binarysearchtree::remove_less_than(const int&x, node *&t)
{
	if (t == nullptr) return;
	//如果x比t所指结点还小 那么递归左子树
	if (x <= t->data) remove_less_than(x, t->left);  //因为是删除比x小的所以t所指的并不用删！！
	else
	{
		//t的右子树可能也有点要删 所以先删掉左边的和t所指的
		//然后继续对t递归调用
		node *tmp = t;
		t = t->right;
		makeempty(tmp->left);
		delete tmp;
		remove_less_than(x, t);

	}
}

void binarysearchtree::remove_more_than(const int&x, node*&t)
{

	//思想基本同上
	if (t == nullptr) return;
	if (t->data <= x) remove_more_than(x, t->right);
	else
	{
		node *tmp = t;
		t = t->left;
		makeempty(tmp->right);
		delete tmp;
		remove_more_than(x, t);
	}
}


void binarysearchtree::findth(int x, node *t)
{
	if (!t || t->size < x)
	{
		cout << "N" << endl;
		return;
	}
	else
	{
		if (!t->left && x != 1) findth(x - 1, t->right);
		else {
			if (!t->left && x == 1)
			{
				cout << t->data << endl;
				return;
			}
			else {
				if (t->left && t->left->size == x - 1)
				{
					cout << t->data << endl;
					return;
				}
				else
				{
					if (t->left->size < x - 1)
						findth(x - t->left->size - 1, t->right);
					else
						if (t->left->size > x - 1)
							findth(x, t->left);
				}
			}
		}
	}
}


void binarysearchtree::remove_bound(const int&x, const int&y)
{
	if (x <= y) remove_bound(x, y, root);
}


void binarysearchtree::remove_bound(const int&x, const int&y, node *&t)
{
	if (t == nullptr) return;
	//如果t所指结点小于x或者大于y 那么对子树递归调用
	if (t->data <= x) remove_bound(x, y, t->right);
	else
		if (t->data >= y) remove_bound(x, y, t->left);
		else
		{
			//t所指就在范围之内 那么把t所指去除 然后继续对这个位置进行调用
			remove(t->data, t);
			remove_bound(x, y, t);
		}
}

int main()
{
	binarysearchtree a;
	int n;
	cin >> n;
	int tmp;
	char *p = new char[20];
	for (int i = 0; i < n; ++i)
	{
		cin >> p >> tmp;
		if (strcmp(p, "insert") == 0) a.insert(tmp);
		if (strcmp(p, "find") == 0)
		{
			if (a.find(tmp)) cout << "Y" << endl;
			else cout << "N" << endl;
		}
		if (strcmp(p, "find_ith") == 0) a.findth(tmp);
		if (strcmp(p, "delete") == 0) a.remove(tmp);
		if (strcmp(p, "delete_greater_than") == 0) a.remove_more_than(tmp);
		if (strcmp(p, "delete_less_than") == 0) a.remove_less_than(tmp);
		if (strcmp(p, "delete_interval") == 0)
		{
			int tmp2; 
			cin >> tmp2;
			a.remove_bound(tmp, tmp2);
		}
	}


	return 0;
}