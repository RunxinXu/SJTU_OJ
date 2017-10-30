#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;

//���ཻ�������鼯����֯��һ����  ������������ʽ�洢
//����Ǹ�����ô˵����һ�����ϵĸ��ڵ� ������ֵ���������ģ or �߶ȣ�������Ҫ����ģ�����ǰ��߶Ȳ���
//����������򴢴���Ǹ��ڵ���±�
//����ʱ�� �������ģ������ģС����Ϊ��ģ��ĵ�����  ����ֵ��Ҫ������
//         ������߶Ȳ����߶�С����Ϊ�߶ȴ�ĵ�����  ֻ�������߶�һ��ʱ�߶ȴ����Ҫ+1 ���򱣳ֲ��䣡
//���� ֻ�е������������ϣ���ģor�߶���ͬʱ ���Ż����Ӹ߶� �������Լ���find��ʱ��
//���� ���ǿ��Լ����Ż���������
//��ִ��find��ʱ�� ���ǿ��԰���·�߹���·��ȫ������Ϊ���ڵ�Ķ��� ��Ϊ·��ѹ��
//��Ϊ����״̬��ϣ�����鼯��ֻ�����㣡
//������·��ѹ������ ֻ�밴��ģ������ ��Ϊ ·��ѹ����֪����ô����߶ȣ�

//����һ����˵���鼯 ����һ����� ����ģ��+·��ѹ���ķ�������

class disjointset
{
public:
	int size;
	int *parent;


	disjointset(int s) :size(s)
	{
		parent = new int[size];
		for (int i = 0; i < size; ++i) parent[i] = -1;  //��ʼʱ��ÿ���˶����Լ�һ����
	}
	~disjointset() { delete[]parent; }
	int find(int x);             //��
	void Union(int root1, int root2);  //��
};


//������Һ����ĵݹ�Ҳ̫������
//��������һ��ʱ ���ǲ���֪����������ȥ֮����ڵ���˭ ����û�취�İ�����
//����û��ϵ ������һ������ĵݹ� find(parent[x]) �����صľ��Ǹ��ڵ�
//��ô����parent[x]=find(parent[x])�ˣ���

/*int disjointset::find(int x)
{
	//��Ҫ��·��ѹ����
	if (parent[x] < 0) return x;   //������ʾ�ҵ��˸��ڵ���
	else
		return parent[x] = find(parent[x]);
}*/

int disjointset::find(int x)
{
	int tmp=x;
	while (parent[tmp] >= 0) tmp = parent[tmp];
	int p = x;
	while (parent[p] >= 0) parent[p] = tmp;
	return tmp;
}
//��Ȼ��Ҳ�����÷ǵݹ�İ汾 Ч�ʲ��
//���ǽ������θ����� ��һ���ҵ�Ҫ������
//�ڶ��θ�����һ·����ţ���


void disjointset::Union(int root1, int root2)  //������Ҫ�ֶ���֤��һ����root�����������Ż�
{
	if (root1 == root2) return;
	if (root1 > root2) Union(root2, root1);  //����漼����Ӧ�����ڶ��������ѧ����������

	parent[root2] += parent[root1];
	parent[root1] = root2;
}


//���鼯��Ӧ��֮���Թ�
//������һֱ���ѡһ��ǽ ���ǽ���߻�����ͬһ�������ǾͰ�ǽ����
//�������յ���ͬһ�����Ͼ�����
void createpuzzle(int size)
{
	int num1, num2;
	disjointset ds(size*size);  //��ά����һά

	
	while (ds.find(0) !=ds.find(size*size - 1))//��������find�����ͬ ��˵��������ͬһ�����ϣ�����
	{
		
		while (true)
		{
			
			num1 = rand()*size*size / (RAND_MAX + 1);  //���ѡһ��
			num2 = num1 - size;  //�������������
			if (num2 >= 0 && num2>=0 &&num2<size*size)
			{
				if (ds.find(num2) != ds.find(num1)) break;  //����������
			}
			num2 = num1 - 1; //����������ߵ�
			if (num1%size!=0 && num2 >= 0 && num2<size*size)
			{
				if (ds.find(num2) != ds.find(num1)) break; //����������
			}
			num2 = num1 + 1;//���������ұߵ�
			if (num2%size != 0 && num2 >= 0 && num2<size*size) //��Խ��
			{
				if (ds.find(num2) != ds.find(num1))break;
			}
			num2 = num1 + size;
			if (num2<size*size&& num2 >= 0 && num2<size*size)
			{
				if (ds.find(num2) != ds.find(num1))break;
			}

		}
		ds.Union(ds.find(num1),ds.find(num2)); //֮ǰ˵���� ��Ҫ�Լ���֤��root ������ ��ô������find����֤������
		cout << "<" << num1 << "," << num2 << ">" << endl;
	}
}




int main()
{
	srand(time(nullptr));
	createpuzzle(10);
	return 0;
}
