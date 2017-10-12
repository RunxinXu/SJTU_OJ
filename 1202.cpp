#include <iostream>
#include <cstring>

using namespace std;

struct node
{
	char n;
	node* next;
	
};

int main()
{
	char *p = new char[100];
	char *q = new char[100];
	cin >> p >> q;
	int sizep = strlen(p);
	int sizeq = strlen(q);
	node *temp1 = new node, *temp2, *temp3, *temp4;
	node *headp = temp1;
	for (int i = sizep - 1; i >= 0; --i)
	{
		temp1->n = p[i];
		if (i > 0)
		{
			temp2 = new node;
			temp1->next = temp2;
			temp1 = temp2;
		}
		else
			temp1->next=NULL;  //��ʱtemp1temp2�������һ��
	}
	temp2 = new node;   //ֻ��temp1ָ�����
	node *headq = temp2;
	for (int i = sizeq - 1; i >= 0; --i)
	{
		temp2->n = q[i];
		if (i > 0)
		{
			temp3 = new node;
			temp2->next = temp3;
			temp2 = temp3;
		}
		else
			temp2->next = NULL;   //temp2��q��ĩβ
	} 

	temp4 = new node;
	node* headresult = temp3=temp4;
    node *pcur = headp, *qcur = headq;
	int carry = 0;//��λ
	int tempresult = 0;//��ʱ���

	while (pcur != NULL && qcur != NULL)
	{
		temp3 = temp4;
		tempresult = pcur->n - '0' + qcur->n - '0'+carry;
		carry = tempresult / 10;
		tempresult %= 10;
		temp3->n = tempresult + '0';
		temp4 = new node;
		temp3->next = temp4;
		pcur = pcur->next;
		qcur = qcur->next;
	}
	//temp3 temp4����һ��δ���node��

	while (pcur != NULL)
	{
		temp3 = temp4;
		tempresult = pcur->n - '0' + carry;
		carry = tempresult / 10;
		tempresult %= 10;
		temp3->n = tempresult + '0';
		temp4 = new node;
		temp3->next = temp4;	
		pcur = pcur->next;
	}
     
	while (qcur != NULL)
	{
		temp3 = temp4;
		tempresult = qcur->n - '0' + carry;
		carry = tempresult / 10;
		tempresult %= 10;
		temp3->n = tempresult + '0';
		temp4 = new node;
		temp3->next = temp4;
		qcur = qcur->next;
	}
    
	if (carry != 0)
	{
		temp3 = temp4;
		temp3->n = carry + '0';
		temp3->next = NULL;   //temp3=temp4=result��ĩβ
	}
	else
	{
		delete temp4; //temp4Ϊ��ָ��
		temp3->next = NULL;
	}

	if (headresult->next == NULL) cout << headresult->n;
	else
	{
		if (headresult->next->next == NULL)
		{
			cout << headresult->next->n << headresult->n;
		}
		else
		{
			//��������תresult  ͷ��headresult β��temp3
			node *pre, *cur, *rear;
			pre = headresult;
			cur = pre->next;
			rear = cur->next;
			headresult->next = NULL;
			while (rear)
			{
				cur->next = pre;
				pre = cur;
				cur = rear;
				rear = cur->next;
			}
			cur->next = pre;
			while (cur)
			{
				cout << cur->n;
				cur = cur->next;
			}
		}
	}


	return 0;
}