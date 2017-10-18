#include <iostream>


using namespace std;

//KMP算法字符串匹配！ 时间复杂度O（n）
int find(const char*a, const char*b)
{
	//在a中找有无b子串
	int a_size = strlen(a);
	int b_size = strlen(b);

	//先预处理字符串b 生成一个失效函数
	int *p = new int[b_size];
	int j;

	p[0] = -1;
	for (int i = 1; i < b_size; ++i)
	{
		j = i - 1; //j为i的前一个下标
		while (j >= 0 && b[p[j] + 1] != b[i]) j = p[j];
		//如果b[p[j] + 1] == b[i] 那么显然可以p[j]+1即可
		//如果j<0 说明已经找不到了 那么这个p[i]即为-1  也就是再怎么缩小也找不到满足 前x个和后x个相同
		if (j < 0) p[i] = -1;
		else p[i] = p[j] + 1;
	}

	//这个预处理是非常精妙的 具体图示可以见图


	//接下来是KMP算法主要流程 同样精彩 注意当j=0时说明上一部退化成了-1 此时只需要增加i到重新匹配到第一个之后再进行
	int i = 0;
	j = 0;
	while (i < a_size && j < b_size)
	{
		//匹配到a[i] 与b[j]
		if (a[i] == b[j])
		{
			i++;
			j++;
		}
		else
		{
			if (j == 0) //上一部退化成了j=-1;
				i++;
			else
				j = p[j-1]+1; //退化！
			//注意j是准备去匹配的 而j-1是已经匹配上的 所以退化时用的是p[j-1] 加一则是更新 匹配下一个！
		}
	}
	delete[]p;
	if (j == b_size) //匹配到了全部 
		return i - b_size;   //返回在a的下标第一个
	else
		return -1; //匹配失败
}


int main()
{
	char* a = "asdf;kjasdffkljasf";
	char *b = "sdffkl";
	cout << find(a, b);


	return 0;
}