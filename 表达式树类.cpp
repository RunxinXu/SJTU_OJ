#include <iostream>
#include <cmath>

using namespace std;
//构建一个表达树类并进行计算
//栈也可以实现计算哦 显示中缀-》后缀 之后计算后缀式
//运算符只有加减乘除和小括号！！
//课后习题还要求实现乘方~~乘法优先度高 在这里也把他顺便实现了！

class calc
{
	enum type{data,add,sub,multi,div,exp,zuokuohao,youkuohao,EOL};

	struct node
	{
		type t;
		int data;
		node*left, *right;

		node(type tt, int d = 0, node*l = nullptr, node*r = nullptr)
		{
			t = tt;
			data = d;
			left = l;
			right = r;
		}
	};

	node *root; //树的根
    
	node* create(char* & s);//从表达式s创建一棵树
	type gettoken(char *&s, int &value); //获取下一个符号
	int result(node *t);

public:
	calc(char *s) { root = create(s); }
	int result()
	{
		if (root == nullptr) return 0;
		else return result(root);
	}

};

//具体分类讨论与算法可以见书
//重点与核心就在于建树
calc::node* calc::create(char* &s)
{
	node*p = nullptr, *root = nullptr, *tmp = nullptr; //等下将root返回
	type returntype;
	int value;

	while (*s)
	{
		returntype = gettoken(s,value);  //调用函数获得*s此时的类型 且以value引用作为另一个返回值 并且在该函数中会自动将s向后移动一位 这就是指针也是引用的原因

		switch (returntype)
		{
		case data:case zuokuohao:
			if (returntype == data)
			{
				p = new node(data, value);
			}
			else
			{
				p = create(s); //这里牛逼了 如果是左括号那么由于此时s指针已经移动了 那么参数直接用s 括号内作为一个递归返回一棵树 而这棵树
							   //其实就相当于一个运算数 这也是这两个归到一起的原因
				int aa = result(p);
				p = new node(data, aa);
				//这里书出现了错误！！！括号返回的时候应该只放回一个运算数 也就是括号内的结果
				//否则会出现如（1-2）^80 的错误 如果返回整棵树 他会是1-2^80 ！！！
			}
			if (root == nullptr)
			{
				root = p;
			}
			else
			{
				//除了第一个运算数作为根将来作为左子树之外 其他都是加到当前树的最右边的结点
				tmp = root;
				while (tmp->right) tmp = tmp->right;
				tmp->right = p;
			}
			break;
		case youkuohao:case EOL:
			return root; //遇到结束标记或者右括号就返回root 结束递归
		case add:case sub:  //优先度最低 一定作为根   还有一点 运算符都是右结合的！！
			root = new node(returntype, 0, root);
			break;
		case multi:case div:
			if (root->t == data || root->t == multi || root->t == div || root->t == exp)
			{
				//如果根是运算数或者*/ 那么新的*/就可以作为根 原来的root作为左儿子
				root = new node(returntype, 0, root);
			}
			else
			{
				//根是+-
				//此时根的右儿子可能是/* exp 也可能是一个运算数 但是不管是什么都用p顶替他的位置 并将他作为p的左儿子
				root->right = new node(returntype, 0, root->right);
			}
			break;
		case exp:
			if (root->t == data || root->t == exp)
			{
				root = new node(returntype, 0, root);
			}
			else
			{
				//这东西和只有+-/*的时候一样 只不过多了一层
				//root的右边那条路 乘方最多可以到第三层即根为+- 接下去为/* 再接下去为^ 的情况
				//那么我们只需要沿着这条路一直找 知道找到一个运算数或者是一个乘方符号 代替他并让其成为左儿子
				tmp = root;
				while (tmp->right&&tmp->right->t != exp && tmp->right->t != data) tmp = tmp->right;
				node*tmptmp = tmp->right;
				while (tmptmp->right && (tmptmp->right->t == exp || tmptmp->right->t == data))
				{
					tmptmp = tmptmp->right;
					tmp = tmp->right;
				}
				//前一个while找到乘方符号或者运算数
				//后一个while找到最后一个乘方符号或者运算数
				tmp->right = new node(returntype, 0, tmp->right);
				
				
			}
		}
	}
	return root;
}

calc::type calc::gettoken(char *&s,int &value)
{
	char type;

	while (*s == ' ') s++;  //跳过前缀空格

	if (*s >= '0' && *s <= '9')
	{
		//遇到运算数 要一直读到不是数
		int n = *s - '0';
		s++;
		while (*s >= '0'&&*s <= '9')
		{
			n = n * 10 + *s - '0';
			s++;
		}
		value = n;
		return data;
	}

	if (*s == '\0') return EOL;
	type = *s; ++s;
	switch (type)
	{
	case '+':return add; 
	case '-':return sub;
	case '*':return multi;
	case '/':return div;
	case '(':return zuokuohao;
	case ')':return youkuohao;
	case '^':return exp;
	default:return EOL;
	}
}

int calc::result(node *t)
{
	if (t->t==data) return t->data;
	int left = 0, right = 0;
	left = result(t->left);
	right = result(t->right);
	switch (t->t)
	{
	case add:
		return left + right;
	case sub:
		return left - right;
	case multi:
		return left*right;
	case div:
		return left / right;
	case exp:
		return pow(left, right);
	}
	return t->data;
	
}
int main()
{
	calc a("3*2^2+16-(1-2)^80");
	cout << a.result();
	
	return 0;
}