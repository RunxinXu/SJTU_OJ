#include <stdio.h>
#define max 1000001
long a[max], b[max];
long count;


//归并排序 两步骤：排序 合并
//         两数组：一数据 一临时
void Merge(long a[], int start, int mid, int end)  //归并排序的合并部分
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
			count += j - k;//统计逆序数对
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

void MergeSort(long a[], int start, int end)  //归并排序
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		MergeSort(a, start, mid);     // 将前半部分排序
		MergeSort(a, mid + 1, end);     // 将后半部分排序
		Merge(a, start, mid, end);     // 合并前后两个部分
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