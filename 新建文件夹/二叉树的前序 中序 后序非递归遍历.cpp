#include <iostream>
#include <stack>

using namespace std;

//树的前序 中序 后序遍历的非递归实现   用栈！！！

struct node
{
	int data;
	node* left, *right;
};
struct stnode
{
	node* node;
	int time;//进栈的次数
};

void pre_order()
{
	stack<node*> s;
	node* current;

	cout << "前序遍历" << endl;
	s.push(root);

	while (!s.empty())
	{
		current = s.top();
		s.pop();
		cout << current->data;

		if (current->left) s.push(current->left);
		if (current->right) s.push(current->right);

	}
}


void mid_order()
{
	stack<stnode*> s;
	stnode current(root);

	cout << "中序遍历";

	s.push(current);

	while (!s.empty())
	{
		current = s.top();
		s.pop();

		if (current.time == 0) //如果是第一次出栈
		{
			current.time++;
			s.push(current);
			if (current.node->left) s.push(stnode(current.node->left));
		}
		else //第二次出栈
		{
			cout << current.node->data;
			if (current.node->right) s.push(stnode(current.node->right));
		}
	}
}


void post_order()
{
	stack<stnode*> s;
	stnode current(root);

	cout << "后序遍历";

	s.push(current);

	while (!s.empty())
	{
		current = s.top();
		s.pop();
		if (current.time == 0) //第一次出栈
		{
			current.time++;
			s.push(current);
			if (current.node->left) s.push(stnode(current.node->left));
		}
		else
			if (current.time == 1) //第二次出栈
			{
				current.time++;
				s.push(current);
				if (current.node->right) s.push(stnode(current.node->right));
			}
			else
			{
				//第三次出栈
				cout << current.node->data;
				continue;
			}
	}
}



int main()
{
	
	return 0;
}