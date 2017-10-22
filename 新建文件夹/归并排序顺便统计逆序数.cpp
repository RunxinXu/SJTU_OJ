#include <iostream>


using namespace std;
//�����ǹ鲢������������
void hehe(int *a, int *result, int left, int right, int &sum)
{
	//����������a result������������� ����Ϊ��left��right�� sumͳ�Ƴ��ֵ�������
	if (left == right)
	{
		return;
	}

	int middle = (left + right) / 2;
	hehe(a, result, left, middle, sum);   //���صľֲ���������鳤����middle-left+1
	hehe(a, result, middle + 1, right, sum);  //���غ�ľֲ���������鳤����right-middle

	int i = 0,j = 0;
	int l_size = middle - left + 1;
	int r_size = right - middle;
	int *tmp = new int[l_size + r_size];
	int k = 0;

	while (i < l_size && j < r_size)
	{
		if (result[left+i] <= result[middle+1+j])
		{
			tmp[k]=result[left+i];
			i++;
			k++;
		}
		else
		{
			//r����ȥ ��ʱlʣ�µĶ��Ǳ������ ��������������ô���
			tmp[k] = result[middle + 1 + j];
			j++;
			k++;
			sum += l_size - i;

		}
	}
	while (i < l_size)
	{
		tmp[k] = result[left  + i];
		k++;
		i++;
	}
	while (j < r_size)
	{
		tmp[k] = result[middle + 1 + j];
		k++;
		j++;
	}
	k = 0;
	for (int t = left; t <= right; ++t)
	{
		result[t] = tmp[k];
		k++;
	}
	delete tmp;
}


int main()
{
	int n;
	cin >> n;
	int *a = new int[n];
	for (int i = 0; i < n; ++i) cin >> a[i];
	int *result = new int[n];
	for (int i = 0; i < n; ++i) result[i] = a[i];
	int sum=0;
	hehe(a, result, 0, n - 1,sum);
	cout << sum;

	return 0;
}

