#include <iostream>
#include <string>


using namespace std;

//����������n��Ҷ�ӽ�� ���ڳ���Ҷ�ӽ���������Ƕ�Ϊ2�Ľ�� ������n0=n2+1 ���ܽ����Ϊ2n-1
//���������� ���Կ��Բ�ȡ��̬�洢 ��һ��������ʵ�� ��ģΪ2n ��0���ã�
//����Ҫ���� ���Ե���parent

template<class type>
class hfTree
{
private:
	struct node
	{
		type data;
		int weight;//Ȩֵ
		int parent = 0, left = 0, right = 0; //���±���ʽ�洢
	};

	node *elem; //�洢��������
	int length;
public:
	struct hfcode
	{
		type data;
		string code;
	};

	hfTree(const type*xx, const int *w, int size);
	void getcode(hfcode[]);
	~hfTree() { delete[]elem; }
};

template<class type>
hfTree<type>::hfTree(const type*xx, const int *w, int size)   //xΪ������Ķ��������� wΪȨֵ����
{
	const int max_int = 32767;
	int min1,min2;
	int x, y;//�����ϲ������±�

	length = 2 * size;  //size��Ҷ�ӽ�� ��һ����
	elem = new node[length];

	for (int i = size; i < length; ++i)
	{
		elem[i].weight = w[i - size];
		elem[i].data = xx[i - size];
		elem[i].parent = elem[i].left = elem[i].right = 0;
	}
	//��ʼ�� �������±�n �� 2n-1�� ֮�󲻶�ѡ����Ȩֵ��С�����һ��Ȩֵ֮���½ڵ�ŵ�����λ�õ����һ��(Ҳ�������ݵ�ǰһλ)�����¸��ӹ�ϵ

	for (int i = size - 1; i >= 0; --i)
	{
		min1 = min2 = max_int; x = y = 0;
		for (int j = i + 1; j < length; ++j)
		{
			if (elem[j].parent == 0)
			{
				//��Ҫδ���ϲ��� Ҳ������Ϊ���ڵ��
				if (elem[j].weight < min1)
				{
					min2 = min1;
					min1 = elem[j].weight;
					y = x;
					x = j;
					//min1 ��Զ�� min2 ҪС 
				}
				else
				{
					//�Ȳ���min1 ��ô�ͺ�min2�ȱ�
					if (elem[j].weight < min2)
					{
						min2 = elem[j].weight;
						y = j;
					}
				}
			}
		}

		elem[i].weight = min1 + min2;
		elem[i].left = x;
		elem[i].right = y;
		elem[x].parent = i;
		elem[y].parent = i;
		elem[i].parent = 0;
	}

}

template <class type>
void hfTree<type>::getcode(hfcode result[])
{
	int size = length / 2; //length������ż��
	int p, s;

	for (int i = size; i < length; ++i)
	{
		result[i - size].data = elem[i].data;
		result[i - size].code = "";
		p = elem[i].parent; s = i;

		while (p != 0)
		{
			if (elem[p].left == s) result[i - size].code = "0" + result[i - size].code;
			if (elem[p].right == s) result[i - size].code = "1" + result[i - size].code;
			s = p; p = elem[s].parent;
		}
	}
}


int main()
{
	char ch[] = { "aeistdn" };
	int w[] = { 10,15,12,3,4,13,1 };

	hfTree<char> tree(ch, w, 7);
	hfTree<char> ::hfcode result[7];
	tree.getcode(result);
	for (int i = 0; i < 7; ++i)
	{
		cout << result[i].data << " ->  " << result[i].code;
		cout << endl;
	}
	return 0;
}

