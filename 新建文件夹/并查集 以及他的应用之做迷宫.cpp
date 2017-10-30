#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;

//不相交集（并查集）组织成一棵树  但是以数组形式存储
//如果是负数那么说明是一个集合的根节点 而绝对值可以是其规模 or 高度（看你是要按规模并还是按高度并）
//如果是正数则储存的是父节点的下标
//并的时候 如果按规模并：规模小的作为规模大的的子树  两根值需要加起来
//         如果按高度并：高度小的作为高度大的的子树  只有两根高度一样时高度大的需要+1 否则保持不变！
//所以 只有当两树（两集合）规模or高度相同时 他才会增加高度 这样可以减少find的时间
//所以 我们可以继续优化！！！！
//在执行find的时候 我们可以把沿路走过的路径全部设置为根节点的儿子 成为路径压缩
//因为理想状态下希望并查集树只有两层！
//但这种路径压缩方法 只与按规模并兼容 因为 路径压缩后不知道怎么计算高度！

//所以一般来说并查集 我们一般采用 按规模并+路径压缩的方法！！

class disjointset
{
public:
	int size;
	int *parent;


	disjointset(int s) :size(s)
	{
		parent = new int[size];
		for (int i = 0; i < size; ++i) parent[i] = -1;  //初始时候每个人都是自己一个集
	}
	~disjointset() { delete[]parent; }
	int find(int x);             //查
	void Union(int root1, int root2);  //并
};


//这个查找函数的递归也太巧妙了
//当我们找一个时 我们并不知道它上溯上去之后根节点是谁 所以没办法改啊！！
//但是没关系 我们用一个巧妙的递归 find(parent[x]) 它返回的就是根节点
//那么就是parent[x]=find(parent[x])了！！

/*int disjointset::find(int x)
{
	//需要做路径压缩！
	if (parent[x] < 0) return x;   //负数表示找到了根节点了
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
//当然了也可以用非递归的版本 效率差不多
//就是进行两次根回溯 第一次找到要填的序号
//第二次根回溯一路填序号！！


void disjointset::Union(int root1, int root2)  //这里你要手动保证他一定是root！！！可以优化
{
	if (root1 == root2) return;
	if (root1 > root2) Union(root2, root1);  //这个奇技淫巧应该是在二项队列里学到的嘻嘻嘻

	parent[root2] += parent[root1];
	parent[root1] = root2;
}


//并查集的应用之：迷宫
//方法是一直随机选一面墙 如果墙两边还不是同一个集合那就把墙拆了
//拆到起点和终点在同一个集合就行了
void createpuzzle(int size)
{
	int num1, num2;
	disjointset ds(size*size);  //二维化成一维

	
	while (ds.find(0) !=ds.find(size*size - 1))//两个数的find结果不同 就说明不属于同一个集合！！！
	{
		
		while (true)
		{
			
			num1 = rand()*size*size / (RAND_MAX + 1);  //随机选一个
			num2 = num1 - size;  //看看和它上面的
			if (num2 >= 0 && num2>=0 &&num2<size*size)
			{
				if (ds.find(num2) != ds.find(num1)) break;  //就是你们了
			}
			num2 = num1 - 1; //看看和它左边的
			if (num1%size!=0 && num2 >= 0 && num2<size*size)
			{
				if (ds.find(num2) != ds.find(num1)) break; //就是你们了
			}
			num2 = num1 + 1;//看看和它右边的
			if (num2%size != 0 && num2 >= 0 && num2<size*size) //不越界
			{
				if (ds.find(num2) != ds.find(num1))break;
			}
			num2 = num1 + size;
			if (num2<size*size&& num2 >= 0 && num2<size*size)
			{
				if (ds.find(num2) != ds.find(num1))break;
			}

		}
		ds.Union(ds.find(num1),ds.find(num2)); //之前说过了 需要自己保证是root ！！！ 那么可以用find来保证！！！
		cout << "<" << num1 << "," << num2 << ">" << endl;
	}
}




int main()
{
	srand(time(nullptr));
	createpuzzle(10);
	return 0;
}
