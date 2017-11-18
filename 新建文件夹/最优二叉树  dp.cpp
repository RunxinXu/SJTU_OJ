#include <iostream>
#include <string>
#include <queue>

using namespace std;

//最优二叉查找树
//最先先到的是贪婪法 就像哈夫曼树一样 
//但是他和hftree不同 所以只是局部最优解而不是全局最优解
//要得到全局最优解需要用动态规划dp
//其状态转移方程 见图片~~~~
//时间复杂度是O(n^3)

//可以形象地看作 捏起绳子的哪个点最好！！

struct node
{
	int root;
	double value;
};
struct queuenode
{
	int x, y;
};

//从树有 一个 两个 三个……结点开始构建
void optimalbst(string word[], double weight[], int size)
{
	node **tree;
	queue<queuenode> q;

	tree = new node*[size];
	for (int i = 0; i < size; ++i) tree[i] = new node[size];   
	for (int i = 0; i < size; ++i)
	{
		tree[0][i].root = i;
		tree[0][i].value = weight[i];
	}
	//这是树有一个结点的情况 作为初始值

	int root;
	for (int i = 1; i < size; ++i)
	{
		//一直构造到树有size个结点~就是最终的结果

		for (int j = 0; j < size - i; ++j)  //需要试这么多次
		{
			double optimalvalue = 1e10;
			double totalvalue = 0;

			//先是第一部分 即所有结点的代价
			for (int k = j; k <= i + j; ++k)
			{
				totalvalue += tree[0][k].value;   
			}
			for (int k = j; k <= i + j; ++k)
			{
				double tmpvalue = totalvalue;
				//第二部分 

				//第一个下标表示是树有几个结点的一行
				//第二个下标表示是这行按顺序的第几个

				if (k < i + j) tmpvalue += tree[i + j - k - 1][k + 1].value;
				if (k > j) tmpvalue += tree[k - j - 1][j].value;
				if (tmpvalue < optimalvalue)
				{
					optimalvalue = tmpvalue;
					root = k;
				}
			}

			tree[i][j].root = root;  //从第一行可得知这个数字对应哪个
			tree[i][j].value = optimalvalue;
		}
	}

	//输出
	queuenode tmp;
	tmp.x = size - 1;
	tmp.y = 0;
	//从结果回溯才可以输出
	
	//回溯的关键是确定下一个的坐标 而坐标第一个就是确定结点个数 第二个坐标就是确定子树最左边元素是第几个 以确定他是第几个序列





	q.push(tmp);
	while (!q.empty())
	{
		tmp = q.front();
		q.pop();
		queuenode tmp1, tmp2;

		tmp1.x = tree[tmp.x][tmp.y].root - tmp.y - 1; //左子树的个数对应的下标 
		tmp1.y = tmp.y;    //是对应的第几种序列 由于最左边的元素相同 所以相等

		tmp2.x = (tmp.x + tmp.y + 1) - 1 - tree[tmp.x][tmp.y].root - 1; 
		//右子树结点的个数是 （总个数）-1 -tree[tmp.x][tmp.y].root  ==========>
		//对应下标需要-1
		tmp2.y = tree[tmp.x][tmp.y].root + 1;  //最左边的是根的右边的那个


		string lchild, rchild;
		if (tmp1.x < 0) lchild = "";
		else
		{
			lchild = word[tree[tmp1.x][tmp1.y].root];
			q.push(tmp1);
		}
		if (tmp2.x < 0) rchild = "";
		else
		{
			rchild = word[tree[tmp2.x][tmp2.y].root];
			q.push(tmp2);
		}

		cout << word[tree[tmp.x][tmp.y].root] << "的左儿子是" << lchild << " 右儿子是" << rchild << endl;
	}
}

int main()
{
	string hehe[] = { "ff","banana","apple" };
	double weight[] = { 12,2.0,3.6 };
	optimalbst(hehe, weight, 3);

	return 0;
	
}