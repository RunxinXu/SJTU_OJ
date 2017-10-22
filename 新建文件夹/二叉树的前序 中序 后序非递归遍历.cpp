#include <iostream>
#include <stack>

using namespace std;

//����ǰ�� ���� ��������ķǵݹ�ʵ��   ��ջ������

struct node
{
	int data;
	node* left, *right;
};
struct stnode
{
	node* node;
	int time;//��ջ�Ĵ���
};

void pre_order()
{
	stack<node*> s;
	node* current;

	cout << "ǰ�����" << endl;
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

	cout << "�������";

	s.push(current);

	while (!s.empty())
	{
		current = s.top();
		s.pop();

		if (current.time == 0) //����ǵ�һ�γ�ջ
		{
			current.time++;
			s.push(current);
			if (current.node->left) s.push(stnode(current.node->left));
		}
		else //�ڶ��γ�ջ
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

	cout << "�������";

	s.push(current);

	while (!s.empty())
	{
		current = s.top();
		s.pop();
		if (current.time == 0) //��һ�γ�ջ
		{
			current.time++;
			s.push(current);
			if (current.node->left) s.push(stnode(current.node->left));
		}
		else
			if (current.time == 1) //�ڶ��γ�ջ
			{
				current.time++;
				s.push(current);
				if (current.node->right) s.push(stnode(current.node->right));
			}
			else
			{
				//�����γ�ջ
				cout << current.node->data;
				continue;
			}
	}
}



int main()
{
	
	return 0;
}