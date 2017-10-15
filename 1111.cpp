#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

struct node
{
	char n;
	node*left, *right;
};

node* hehe(char*pre,char*middle, int length)
{
	if (length == 1)
	{
		node* cur = new node;
		cur->n = pre[0];
		cur->left = cur->right = NULL;
		return cur;
	}
	if (length == 0)
	{
		return NULL;
	}
	char tmp = pre[0];
	int j = 0;
	while (tmp!=middle[j]) j++;  
	//此时j为middle中 pre【0】对应的下标
	node* cur = new node;
	cur->n = pre[0];
	cur->left = hehe(pre + 1, middle, j);
	cur->right = hehe(pre + 1 + j, &middle[j] + 1, length - j - 1);
	return cur;
}

int main()
{
	char *pre = new char[27];
	char *middle = new char[27];
	cin.getline(pre,27);
	cin.getline(middle,27);
	int size = strlen(pre);
	node *root = hehe(pre, middle, size);

	queue<node*> heihei;
	heihei.push(root); 
	int current_num = 0;

	while (!heihei.empty())
	{
		node* tmp = heihei.front();
		heihei.pop();
		if (tmp != NULL)
		{
			current_num++; cout << tmp->n << " ";
			heihei.push(tmp->left);
			heihei.push(tmp->right);
		}
		else
		{
			cout << "NULL ";
			heihei.push(NULL);
			heihei.push(NULL);
		}
		
		if (current_num >= size) break;
	}


	return 0;
}

