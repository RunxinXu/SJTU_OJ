#include <iostream>


using namespace std;

//KMP�㷨�ַ���ƥ�䣡 ʱ�临�Ӷ�O��n��
int find(const char*a, const char*b)
{
	//��a��������b�Ӵ�
	int a_size = strlen(a);
	int b_size = strlen(b);

	//��Ԥ�����ַ���b ����һ��ʧЧ����
	int *p = new int[b_size];
	int j;

	p[0] = -1;
	for (int i = 1; i < b_size; ++i)
	{
		j = i - 1; //jΪi��ǰһ���±�
		while (j >= 0 && b[p[j] + 1] != b[i]) j = p[j];
		//���b[p[j] + 1] == b[i] ��ô��Ȼ����p[j]+1����
		//���j<0 ˵���Ѿ��Ҳ����� ��ô���p[i]��Ϊ-1  Ҳ��������ô��СҲ�Ҳ������� ǰx���ͺ�x����ͬ
		if (j < 0) p[i] = -1;
		else p[i] = p[j] + 1;
	}

	//���Ԥ�����Ƿǳ������ ����ͼʾ���Լ�ͼ


	//��������KMP�㷨��Ҫ���� ͬ������ ע�⵱j=0ʱ˵����һ���˻�����-1 ��ʱֻ��Ҫ����i������ƥ�䵽��һ��֮���ٽ���
	int i = 0;
	j = 0;
	while (i < a_size && j < b_size)
	{
		//ƥ�䵽a[i] ��b[j]
		if (a[i] == b[j])
		{
			i++;
			j++;
		}
		else
		{
			if (j == 0) //��һ���˻�����j=-1;
				i++;
			else
				j = p[j-1]+1; //�˻���
			//ע��j��׼��ȥƥ��� ��j-1���Ѿ�ƥ���ϵ� �����˻�ʱ�õ���p[j-1] ��һ���Ǹ��� ƥ����һ����
		}
	}
	delete[]p;
	if (j == b_size) //ƥ�䵽��ȫ�� 
		return i - b_size;   //������a���±��һ��
	else
		return -1; //ƥ��ʧ��
}


int main()
{
	char* a = "asdf;kjasdffkljasf";
	char *b = "sdffkl";
	cout << find(a, b);


	return 0;
}