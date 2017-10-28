#include <cstdio>
#include <iostream>

using namespace std;


//LIS ��������� 
//��̬�滮�ⷨ O(n^2)
//��f(i) ��ʾ���±�i ��β����������г���  =============��״̬
//״̬ת�Ʒ��̣� f(i)= max( f(j)+1 ) if ( j < i && a[j] < a[i] )

/*int main()
{

	int f[10000000];
	int a[10000000];
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);

	}
	f[0] = 1;
	int m = 1;
	for (int i = 1; i < n; ++i)
	{
		f[i] = 1;
		for (int j = 0; j < i; ++j)
		{
			if (a[j] < a[i] && f[j] + 1>f[i]) f[i] = f[j] + 1;

		}
		if (f[i] > m) m = f[i];
	}
	
	printf("%d", m);
	
	return 0;
}*/


//���ŵ�LIS �ⷨ ʱ�临�Ӷ�O(nlgn)
//������ ��Ūһ����ҲΪn�ı�
//b[n] ��ʾ���� ĿǰΪֹ��Ϊn+1�ĵ��������� �����һ��Ԫ�ص���Сֵ
//��a��0��˳��ɨ�赽a[n-1]
//����ÿ��ֵ ������b���Ѿ������ݵ����в��� 
//������ѧ���ɷ����� ���a[k]��ĳ��b[j]�� ��ô�ҿ��Խ�������� ���������г���Ҳ���Դ�j+1���j+2 
//                                        ��a[k]Ҳ����Ϊ����j+2���������е���СԪ�ؼ�b[j+1]=a[k]
//                   ���a[k]��b[j]С �ǿ϶������ܷ���b[m](m>j) ��Ϊb[j]�Ѿ����Ǹ����������е����һ��Ԫ�ؾ���С��ֵ�ˣ�
//��� b���Ѿ������ݵ�����һ���ǵ����ģ�������  �����Ҫ��������

//���������ǣ�ɨ�赽a[k] ��b���ҵ�����λ�� �����ö��ֲ���
//            ���b[position]==a[k] ��ô����j ������ȸ��Ǽ���
//            �������һ��positionʹ��b[position-1]<a[k]<b[position]
//            ����������a[k]�� b[position]�ȣ�����������ݣ�
//            ��ʱ������Сֵ
//����˼�������Ҫ���� ÿ�����ȵĵ��������е����һ��Ԫ�ؾ���С �����ſ��Լ������Ͻӣ�������

//ɨ��n ����lgn ��ô O(nlgn)  Ư����һ�ƣ�����
//�Ż���һ������������

int binary_search(int *b, int num,int right) 
{
	//��0���±�right�ж��ֲ���numӦ�ò����λ��
	//���right==-1 ˵���ǵ�һ�� ��ôֱ�ӷ���0
	//else
	//����ҵ�ֵb[position]==num  ���� position
	//���� b[position-1]<num<b[position] ����position

	if (right == -1) return 0;
    
	int left = 0;
	int middle;
	while (left < right)
	{
		middle = (left + right) / 2;
		if (num > b[middle]) left = middle + 1;
		else
			if (num == b[middle]) return middle;
			else  right = middle - 1;
	}
	if (num > b[left]) return left + 1;
	else return left;
}

int main()
{
	int n;
	cin >> n;
	int *b = new int[n];
	int *a = new int[n];
	int k = -1;
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
		b[i] = -1;
	}

	for (int i = 0; i < n; ++i)
	{
		int position = binary_search(b, a[i],k);
		//������ ��ôͬ�������λ�� ���ƻ����� 
		if (b[position] == -1)
		{
			b[position] = a[i];
			k = position;
		}
		else
			if (b[position] > a[i])
				b[position] = a[i];
	}
	
	cout << k + 1;


	return 0;
}