#include <stdio.h>
#define max 1000001
long a[max], b[max];
long count;


//�鲢���� �����裺���� �ϲ�
//         �����飺һ���� һ��ʱ
void Merge(long a[], int start, int mid, int end)  //�鲢����ĺϲ�����
{
	int i = start, j = mid + 1, k = start;
	while (i <= mid&&j <= end)
	{
		if (a[i] <= a[j])
		{
			b[k++] = a[i++];
		}
		else
		{
			count += j - k;//ͳ����������
			b[k++] = a[j++];
		}
	}
	while (i <= mid)
	{
		b[k++] = a[i++];
	}
	while (j <= end)
	{
		b[k++] = a[j++];
	}
	for (int i = start; i <= end; i++)
	{
		a[i] = b[i];
	}
}

void MergeSort(long a[], int start, int end)  //�鲢����
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		MergeSort(a, start, mid);     // ��ǰ�벿������
		MergeSort(a, mid + 1, end);     // ����벿������
		Merge(a, start, mid, end);     // �ϲ�ǰ����������
	}
}
int main(int argc, char const *argv[])
{
	int m;
	//scanf("%d",&n);
	//while(n--)
	//{
	scanf("%d", &m);
	count = 0;
	for (int i = 0; i < m; i++)
	{
		scanf("%ld", a + i);
	}
	MergeSort(a, 0, m - 1);
	printf("%ld\n", count);
	//}
	return 0;
}