#include <iostream>
#include <string>
#include <stack>


using namespace std;

//这是用动态存储实现哈夫曼树 这真的就是树了
//动态存储由于一直在合并 到最后只有一个root 所以也就没必要用parent指针了
//那么如何从root找到所有叶子结点并且给出编码呢
//那么就要用到栈了！！！
//其实我感觉递归且用编码做传递的参数去递归也是可以的。。。
//反正栈就是来将递归问题变成非递归的有力工具！！！

template<class T>
class hftree
{
private:
	struct node
	{
		T data;
		int weight;
		node *left=nullptr, *right=nullptr	;
		

		node(int w, node*l=nullptr, node*r=nullptr) :weight(w), left(l), right(r) {};
	};

	struct stacknode
	{
		node *t;
	    string code;
		stacknode(node*tt = nullptr, string s = "") :t(tt), code(s) {};
	};
	node *root;
public:
	struct hfcode
	{
		T data;
		string code;
	};
	hftree(const T*a, const int * b, int size);
	void getcode(hfcode result[]);
};

template<class T>
hftree<T>::hftree(const T*a, const int * b, int size)
{
	node** hehe;
	hehe = new node*[size];
	node *tmp;
	for (int i = 0; i < size; ++i)
	{
		hehe[i] = new node(b[i]);
		hehe[i]->data = a[i];
	}

	int x = 0, y = 0;
	const int max_int = 30000;
	int min1 = max_int;
	int min2 = min1;

	for (int i = 1; i < size; ++i)
	{
		min1 = min2 = max_int;
		for (int j = 0; j < size; ++j)
		{
			if (hehe[j] == nullptr) continue;
			if (hehe[j]->weight < min1)
			{
				min2 = min1;
				y = x;
				x = j;
				min1 = hehe[j]->weight;
			}
			else
			{
				if (hehe[j]->weight < min2)
				{
					y = j;
					min2 = hehe[j]->weight;
				}
			}
		}

		tmp = new node(hehe[x]->weight + hehe[y]->weight, hehe[x], hehe[y]);
	
		hehe[x] = tmp;
		hehe[y] = nullptr;
	}
	root = hehe[x];
	delete[]hehe;

}

template<class T>
void hftree<T>::getcode(hfcode result[])
{
	stack<stacknode> st;
	int num = 0;
	stacknode cur;

	if (root == nullptr) return;
	st.push(stacknode(root, ""));

	while (!st.empty())
	{
		cur = st.top();
		st.pop();
		if (cur.t->left == nullptr)   //叶子结点
		{
			result[num].data = cur.t->data;
			result[num].code = cur.code;
			++num;
			continue;
		}
		st.push(stacknode(cur.t->left, cur.code + "0"));
		st.push(stacknode(cur.t->right, cur.code + "1"));
	}
}

int main()
{
	char ch[] = { "aeistdn" };
	int w[] = { 10,15,12,3,4,13,1 };
	hftree<char> tree(ch, w, 7);
	hftree<char>::hfcode result[7];
	tree.getcode(result);
	for (int i = 0; i < 7; ++i)
	{
		cout << result[i].data << "->" << result[i].code << endl;
	}
	
	return 0;
}

