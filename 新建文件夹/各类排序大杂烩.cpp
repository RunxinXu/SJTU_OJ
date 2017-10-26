#include <iostream>

using namespace std;

//ֱ�Ӳ������� ���ֲ������� л������
//ֱ��ѡ������ ð������
//������ �鲢���� ��������
//������

//ֱ�Ӳ������򣺴�1������n �ֱ������õ����д�β��ͷ���� ���뵽��ȷ��λ��
//ʱ�临�Ӷ�O(n^2) �ȶ�����
template<class T>
void simpleinsertsort(T a[], int size)
{
	int k;
	T tmp;
	for (int i = 1; i < size; ++i)
	{
		tmp = a[i];
		for (k = i - 1; k >= 0&&tmp<a[k]; --k)
		{
			a[k + 1] = a[k];
		}
		a[k + 1] = tmp;
	}
}

//���ֲ��������ڴ�����õ�������λ��ʱ�ö��ֲ���
//�����ƶ��ĸ��ӶȻ���n �����ܵĻ���O(n^2) �ȶ�����

//ϣ�����򣺲���������һ��Ԫ�����Ҫ�ƶ�����Զ���Ǳ�һ��һ���ƹ�ȥ��
//ϣ��������һ���������� ֻҪ��֤�����1-���򼴿�
//�ǲ��ȶ�������
template<class T>
void shellsort(T a[], int size)
{
	int step, i, j;
	T tmp;
	 
	for (step = size / 2; step >= 1; step /= 2)   //������������в��ö���ֱ��1-����
	{
		for (i = step; i < size; ++i)    //Ϊʲô��step��ʼ���� ��Ϊ��һ��Ԫ�ز����ţ�
		{
			tmp = a[i];
			for (j = i - step; j >= 0 && a[j] > tmp; j -= step) a[j + step] = a[j];
			a[j + step] = tmp;
		}
	}
}

//ֱ��ѡ������ ������� ���Ӷ�O(n^2)
//���ȶ�����  ��5 8 5 2 9 ����һλѡ��ʱ5 ��2 ���� �����Ͳ����ȶ����ˣ���
template<class T>
void simpleselectsort(T a[], int size)
{
	int i, j, minx;
	T tmp;

	for (i = 0; i < size - 1; ++i)
	{
		minx = i;
		for (j = i+1; j < size; ++j)
		{
			if (a[j] < a[minx]) minx = j;
		}
		tmp = a[i];
		a[i] = a[minx];
		a[minx] = tmp;
	}
}


//������ ʱ�临�Ӷ�O(nlgn)
//��Ѳ�ͬ�ļ����У�
//1.һ�㽨�ѵ�ʱ���Ƚ�һ������
//2.���ӵ�Ԫ�طŵ���� Ȼ��size-1 �������Ա�����һ���������ĵĿռ�
//3.Ԫ�ز��ٴ�1��ʼ ����Ϊ������������ ��0��ʼ ����
//  ���i�ĸ��ڵ���(i-1)/2 �����2i+1 �Ҷ���2i+2 
//�������� ���ȶ�������
template<class T>
void heapsort(T a[], int size)
{
	int i;
	T tmp;
	//�Ƚ���
	for (i = size / 2-1; i >= 0; i--)
	{
		percolatedown(a, i, size);
	}

	for (i = size - 1; i > 0; --i)
	{
		tmp = a[0];
		a[0] = a[i];
		a[i] = tmp;
		percolatedown(a, 0,i);  //�ǵø��´�С ��Ϊ���滹�����޹ص�����
	}
}

template<class T>
void percolatedown(T a[], int i, int size)
{
	T tmp = a[i];
	int child;
	for (; i * 2 + 1 < size;)
	{
		child = 2 * i + 1;
		if (child != size - 1 && a[child + 1] > a[child]) child++;
		if (a[child] > tmp) {
			a[i] = a[child];
			i = child;
		}
		else break;

	}
	a[i] = tmp;
}

//ð������O(n^2)
//�ȶ�����
template<class T>
void bubblesort(T a[], int size)
{
	T tmp;
	bool flag;
	for (int i = 1; i < size; ++i)
	{
		flag = false;
		for (int j = 0; j < size - i; ++j)
		{
			if (a[j + 1] < a[j])
			{
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
				flag = true;
			}
			
		}
		if (!flag)break;  //���û������ ˵���Ѿ������� ��ʱ��ֽ����
	}
}


//�鲢����:O(nlgn) 
//�ȶ�����
template<class T>
void merge(T a[], int left, int mid, int right)
{
	T *tmp = new T[right - left + 1]; //��Ϊ��ʱ���������
	int i = left, j = mid, k = 0;

	while (i < mid &&j <= right) //����������ʱ
	{
		if (a[i] < a[j])
		{
			tmp[k++] = a[i++];
		}
		else
		{
			tmp[k++] = a[j++];
		}
	}
	while (i < mid) tmp[k++] = a[i++];
	while (j <= right) tmp[k++] = a[j++];

	for (i = 0, k = left; k <= right;) a[k++] = tmp[i++];
	//��ʱ��������ݹ��� ԭ��Ҫ���������
	delete[]tmp;
}

template<class T>
void mergesort(T a[], int left, int right)
{
	int mid = (left + right) / 2;
	if (left == right) return;
	
	mergesort(a, left, mid);
	mergesort(a, mid + 1, right);
	merge(a, left, mid + 1,right);
}
//���������������ǹ鲢���������䲽�� �� ������鲢
//��������������
template<class T>
void mergesort(T a[], int size)
{
	mergesort(a, 0, size - 1);
}

//��������ƽ��O(nlgn) �O(n^2) 
//���ȶ����� 
//ռ�Ӵ���
template<class T>
void quicksort(T a[], int low, int high)
{
	if (low >= high) return;
	int mid = partition(a, low, high);  //��[low,high] ����ѡ�� a[low]Ϊ��׼Ԫ�� �����������õ��±�
	quicksort(a, low, mid - 1);
	quicksort(a,mid + 1, high);
}

template<class T>
void quicksort(T a[],int size)
{
	quicksort(a, 0, size - 1);
}

template<class T>
int partition(T a[], int low, int high)
{
	T tmp = a[low];
	do
	{
		while (low < high && a[high] >= tmp) high--; //��high��û����low �����ҵ�һ����tmpС����ʱ����
		if (low < high) //������ҵ���tmpС��������������low�� ��ô����
		{
			a[low] = a[high];
			low++;
		}
		while (low < high && a[low] <= tmp) low++; //����������
		if (low < high)
		{
			a[high] = a[low];
			high--;
		}
	} while (low != high);

	a[low] = tmp;
	return low;
}

//����Ŀ��Ųο�Ԫ��ѡ��һ�� Ҳ�����������ѡ��
template<class T>
void randomquicksort(T a[], int size)
{
	randomquicksort(a, 0, size - 1);
}

template<class T>
void randomquicksort(T a[], int low, int high)
{
	if (low >= high) return;
	int mid = randompartition(a, low, high);
	randomquicksort(a, low, mid - 1);
	randomquicksort(a, mid + 1, high);
}

template<class T>
int randompartition(T a[], int low, int high)
{
	int random = rand() % (high - low) + low;
	swap(a[random], a[low]);

	//��һ������� ���� ��һ��Ԫ�� Ȼ�����֮ǰ�ľͺ���
	return partition(a, low, high);
}

//����ƽ����� ����ѡ����� ����ѡ���������β���м��������� �ҳ���ֵ ��Ϊ��׼Ԫ�أ�


//��������
//������
//�����ֶΣ��û�ѡ�� �ڴ��������n�� ��ô�ȶ���n�� ��ѡ����С���Ǹ��߳�ȥ֮�� �ڴ����һ��λ�ÿճ����� ��ʱ���Լ�����������
//          �������������ȸղű��߳�ȥ������ ��ô����ֱ�Ӳ������� �������С ��ô�����ڴ�֮���ܲ������� ��Ҫ�ȴ���һ��
//          ��ʱӦ�ð������ڴ�ִ�е������㷨��size-1
//��ͬ�Ŵ��е�����õ�СƬ��Ҫ�鲢��ͬһ���Ŵ��ķ�����
//1.��·�鲢��ѡ��·�鵽��һ���Ŵ� ��ѡ�����鵽��һ�� ���ϵ�ֻ��һ�� ����ÿ�ι�ģ����һ�� �����������Ƭ����M��
//            ��ô��Ҫlog2 M �ι鲢
//2.��·�鲢: K ���Ŵ��鲢���˷�����Ҫ2K���Ŵ��� ��ô����ͬʱ�鲢 K���ĵ�һ�����й鲢��һ������k+1���Ŵ���
//            ��������ÿ�ν���k-1�ȽϷ�ʱ ���Խ�һ����СΪk�Ķ� Ȼ��ÿ���߳�ȥ������������һ��Ԫ�ؽ���
//            �㷨�����϶�������һ�µ���Ŷ������ M��Ƭ����ҪlogK M �ι鲢
//3.��׶ι鲢	
template<class T>
void print(T a[], int size)
{
	for (int i = 0; i < size; ++i)
		cout << a[i] << " ";
	cout << endl;
}
int main()
{
	int a[] = { 40,25,1,32,24,68,24,10,69,23 };
	randomquicksort(a, 10);
	print(a, 10);
	return 0;
}