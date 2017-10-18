#include <iostream>
#include <cmath>

using namespace std;
//����һ��������ಢ���м���
//ջҲ����ʵ�ּ���Ŷ ��ʾ��׺-����׺ ֮������׺ʽ
//�����ֻ�мӼ��˳���С���ţ���
//�κ�ϰ�⻹Ҫ��ʵ�ֳ˷�~~�˷����ȶȸ� ������Ҳ����˳��ʵ���ˣ�

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

	node *root; //���ĸ�
    
	node* create(char* & s);//�ӱ��ʽs����һ����
	type gettoken(char *&s, int &value); //��ȡ��һ������
	int result(node *t);

public:
	calc(char *s) { root = create(s); }
	int result()
	{
		if (root == nullptr) return 0;
		else return result(root);
	}

};

//��������������㷨���Լ���
//�ص�����ľ����ڽ���
calc::node* calc::create(char* &s)
{
	node*p = nullptr, *root = nullptr, *tmp = nullptr; //���½�root����
	type returntype;
	int value;

	while (*s)
	{
		returntype = gettoken(s,value);  //���ú������*s��ʱ������ ����value������Ϊ��һ������ֵ �����ڸú����л��Զ���s����ƶ�һλ �����ָ��Ҳ�����õ�ԭ��

		switch (returntype)
		{
		case data:case zuokuohao:
			if (returntype == data)
			{
				p = new node(data, value);
			}
			else
			{
				p = create(s); //����ţ���� �������������ô���ڴ�ʱsָ���Ѿ��ƶ��� ��ô����ֱ����s ��������Ϊһ���ݹ鷵��һ���� �������
							   //��ʵ���൱��һ�������� ��Ҳ���������鵽һ���ԭ��
				int aa = result(p);
				p = new node(data, aa);
				//����������˴��󣡣������ŷ��ص�ʱ��Ӧ��ֻ�Ż�һ�������� Ҳ���������ڵĽ��
				//���������磨1-2��^80 �Ĵ��� ������������� ������1-2^80 ������
			}
			if (root == nullptr)
			{
				root = p;
			}
			else
			{
				//���˵�һ����������Ϊ��������Ϊ������֮�� �������Ǽӵ���ǰ�������ұߵĽ��
				tmp = root;
				while (tmp->right) tmp = tmp->right;
				tmp->right = p;
			}
			break;
		case youkuohao:case EOL:
			return root; //����������ǻ��������žͷ���root �����ݹ�
		case add:case sub:  //���ȶ���� һ����Ϊ��   ����һ�� ����������ҽ�ϵģ���
			root = new node(returntype, 0, root);
			break;
		case multi:case div:
			if (root->t == data || root->t == multi || root->t == div || root->t == exp)
			{
				//�����������������*/ ��ô�µ�*/�Ϳ�����Ϊ�� ԭ����root��Ϊ�����
				root = new node(returntype, 0, root);
			}
			else
			{
				//����+-
				//��ʱ�����Ҷ��ӿ�����/* exp Ҳ������һ�������� ���ǲ�����ʲô����p��������λ�� ��������Ϊp�������
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
				//�ⶫ����ֻ��+-/*��ʱ��һ�� ֻ��������һ��
				//root���ұ�����· �˷������Ե������㼴��Ϊ+- ����ȥΪ/* �ٽ���ȥΪ^ �����
				//��ô����ֻ��Ҫ��������·һֱ�� ֪���ҵ�һ��������������һ���˷����� �������������Ϊ�����
				tmp = root;
				while (tmp->right&&tmp->right->t != exp && tmp->right->t != data) tmp = tmp->right;
				node*tmptmp = tmp->right;
				while (tmptmp->right && (tmptmp->right->t == exp || tmptmp->right->t == data))
				{
					tmptmp = tmptmp->right;
					tmp = tmp->right;
				}
				//ǰһ��while�ҵ��˷����Ż���������
				//��һ��while�ҵ����һ���˷����Ż���������
				tmp->right = new node(returntype, 0, tmp->right);
				
				
			}
		}
	}
	return root;
}

calc::type calc::gettoken(char *&s,int &value)
{
	char type;

	while (*s == ' ') s++;  //����ǰ׺�ո�

	if (*s >= '0' && *s <= '9')
	{
		//���������� Ҫһֱ����������
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