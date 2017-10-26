#include <iostream>

using namespace std;

//直接插入排序 二分插入排序 谢尔排序
//直接选择排序 冒泡排序
//堆排序 归并排序 快速排序
//外排序

//直接插入排序：从1遍历到n 分别从排序好的序列从尾向头遍历 插入到正确的位置
//时间复杂度O(n^2) 稳定排序
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

//二分查找排序：在从排序好的序列找位置时用二分查找
//但是移动的复杂度还是n 所以总的还是O(n^2) 稳定排序

//希尔排序：插入排序中一个元素如果要移动到较远的是被一步一步移过去的
//希尔排序有一个增量序列 只要保证最后是1-排序即可
//是不稳定的排序
template<class T>
void shellsort(T a[], int size)
{
	int step, i, j;
	T tmp;
	 
	for (step = size / 2; step >= 1; step /= 2)   //这里的增量序列采用二分直到1-排序
	{
		for (i = step; i < size; ++i)    //为什么从step开始？？ 因为第一个元素不用排！
		{
			tmp = a[i];
			for (j = i - step; j >= 0 && a[j] > tmp; j -= step) a[j + step] = a[j];
			a[j + step] = tmp;
		}
	}
}

//直接选择排序 容易理解 复杂度O(n^2)
//不稳定排序  如5 8 5 2 9 当第一位选择时5 与2 交换 那他就不是稳定的了！！
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


//堆排序 时间复杂度O(nlgn)
//与堆不同的几点有：
//1.一般建堆的时候先建一个最大堆
//2.出队的元素放到最后 然后size-1 这样可以避免另开一个数组消耗的空间
//3.元素不再从1开始 而是为了与其他兼容 从0开始 这样
//  结点i的父节点是(i-1)/2 左儿子2i+1 右儿子2i+2 
//堆排序是 不稳定的排序
template<class T>
void heapsort(T a[], int size)
{
	int i;
	T tmp;
	//先建堆
	for (i = size / 2-1; i >= 0; i--)
	{
		percolatedown(a, i, size);
	}

	for (i = size - 1; i > 0; --i)
	{
		tmp = a[0];
		a[0] = a[i];
		a[i] = tmp;
		percolatedown(a, 0,i);  //记得更新大小 因为后面还放着无关的数据
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

//冒泡排序：O(n^2)
//稳定排序
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
		if (!flag)break;  //如果没起泡了 说明已经结束了 及时剪纸！！
	}
}


//归并排序:O(nlgn) 
//稳定排序
template<class T>
void merge(T a[], int left, int mid, int right)
{
	T *tmp = new T[right - left + 1]; //作为临时数组放数据
	int i = left, j = mid, k = 0;

	while (i < mid &&j <= right) //当两表都还有时
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
	//临时数组的数据归入 原来要排序的数组
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
//以上两个函数就是归并的两个经典步骤 ： 排序与归并
//再来个包裹函数
template<class T>
void mergesort(T a[], int size)
{
	mergesort(a, 0, size - 1);
}

//快速排序：平均O(nlgn) 最坏O(n^2) 
//不稳定排序 
//占坑待填
template<class T>
void quicksort(T a[], int low, int high)
{
	if (low >= high) return;
	int mid = partition(a, low, high);  //对[low,high] 区间选择 a[low]为标准元素 返回他最后放置的下标
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
		while (low < high && a[high] >= tmp) high--; //当high还没遇到low 而且找到一个比tmp小的数时结束
		if (low < high) //如果是找到比tmp小的数而不是遇到low了 那么交换
		{
			a[low] = a[high];
			low++;
		}
		while (low < high && a[low] <= tmp) low++; //与上面类似
		if (low < high)
		{
			a[high] = a[low];
			high--;
		}
	} while (low != high);

	a[low] = tmp;
	return low;
}

//上面的快排参考元素选第一个 也有做法是随机选择
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

	//找一个随机的 换到 第一个元素 然后调用之前的就好了
	return partition(a, low, high);
}

//还有平衡快排 不是选用随机 而是选用数组的首尾和中间三个数据 找出中值 最为基准元素！


//计数排序
//外排序
//技巧手段：置换选择 内存可以容纳n个 那么先读入n个 在选出最小的那个踢出去之后 内存就有一个位置空出来了 此时可以继续从外存读入
//          如果被读入的数比刚才被踢出去的数大 那么可以直接参与排序 如果比他小 那么读入内存之后不能参与排序 需要等待下一轮
//          此时应该把正在内存执行的排序算法的size-1
//不同磁带中的排序好的小片段要归并到同一条磁带的方法：
//1.两路归并：选两路归到另一条磁带 再选两条归到另一条 不断到只有一条 由于每次规模减少一般 所以如果出事片段有M个
//            那么需要log2 M 次归并
//2.多路归并: K 条磁带归并（此方法需要2K条磁带） 那么可以同时归并 K条的第一条序列归并成一条到第k+1条磁带上
//            而且由于每次进行k-1比较费时 可以建一个大小为k的堆 然后每次踢出去的那条带进另一个元素进堆
//            算法导论上堆排序哪一章的题哦！！！ M个片段需要logK M 次归并
//3.多阶段归并	
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