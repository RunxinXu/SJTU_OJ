#include <iostream>
#include <queue>
#include <stack>
using namespace std;

//图的实现可以用邻接矩阵（空间O(v*v)）或者邻接表（空间o(v+e)）来记录边和点
//基本操作是插入边 删除边 边的数目 结点的数目 以及某条边是否存在 这都比较容易实现

//图的遍历包括dfs遍历和bfs遍历 
//dfs遍历借助于递归 深度优先 
//bfs遍历借助于队列 广度优先
//共同点是都需要一个visited数组记录点是否已经被访问 
//以及 若为无向图 则连通图一次遍历就够
//若为有向图 一个强连通极大子图一次  多个则为森林

//图的遍历有多种应用
//1.无向图是否连通
//2.拓扑排序 包括基于dfs和bfs的
//  基于bfs用入度 不断将入度为0的点入队 并且后继结点入度-1 不断循环即可
//  基于dfs的用栈  对于排在前面的肯定要等到排在后面的都遍历完了再回到这 所以可以等遍历完一个结点的后续结点后将其入栈 这样栈内就是其拓扑排序~
//3.找欧拉回路 
//  对于无向图 欧拉路径存在的充要条件是 小于等于两个点的度数为奇数  
//             欧拉回路存在的充要条件是 所有点的读书为偶数
//  对于有向图 欧拉路径存在的充要条件是 有一点的入度比出度大1 有一点的入度比出度小1 其他入度均等于出度 
//             欧拉回路存在的充要条件是 所有点的入度等于出度
//  原则是先判断看看有没有   之后再找出来 都是先找一个回路 然后若有边剩余就继续找回路加进去！一直到所有边都删完！
//  这里实现了一个无向图的欧拉回路 
//  举一反三 无向图的欧拉道路只需要找出两个奇数度的一个做起点 一个做终点 其他都同样 初始遍历时也无需判断 自动停止时就在终点 因为已经满足充要条件
//            之后再不断扫描添加可以加入欧拉道路的回路~
//  有向图的欧拉回路 和 欧拉道路 和无向图基本上一样~ 其实无向图就是特殊的有向图~
//4.有向图的强连通分量 Tarjan算法和Kosaraju算法
//Kosaraju算法：dfs拓扑排序=》逆转图=》按前面的排序顺序dfs遍历=》恢复图       时间O(v+e) 但需要dfs两次 还需要逆转图 效率低于Tarjan
//Tarjan算法：本质是dfs树结点能否回到更上面的结点从而形成强分支分量    用到了两个记录序列 一个是时间戳访问次序visited 一个是记录其ancestor
//            按dfs顺序 对于某个结点i 首先设置它的ancestor[i]为他本身的序号（时间戳） 然后遍历它的后继结点 
//            如果后继结点已经属于一个强连通分支  那么无视它
//            如果后继结点未被访问过 那么递归访问它 如果它的ancestor比ancestor【i】更前 那么更新ancestor[i]
//            如果后继结点已经在此次dfs中被访问过 说明他在dfs树的上方或者是i本身 那么直接设置ancestor[i]等于它的ancestor 
//                                                即可以理解为它无论如何都比i要高级 只要跟着它就对了
//            这样只需要一次dfs  虽然时间也是O(v+E) 但是常数因子会比较小
//            理解起来比Kosaraju难 然而写起来却比它容易 因为步骤少
// (已有主 无视他；未访问 试试看；已访问 跟着他）
//5.判断图是否有环：
//无向图：n算法：  
//第一步：删除所有度 <= 1的顶点及相关的边，并将另外与这些边相关的其它顶点的度减一。
//第二步：将度数变为1的顶点排入队列，并从该队列中取出一个顶点重复步骤一。
//如果最后还有未删除顶点，则存在环，否则没有环。
//其原理是 若有环 那环内结点的度数必定大于等于2且无法因为被删去而减少
//有向图：
//用dfs 并假设每个结点有三个状态 白色：未被访问过 灰色：开始访问某个节点 黑色：该结点的所有后继路径结点已被访问完
//那么在反问过程中 如果遇到白色结点 那显然没问题 遇到黑色也没问题 因为他之后的路径已经被访问过 被事实证明不会形成环
// 而若遇到灰色结点 则说明形成了环 （灰色的结点表示正在考察中的意思） （黑色可以理解为通过了考察）
//在这里具体实现时可以看作（按手指点灯~~)


//dfs遍历 bfs遍历 有向图的强连通分支等等 都是适用于结果为森林的 这也是其for(int i=0;i<vers;++i) 的原因！！

//最小生成树问题： 常用两种算法 prim算法和kruskal算法
//kruskal比较容易 用并查集+优先队列可以实现 
//优先队列O(ElgE) 而并查集查询是对数级的O(lgV) 故不断加边的过程是O(ElgV) 由于一般E>V 所以总的时间复杂度是O(ElgE)
//prim算法：集合U初始化为空 不断选U 到V-U最短路径的V-U中的点加入U 直到U=V
//          时间复杂度为O(V^2)
//          一般用三个数组来记录 一个flag数组记录是否已经加入U 
//                               一个startnode数组记录从哪个点到达的这个新加入U的点 使得可以输出边的起始点和终止点
//                               一个lowcost数组记录对于U-V中的某个点 从U中的点到达它的最小的权




//单源最短路径问题：
//1.无权图的最短路径 ：用bfs（队列） 并用两个数组记录 一个记录当前的距离 一个记录上一个结点用于打印路径
//                     每个节点都入队O(V) 每条边也都检查O(E) 时间复杂度为O(V+E) 相当于一次bfs遍历
//                     打印路径时由于prenode数组存的是上一个结点 所以用递归打印特别直观简单！
//2.有正值权图的最短路径： Dijkstra算法
//                     三数组：一个flag数组记录是否已经纳入U or还是在V-U 
//                             一个prenode数组记录前一个结点 用于打印路径
//                             一个distance数组记录当前记录的最短路径 
//                     三数组~类似与prim算法！ 区别是prim算法的记录距离的数组记录的是从U所有点到U-V某个点的一个最短距离！！！！
//                                              而Dijkstra算法记录的是到源点的当前的最短距离！！
//              算法本身：不断从V-U中选出distance最小的结点i加入U 并更新i的所有后继结点的距离信息 循环至U=V
// Dijkstra主要就是 在加入一个结点后找出下一个最小结点  O(v^2)
//                   更新 O(E)
//                  所以时间复杂度是O(v^2+E) 即O(v^2)  所以可以通过一个优先级队列优化成O(vlgv）
//（如果想输出 路径长度相同时经过结点最少的 那就再开一个数组记录路径上的结点数就好了啊！！！）
//4.无环图的最短路径：用拓扑排列顺序遍历更新结点
//                    
//                    也是用Dijkstra算法 但是时间复杂度可以简化到O(V+E)
//                     原因是它用拓扑排序的顺序去更新点   源点一定要是一个入度为0的结点 否则不可达
//                    方法就是Dijkstra时 不再是选点加入U集并找V-U集最小值
//                    而是按拓扑排序的顺序遍历更新 ！ 这样问题转化为线性！！！
//                    由于有了拓扑排序 所以又是三数组 prenode distance 和一个indegree
//        由于本质上还是Dijkstra 所以不能用于有负值权的图！！！！

//插曲：有向无环图的最长路径常常用来衡量工作线的所需最小时间！！成为关键路径 即从起点到终点的最长路径（无环）
//      正因为无环研究最长才有意义好吗！！！3

//实现方法基本上就是上面的按拓扑排序遍历的Dijkstra算法 只不过初始的时候distance初始化为0 而每次更新是如果比它大就更新
//其他可以说是一样的！！！ 最后一个结点的distance就是最长路径的距离 递归pringpath即可！！！


//3.有负值权图的最短路径（没有负环 否则无解）：
//                      其实想起来就是Dijkstra算法的简化版本   
//                      用一个队列 一开始把start入队 之后循环的出队 并更新出队结点的后继结点 有更新的重新入队
//                      如此循环直至队列空
//                      所以他只需要两个数组 记录prenode和distance 而不用flag标志 因为他没有U V-U 之分
//                      它的终止条件是 不能再更新了！！
//              每个点最多入队E次 所以时间复杂度为O(E*V)




//所有结点之间最短路径问题：
//1.对每个结点用个Dijkstra  那时间复杂度是O(v^3)
//2.floyd算法： 也是O(v^3) 但更简单直观 基于邻接矩阵
//              先有一个v*v数组d 初始化成和邻接矩阵一样
//              之后进行v次迭代 对于第k次迭代更新
//               dk[i][j]=min( dk-1[i][j], dk-1[i][k]+dk-1[k][j]) //
//              直观理解就是对于每一个结点进行一次迭代 把它当作中间结点 去更新信息 
//              如果i绕路到k再到j 会比它之前到j的距离更短  那就更新它！！

//              打印路径保存路径用一个二维数组PATH[V][V] 对于path[i][j] 表示 从i到j的最短路径的倒数第二个结点
//              那么我们可以利用递归 继续找path[i][这倒数第二个结点] 知道path[i][j]=i 表示到头了~！ 
//              简单易懂！又粗暴！！


//实际上 对每个结点用个Dijkstra算法 会被其算法本身不能解决带有负值权边的图的问题所制约
//而floyd算法可以解决负值权边的图的问题！！！
//但是同样的 他不能用于负值环的图 因为那样根本没有最短路径~可以无限刷！








template<class T> //T是边的类型
class graph
{
public:
	virtual bool insert(int u, int v, T w) = 0;
	virtual bool remove(int u, int v) = 0;
	virtual bool exist(int u, int v)const = 0;
	virtual int numofver()const { return vers; }
	virtual int numofedge()const { return edges; }
protected:
	int vers, edges;
};
//基类


//基于邻接矩阵的图
//创建一个基于邻接矩阵的图的空间复杂度是O（V*V)
template<class TV, class T> //分别是结点值的类型和边的类型
class adjmatrixgraph :public graph<T>
{
public:
	adjmatrixgraph(int size, const TV d[], const T noedgeflag);
	bool insert(int u, int v, T w);
	bool remove(int u, int v);
	bool exist(int u, int v)const;
	~adjmatrixgraph();
	void dfs();
	void bfs();
	//floyd算法
	void floyd()const;

private:
	T **edge;
	TV* ver;
	T noedge;
	void dfs(int i, bool*visited);

	

};

template<class TV, class T>
adjmatrixgraph<TV, T>::adjmatrixgraph(int size, const TV d[], T noedgeflag)
{
	int i, j;
	vers = size;  //结点数
	edges = 0;
	noedge = noedgeflag;  //没有边的标记

	ver = new TV[size];
	for (int i = 0; i < size; ++i) ver[i] = d[i];

	edge = new T*[size];
	//对邻接矩阵初始化
	for (i = 0; i < size; ++i)
	{
		edge[i] = new T[size];
		for (j = 0; j < size; ++j) edge[i][j] = noedge;
	
	}
}

template<class TV, class T>
adjmatrixgraph<TV, T>::~adjmatrixgraph()
{
	delete[]ver;
	for (int i = 0; i < vers; ++i) delete[]edge[i];
	delete[]edge;
}


template<class TV, class T>
bool adjmatrixgraph<TV, T>::insert(int u, int v, T w)
{
	if (u<0 || u>vers - 1 || v<0 || v>vers - 1) return false;
	if (edge[u][v] != noedge) return false;
	edge[u][v] = w;
	++edges;
	return true;
}

template<class TV, class T>
bool adjmatrixgraph<TV, T>::remove(int u, int v)
{
	if (u<0 || u>vers - 1 || v<0 || v>vers - 1) return false;
	if (edge[u][v] != noedge) return false;
	edge[u][v] = noedge;
	--edges;
	return true;
}

template<class TV, class T>
bool adjmatrixgraph<TV, T>::exist(int u, int v)const
{
	if (u<0 || u>vers - 1 || v<0 || v>vers - 1) return false;
	if (edge[u][v] != noedge) return false;
	return true;
}


template<class TV,class T>
void adjmatrixgraph<TV, T>::dfs()
{
	bool *visited = new bool[vers];
	for (int i = 0; i < vers; ++i) visited[i] = false;

	for (int i = 0; i < vers; ++i)
	{
		if (visited[i] == true) continue;
		
		dfs(i, visited);
		cout << endl;
	}
}

template<class TV,class T>
void adjmatrixgraph<TV, T>::dfs(int i, bool*visited)
{
	cout << ver[i] << " ";
	visited[i] = true;
	for (int j = 0; j < vers; ++j)
	{
		if (edge[i][j] != noedge && !visited[j])
		{
			dfs(j, visited);
		}
	}
}

template<class TV,class T>
void adjmatrixgraph<TV, T>::bfs()
{
	bool *visited = new bool[vers];
	for (int i = 0; i < vers; ++i) visited[i] = false;

	queue<int> hehe;
	for (int i = 0; i < vers; ++i)
	{
		if (visited[i] == true) continue;
		hehe.push(i);
		while (!hehe.empty())
		{
			int tmp = hehe.front();
			hehe.pop();
			if (visited[tmp] == true) continue;
			cout << ver[tmp] << " ";
			visited[tmp] = true;
			for (int j = 0; j < vers; ++j)
			{
				if (edge[tmp][j] != noedge && visited[j] == false) hehe.push(j);
			}

		}
		cout << endl;
		
	}

}

template<class TV,class T>
void adjmatrixgraph<TV, T>::floyd()const
{
	T**d = new T*[vers];
	for (int i = 0; i < vers; ++i)
	{
		d[i] = new T[vers];
		for (int j = 0; j < vers; ++j)
		{
			d[i][j] = edge[i][j];
		}
	}

	int **prenode = new int*[vers];
	for (int i = 0; i < vers; ++i)
	{
		prenode[i] = new int[vers];
		for (int j = 0; j < vers; ++j)
		{
			prenode[i][j] = edge[i][j] == noedge ? -1 : i;
			//如果i和j右边 那么就填i 
			//如果没边 那就-1 表示相连
		}
	}


	//floyd算法过程
	for (int k = 0; k < vers; ++k)
	{
		for (int i = 0; i < vers; ++i)
		{
			for (int j = 0; j < vers; ++j)
			{
				if (d[i][k] + d[k][j] < d[i][j])
				{
					d[i][j] = d[i][k] + d[k][j];  //更新最短路径
					prenode[i][j] = prenode[k][j];//这步可能有点难理解 
				}
			}
		}
	}

	//输出
	cout << "最短路径长度：" << endl;
	for (int i = 0; i < vers; ++i)
	{
		for (int j = 0; j < vers; ++j)
		{
			cout << d[i][j] << " ";
		}
		cout << endl;
	}

	cout << "最短路径：" << endl;
	for (int i = 0; i < vers; ++i)
	{
		for (int j = 0; j < vers; ++j)
		{
			cout << prenode[i][j] << " ";
		}
		cout << endl;
	}
}


//--------------------------------------------------------------------//
//--------------------------------------------------------------------//
//--------------------------------------------------------------------//
//--------------------------------------------------------------------//
//--------------------------------------------------------------------//


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

int disjointset::find(int x)
{
//需要做路径压缩！
if (parent[x] < 0) return x;   //负数表示找到了根节点了
else
return parent[x] = find(parent[x]);
}

void disjointset::Union(int root1, int root2)  //这里你要手动保证他一定是root！！！可以优化
{
	if (root1 == root2) return;
	if (root1 > root2) Union(root2, root1);  //这个奇技淫巧应该是在二项队列里学到的嘻嘻嘻

	parent[root2] += parent[root1];
	parent[root1] = root2;
}



struct eulernode
{
	int num;
	eulernode* next;

	eulernode(int a) :num(a), next(nullptr) {};
};

//基于邻接表的图  用链表保存从一个结点出发的所有终点
//如果是无向图 则每条边会在邻接表中出现两次
//创建一个基于邻接表的图的空间复杂度是O（V+E）
template<class TV, class T>
class adjlistgraph :public graph<T>
{

public:
	struct edgenode  //保存边的结点
	{
		int end;
		T weight;
		edgenode* next;

		edgenode(int e, T w, edgenode* n = nullptr) :end(e), weight(w), next(n) {};
	};

	struct vernode
	{
		TV ver;  //起点
		edgenode* head;//头结点

		vernode(int v = 0, edgenode* h = nullptr) :ver(v), head(h) {};
	};
	struct edge
	{
		int begin, end;
		T w;
		bool operator<(const edge&p) const { return w < p.w; }

	};

	vernode* verlist;

	void dfs(int i, bool* visited) const;
	void toposort_dfs(int i, bool* visited, stack<int>& hehe) const;
	eulernode* eulercircuit(int i, eulernode* end);
	vernode* clone()
	{
		vernode* hehe = new vernode[vers];
		edgenode* p;

		for (int i = 0; i < vers; ++i)
		{
			hehe[i].ver = verlist[i].ver;
			p = verlist[i].head;
			while (p)
			{
				hehe[i].head = new edgenode(p->end, p->weight, hehe[i].head);  //不断放在前面
				p = p->next;
			}
		}
		return hehe;
	}

	bool isdag(int i, bool* visited)const;
	void find(int start, int m, int &top, bool *visited, int *st)const;
	bool check(int start, int end, bool*visited)const;

	void findstrong_toposort(stack<int>&hehe) const;
	void findstrong_dfs(int start, vernode*tmpv, bool*visited)const;
	int findstrong_tarjan(int start, int *visited, int *ancestors, int &seqno, int&numofstrong)const;


	void printpath(int i,int*prenode) const;
public:
	adjlistgraph(int size, const TV d[]);
	bool insert(int u, int v, T w);
	bool remove(int u, int v);
	bool exist(int u, int v)const;
	~adjlistgraph();


	void dfs()const;   //深度优先遍历
	void bfs()const;   //广度优先遍历

					   //注意：拓扑排序只适用于有向无环图
	void toposort_bfs() const;   //基于bfs的拓扑排序
	void toposort_dfs() const;   //基于dfs的拓扑排序

	//无向图的连通性 等价于 遍历的时候（无论dfs or bfs）只有一棵遍历树而没有森林  即随便找一点进行一次遍历就可以遍历到全部结点
	//有向图的连通性 包括有向图的强连通和弱连通 
	//有向图的弱联通等价于无向图的连通性
	//而有向图的强连通则需要借助一定的算法
	void findstrong_k() const;
	void findstrong_tarjan()const;   


	//寻找无向图的欧拉回路
	void euler(TV start);

	//寻找无向图的欧拉道路
	//和欧拉回路的区别只是充要条件的判断和起始序号
	//它还是会自动停！！！
	//就连clone eulercircuit函数都可以公用！！！
	void euler(); //起点终点是哪两个是确定的 无需用户制定


	//判断是否为有向无环图（DAG）
	bool isdag() const;

	//给出指定点开始的所有路径长为m的简单路径（无环）
	//dfs+回溯法
	void find(TV start, int m)const;

	//给出指定的两个点是否有存在路径  
	//一个简单的dfs应用而已~检查到了就return true 找到最后也没找到就return false
	bool check(TV start, TV end)const;

	//Kruskal算法求最小生成树
	//并查集+优先队列 无难度  O(ElgE)
	void kruskal()const;

	//prim算法求最小生成树
	void prim(T noedge)const;  //需要用户提供一个表示无穷大的标记

	//无权图最短路径
	void unweightedshortdistance(TV start, T noedge)const;

	//正权图最短路径 ：Dijkstra算法
	void dijkstra(TV start, T noedge) const;

	//有负权图的最短路径
	void minusshortdistance(TV start, T noedge)const;
	
	//无环图的最短路径
	void dagshortdistance(TV start, T noedge)const;

};

template<class TV, class T>
adjlistgraph<TV, T>::adjlistgraph(int size, const TV d[])
{
	vers = size;
	edges = 0;

	verlist = new vernode[vers];
	for (int i = 0; i < vers; ++i) verlist[i].ver = d[i];


}

template<class TV, class T>
adjlistgraph<TV, T>::~adjlistgraph()
{
	edgenode* p;
	for (int i = 0; i < vers; ++i)
	{

		while (p = verlist[i].head)
		{
			verlist[i].head = p->next;
			delete p;
		}

	}
	delete[]verlist;
}

template<class TV, class T>
bool adjlistgraph<TV, T>::insert(int u, int v, T w)
{
	if (u<0 || u>vers - 1 || v<0 || v>vers - 1) return false;

	edgenode* q = new edgenode(v, w, verlist[u].head);
	verlist[u].head = q;
	++edges;
	return true;
}

template<class TV, class T>
bool adjlistgraph<TV, T>::remove(int u, int v)
{
	if (u<0 || u>vers - 1 || v<0 || v>vers - 1) return false;
	edgenode* p = verlist[u].head;
	if (p == nullptr) return false;

	if (p->end == v)
	{
		verlist[u].head = p->next;
		delete p;
		--edges;
		return true;
	}

	while (p->next && p->next->end != v) p = p->next;
	if (!p->next) return false;
	else
	{
		edgenode* tmp = p->next;
		p->next = p->next->next;
		delete tmp;
		--edges;
		return true;
	}
}

template<class TV, class T>
bool adjlistgraph<TV, T>::exist(int u, int v) const
{
	if (u<0 || u>vers - 1 || v<0 || v>vers - 1) return false;
	edgenode*p = verlist[u].head;
	while (p)
	{
		if (p->end != v) p = p->next;
		else break;
	}


	if (!p) return false;
	else return true;
}


//深度优先遍历dfs
//用邻接表时dfs的时间复杂度是O(V+E）
//用邻接矩阵则为O(V²)
template<class TV, class T>
void adjlistgraph<TV, T>::dfs()const
{
	bool *visited = new bool[vers]; //是否访问过的标记数组！

	for (int i = 0; i < vers; ++i) visited[i] = false;

	for (int i = 0; i < vers; ++i)
	{
		if (visited[i] == true) continue; //如果已经访问过了 那么就不要它
		cout << verlist[i].ver << " ";
		visited[i] = true;
		dfs(i, visited);  //调用私有dfs函数进行深搜
		cout << endl;   //一棵深搜树出来 换行 每一行是一棵深搜树
	}
}

template<class TV, class T>
void adjlistgraph<TV, T>::dfs(int i, bool* visited) const
{
	edgenode* p = verlist[i].head;
	while (p)
	{
		if (visited[p->end] == true) p = p->next;
		else
		{
			cout << verlist[p->end].ver << " ";
			visited[p->end] = true;
			dfs(p->end, visited);
			p = p->next;
		}
	}
}

//广度遍历BFS
//用邻接表时bfs的时间复杂度是O(V+E）
//用邻接矩阵则为O(V²)
template<class TV, class T>
void adjlistgraph<TV, T>::bfs()const
{
	bool *visited = new bool[vers];
	for (int i = 0; i < vers; ++i) visited[i] = false;
	queue<int> hehe;

	for (int i = 0; i < vers; ++i)
	{
		if (visited[i] == true) continue;
		hehe.push(i);
		while (!hehe.empty())
		{
			int tmp = hehe.front();
			hehe.pop();
			if (visited[tmp] == true) continue;// 如果弹出来的已经访问过了 那么跳过
			else
			{
				//否则输出
				cout << verlist[tmp].ver << " ";
				visited[tmp] = true;
				//然后把它的未访问的后继结点也都加进去
				edgenode* p = verlist[tmp].head;
				while (p)
				{
					if (visited[p->end] == false) hehe.push(p->end);
					p = p->next;
				}
			}

		}
		cout << endl; //一行是一棵广搜树
	}
}

//基于bfs 邻接表的拓扑排序时间复杂度O(v+E)
template<class TV, class T>
void adjlistgraph<TV, T>::toposort_bfs()const
{
	queue<int> hehe;
	edgenode* p;
	int *indegree = new int[vers];
	//先统计每个结点的入度
	for (int i = 0; i < vers; ++i)
	{
		indegree[i] = 0;
	}

	for (int i = 0; i < vers; ++i)
	{
		p = verlist[i].head;
		while (p)
		{
			++indegree[p->end];
			p = p->next;
		}
	}

	//寻找入度为0的入队
	for (int i = 0; i < vers; ++i)
	{
		if (indegree[i] == 0) hehe.push(i);
	}

	//进行拓扑排序
	int tmp;
	while (!hehe.empty())
	{
		tmp = hehe.front();
		hehe.pop();
		cout << verlist[tmp].ver << " ";
		p = verlist[tmp].head;
		while (p)
		{
			--indegree[p->end];
			if (indegree[p->end] == 0) hehe.push(p->end);
			p = p->next;
		}

	}
}

//基于dfs的拓扑排序
template<class TV, class T>
void adjlistgraph<TV, T>::toposort_dfs()const
{
	stack<int> hehe;
	bool*visited = new bool[vers];
	for (int i = 0; i < vers; ++i) visited[i] = false;
	for (int i = 0; i < vers; ++i)
	{
		if (visited[i] == true) continue;
		visited[i] = true;
		toposort_dfs(i, visited, hehe);
	}
    

	while (!hehe.empty())
	{
		int tmp = hehe.top();
		cout << verlist[tmp].ver << " ";
		hehe.pop();
	}

}

template<class TV,class T>
void adjlistgraph<TV, T>::toposort_dfs(int i, bool*visited, stack<int>& hehe) const
{
	edgenode*p = verlist[i].head;
	while (p)
	{
		if (visited[p->end] == true)
		{
			p = p->next;
			continue;
		}
		visited[p->end] = true;
		toposort_dfs(p->end, visited, hehe);
		p = p->next;
	}
	hehe.push(i);
}

template<class TV,class T>

//寻找无向图的欧拉回路
void adjlistgraph<TV, T>::euler(TV start)
{
	eulernode *beg=nullptr, *end=nullptr, *p = nullptr, *q = nullptr, *tb = nullptr, *te = nullptr;  //begin end 为起点终点
	int numofdegree;
	edgenode* r;
	vernode *tmp;

	if (edges == 0)
	{
		cout << "no" << endl;   //没有边 则不存在欧拉回路
		return;
	}
	//检查其充要条件：所有点的度数为偶数
	for (int i = 0; i < vers; ++i)
	{
		numofdegree = 0;
		r = verlist[i].head;
		while (r)
		{
			numofdegree++;
			r = r->next;
		}
		if (numofdegree == 0 || numofdegree % 2 != 0) {
			cout << "no" << endl; return;
		}

	}

	//找到用户要求的那个起始点
	int i;
	for (i = 0; i < vers; ++i)
	{
		if (verlist[i].ver == start) break;
	}
	if (i == vers) {
		cout << "no" << endl; return;
	}

	tmp = clone();  //保存一个副本 等下可以恢复

	beg = eulercircuit(i, end);   //end只是作为一个接受结果的参数 因为要返回首尾~  
	                              //这个函数就是返回一个i的回路的路径首尾（链表形式）
	
	while (true)
	{
		p = beg;
		while (p->next != nullptr)
		{
			//对第一条初始回路 依次扫描上面的点 用来将剩下的边都纳入欧拉回路中
			if (verlist[p->next->num].head != nullptr)
			{
				//如果还有边没纳入
				break;
			}
			else
				p = p->next;  //通过检查 继续检查下一个点
		}
		if (p->next == nullptr) //所有都通过了检查 
			break;
		else
		{
			q = p->next;
			tb = eulercircuit(q->num, te);  //探索一条回路
			//纳入欧拉回路中~
			te->next = q->next;
			p->next = tb;
			delete q;
		}
	}

	delete[]verlist;
	verlist = tmp;//恢复原图

	while (beg)
	{
		cout << verlist[beg->num].ver << " ";
		p = beg;
		beg = beg->next;
		delete p;
		
	}

}

template<class TV,class T>
eulernode* adjlistgraph<TV, T>::eulercircuit(int start, eulernode* end)
{
	eulernode* beg;
	int nextnode;

	beg = end = new eulernode(start);
	while (verlist[start].head != nullptr)
	{
		nextnode = verlist[start].head->end;
		//探索下一个点

		remove(start, nextnode);
		remove(nextnode, start);//无向图出现两次！

		start = nextnode;
		end->next = new eulernode(start);
		end = end->next;
	}
	//一个非常厉害的细节就是 不用特意去限制什么有一次到了start 因为已经过了充要条件的判断 那么它一定是存在的！！
	//只需要无脑dfs 停了的时候就是到了start了！！！！

	return beg;
}

//判断是否为有向无环图
template<class TV,class T>
bool adjlistgraph<TV, T>::isdag()const
{
	bool*visited = new bool[vers];
	for (int i = 0; i < vers; ++i) visited[i] = false;

	for (int i = 0; i < vers; ++i)
	{
		if (!isdag(i, visited)) return false; 
		visited[i] = flase;     //为考察下一个结点做准备
	}
}

template<class TV,class T>
bool adjlistgraph<TV, T>::isdag(int i, bool*visited)const
{
	//在考察中的即为true
	edgenode* p = verlist[i].head;
	visited[i] = true;

	while (p)
	{
		if (visited[p->end] == true) return false;
		if (!isdag(p->end, visited)) return false;  
		//来到了这步说明通过p->end 的路径没有与之前路径上的点（true的）形成环 那么解除他的访问状态
		//考察下一个结点 
		//可以解除的原因是 接下来其他路径就算访问到他 他也已经经受了考察 不会形成环 ~所以可以看成unvisited
		visited[p->end] = false;   //这步就是精华啊！！
		p = p->next;
	}
	return true;
}

//找长度为m的简单路径
template<class TV,class T>
void adjlistgraph<TV, T>::find(TV start, int m)const
{
	bool* visited = new bool[vers];
	for (int i = 0; i < vers; ++i) visited[i] = false;

	int *st = new int[m + 1];
	int top = 0;   
	int i;
	//找到开始的结点对应的内部序号
	for (i = 0; i < vers; ++i)
		if (verlist[i].ver == start) break;
	if (i == vers)
	{
		cout << "no" << endl;
		return;
	}
	find(i, m, top, visited, st);
}

template<class TV,class T>
void adjlistgraph<TV, T>::find(int start, int m, int &top, bool*visited, int*st)const
{
	edgenode*p = verlist[start].head; //指向start接下来的结点们
	visited[start] = true;
	st[top++] = start;
	if (top == m + 1)
	{
		//已经够m了 那么把他输出
		for (int i = 0; i < top; ++i)
		{
			cout << verlist[st[i]].ver << " ";
		}
		visited[start] = false;
		--top;
		return;  //类似于回溯法 把状态还原 之后回溯! 八皇后问题
	}

	//如果还没满
	while (p)
	{
		if (visited[p->end] == true)
		{
			p = p->next;
			continue;
		}
		else
		{
			find(p->end, m, top, visited, st);
			p = p->next;
		}
	}

	visited[start] = false;
	--top;
	return;
	//这个也是一个回溯~
}

//检查两个结点间是否有路径
template<class TV,class T>
bool adjlistgraph<TV, T>::check(TV start, TV end)const
{
	bool*visited = new bool[vers];
	for (int i = 0; i < vers; ++i) visited[i] = false;

	int i, j;
	for (i = 0; i < vers; ++i)
		if (verlist[i].ver == start) break;
	if (i == vers) { cout << "no" << endl; return false; }
	for (j = 0; j < vers; ++j)
		if (verlist[j].ver == end) break;
	if (j == vers) { cout << "no" << endl; return false; }
	

	return check(i, j, visited);
}

template<class TV,class T>
bool adjlistgraph<TV, T>::check(int start, int end, bool*visited)const
{
	edgenode*p = verlist[start].head;
	visited[start] = true;

	while (p)
	{
		if (p->end == end) return true;
		if (visited[p->end] == true)
		{
			p = p->next;
			continue;
		}
		else
		{
			if (check(p->end, end, visited)) return true;
			p = p->next;
		}
	}

	return false;
}

//找欧拉道路
template<class TV,class T>
void adjlistgraph<TV,T>::euler()
{
	eulernode *beg = nullptr, *end = nullptr, *p = nullptr, *q = nullptr, *tb = nullptr, *te = nullptr;  //begin end 为起点终点
	int numofdegree;
	edgenode* r;
	vernode *tmp;

	if (edges == 0)
	{
		cout << "no" << endl;   //没有边 则不存在欧拉回路
		return;
	}

	int oddnumber = 0;
	int oddnode = 0;
	//检查其充要条件：两个点度数为奇 其他都为偶数 并找出这两个点
	for (int i = 0; i < vers; ++i)
	{
		numofdegree = 0;
		r = verlist[i].head;
		while (r)
		{
			numofdegree++;
			r = r->next;
		}
		if (numofdegree == 0) { cout << "no" << endl; return; }
		if (numofdegree % 2 != 0)
		{
			oddnumber++;
			if(oddnumber==3) { cout << "no" << endl; return; }
			oddnode = i;
		}
	}


	tmp = clone();  //保存一个副本 等下可以恢复

	beg = eulercircuit(oddnode, end);   //end只是作为一个接受结果的参数 因为要返回首尾~  
	//给出一个奇数度的即可！！  他会自动到达另一个奇数度的结点停止！！！					 

	while (true)
	{
		p = beg;
		while (p->next != nullptr)
		{
			//对第一条初始回路 依次扫描上面的点 用来将剩下的边都纳入欧拉回路中
			if (verlist[p->next->num].head != nullptr)
			{
				//如果还有边没纳入
				break;
			}
			else
				p = p->next;  //通过检查 继续检查下一个点
		}
		if (p->next == nullptr) //所有都通过了检查 
			break;
		else
		{
			q = p->next;
			tb = eulercircuit(q->num, te);  //探索一条回路
											//纳入欧拉回路中~
			te->next = q->next;
			p->next = tb;
			delete q;
		}
	}

	delete[]verlist;
	verlist = tmp;//恢复原图

	while (beg)
	{
		cout << verlist[beg->num].ver << " ";
		p = beg;
		beg = beg->next;
		delete p;
	}

}

//找强连通分量的k什么什么方法
template<class TV,class T>
void adjlistgraph<TV, T>::findstrong_toposort(stack<int>&hehe) const
{
	bool*visited = new bool[vers];
	for (int i = 0; i < vers; ++i) visited[i] = false;
	for (int i = 0; i < vers; ++i)
	{
		if (visited[i] == true) continue;
		visited[i] = true;
		toposort_dfs(i, visited, hehe);  //复用了基于dfs的拓扑排序的私有函数!!!!因为是一样的！！！
	}

}

template<class TV,class T>
void adjlistgraph<TV, T>::findstrong_k()const
{
	stack<int> hehe;
	findstrong_toposort(hehe);  //hehe则放好了拓扑排序好的结点

	//第二步是逆转图
	vernode *tmpv = new vernode[vers];  //新的逆转图
	edgenode* oldp, *newp;
	for (int i = 0; i < vers; ++i)
	{
		oldp = verlist[i].head;
		while (oldp)
		{
			tmpv[oldp->end].head = new edgenode(i, oldp->weight, tmpv[oldp->end].head);
			oldp = oldp->next;
		}
	}

	//第三步是 按顺序dfs遍历逆转的图 输出所有强连通的分量
	int numofstrong = 0;
	int current;
	bool*visited = new bool[vers];
	for (int i = 0; i < vers; ++i) visited[i] = false;
	while (!hehe.empty())
	{
		current = hehe.top();
		hehe.pop();
		if (visited[current] == true) continue;
		else
		{
			++numofstrong;
			cout << "第" << numofstrong << "个强连通分量:";
			findstrong_dfs(current, tmpv, visited);
		}
		cout << endl;
	}

	//第四步：恢复图
	for (int i = 0; i < vers; ++i)
	{
		oldp = tmpv[i].head;
		while (oldp)
		{
			newp = oldp;
			oldp = oldp->next;
			delete newp;
		}
	}
	delete[]tmpv;
}

template<class TV,class T>
void adjlistgraph<TV, T>::findstrong_dfs(int start, vernode* tmpv, bool*visited)const
{
	edgenode*p = tmpv[start].head;
	cout << verlist[start].ver << " ";
	visited[start] = true;
	while (p)
	{
		if (visited[p->end])
		{
			p = p->next;
			continue;
		}
		else
		{
			findstrong_dfs(p->end, tmpv, visited);
			p = p->next;
		}
	}
}

//找强连通分量的tarjan方法
template<class TV,class T>
void adjlistgraph<TV, T>::findstrong_tarjan()const
{
	int *visited = new int[vers];
	for (int i = 0; i < vers; ++i) visited[i] = 0;
	int *ancestors = new int[vers];
	int seqno = 0;
	int numofstrong = 0;
	for (int i = 0; i < vers; ++i)
	{
		if (visited[i] == -1) continue;  //已经属于某个强连通分支
		findstrong_tarjan(i, visited, ancestors, seqno, numofstrong);

	}
}

template<class TV,class T>
int adjlistgraph<TV, T>::findstrong_tarjan(int start, int*visited, int*ancestors, int&seqno, int&numofstrong)const
{
	
	edgenode*p = verlist[start].head;
	int ancestor, i;
	++seqno;   
	visited[start] = ancestors[start] = seqno;   //visited是盖一个时间戳  ancestors是先初始化为自己 将来再看需不需要更新

	while (p)
	{
		switch (visited[p->end])
		{
		case -1:break;   //如果已经属于某个强连通分支 那么直接无视
		case 0:
			ancestor = findstrong_tarjan(p->end, visited, ancestors, seqno, numofstrong);  //递归反问
			if (ancestor < ancestors[start]) ancestors[start] = ancestor; //更新
			break;
		default: //其他情况即为 他已经有了时间戳 说明他已经被访问过了！！
			ancestors[start] = ancestors[p->end];
			
		}
		p = p->next;
	}
	if (visited[start] == ancestors[start])
	{
		//这个判断条件可能比较晦涩难懂
		//它的意思是 对于当前结点start 我想尽办法利用了我所有的子树 然而还是没办法到达更早的结点 那么我这个派系就自成了一个强连通分量
		++numofstrong;
		cout << "第" << numofstrong << "个强连通分量：";
		for (i = 0; i < vers; ++i)
		{
			if (ancestors[i] == ancestors[start])
			{
				cout << verlist[i].ver << " ";
				visited[i] = -1; //标记其已经属于某个强连通分量
			}
		}
		cout << endl;
	}
	
	return ancestors[start];
}

//krustal求最小生成树：优先队列+并查集
template<class TV,class T>
void adjlistgraph<TV, T>::kruskal()const
{
	int count = 1;//数到vers-1
	edgenode* p;
	edge e;
	disjointset ds(vers); //并查集
	priority_queue<edge> hehe;//边的优先级队列

	//生成边的优先级队列
	for (int i = 0; i < vers; ++i)
	{
		p = verlist[i].head;
		while (p)
		{
			if (i < p->end) //无向图只需要进一个就够了！！！！ 有向图这个条件就要去掉！！！！
			{
				e.begin = i;
				e.end = p->end;
				e.w = p->weight;
				hehe.push(e);
			}
			p = p->next;
		}
	}

	//开始不断加入边
	while (count <= vers - 1)
	{
		e = hehe.top();
		hehe.pop();
		int u = ds.find(e.begin);
		int v = ds.find(e.end);
		if (u!= v)
		{
			//如果边可以加进去 那么
			count++;
			ds.Union(u, v);
			cout << "(" << verlist[u].ver << "," << verlist[v].ver << ")" << " ";  //输出这条边
		}
	}
}

//prim算法求最小生成树：三数组
template<class TV,class T>
void adjlistgraph<TV, T>::prim(T noedge)const
{
	bool *flag = new bool[vers];
	T *lowcost = new T[vers];
	int *startnode = new int[vers];

	edgenode*p;
	T min;
	int start, i, j;

	for (i = 0; i < vers; ++i)
	{
		flag[i] = false;
		lowcost[i] = noedge;
	}

	start = 0;  //从第0号点开始

	for (i = 1; i < vers; ++i)
	{
		flag[start] = true;
		p = verlist[start].head;
		while (p)
		{
			if (!flag[p->end] && lowcost[p->end] > p->weight)
			{
				//如果这个后继结点还没有加入到U 而且这条边的权比它已经记录的最低权还小 那么及时地更新
				lowcost[p->end] = p->weight;
				startnode[p->end] = start;
			}
			p = p->next;
		}
		
		min = noedge;
		//接下来找到U-V中 的最小的边
		for (j = 0; j < vers; ++j)
		{
			if (lowcost[j] < min)
			{
				min = lowcost[j];
				start = j;
			}
		}
		cout << "(" << verlist[startnode[start]].ver << "," << verlist[start].ver << ") ";

		lowcost[start] = noedge;  //把已经加入到U的点的lowcost设置为无穷大 这样它就永远不会在选最小边的时候被选到~ 相当于不用判断每个点是否已经加入了U~

	}

	//删掉三数组
	delete[]flag;
	delete[]startnode;
	delete[]lowcost;
}


//无权图最短路径
template<class TV,class T>
void adjlistgraph<TV, T>::unweightedshortdistance(TV start, T noedge)const
{
	queue<int> hehe;
	T* distance = new T[vers];   //记录距离的数组
	int *prenode = new int[vers]; //记录前一个结点的数组
	

	for (int i = 0; i < vers; ++i)
	{
		distance[i] = noedge;
	}

	int num;
	//寻找起始start对应的内部编号
	for (num = 0; num < vers; ++num)
	{
		if (verlist[num].ver == start) break;
	}
	if (num == vers) { cout << "no" << endl; return; }
	

	distance[num] = 0;  //起点到自己的距离为0
	prenode[num] = num;  //作为将来打印路径的递归结束标志
	int seqno = 1;    //距离编号
	hehe.push(num);
	//给所有结点一个距离
	while (!hehe.empty())
	{
		int tmp = hehe.front();
		hehe.pop();
		edgenode*p = verlist[tmp].head;
		while (p)
		{
			if (distance[p->end] > seqno)
			{
				distance[p->end] = seqno;
				prenode[p->end] = tmp;
				hehe.push(p->end);
			}
			p = p->next;
		}
		++seqno;
	}
	//打印出来
	for (int i = 0; i < vers; ++i)
	{
		cout << "从" << start << "到" << verlist[i].ver << "的最短距离是：" << distance[i] << endl;
		cout << "其路径是:";
		printpath(i, prenode);
		cout << endl;
	}
}

//打印路径
template<class TV,class T>
void adjlistgraph<TV, T>::printpath(int i, int *prenode)const
{
	if (prenode[i] == i)
	{
		cout << i<< "  ";
		return;
	}

	printpath(prenode[i], prenode);
	cout << i << " ";
	return;
}

template<class TV,class T>
void adjlistgraph<TV, T>::dijkstra(TV start, T noedge)const
{
	T *distance = new T[vers];
	int *prenode = new int[vers];
	bool *flag = new bool[vers];
	for (int i = 0; i < vers; ++i)
	{
		flag[i] = false;
		distance[i] = noedge;
	}

	//找出start
	int num;
	for (num = 0; num < vers; ++num)
	{
		if (verlist[num].ver == start) break;
	}
	if (num == vers) { cout << "no" << endl; return; }

	prenode[num] = num;
	distance[num] = 0;
	
	queue<int> hehe;
	for (int i = 0; i < vers; ++i) //单纯控制次数
	{
		T min = noedge;
		int minnode=0;
		//找出U-V的最小值
		for (int j = 0; j < vers; ++j)
		{
			if (flag[j]==false && distance[j] < min)
			{
				min = distance[j];
				minnode = j;
			}
		}

		//把j加入U
		flag[minnode] = true;
		edgenode*p = verlist[minnode].head;
		while (p)
		{
			if (flag[p->end] == true)
			{
				p = p->next;
				continue;
			}
			else
			{
				if (distance[p->end] > distance[minnode] + p->weight)
				{
					distance[p->end] = distance[minnode] + p->weight;
					prenode[p->end] = minnode;
				}
				p = p->next;
			}
		}

	}

	//打印出来
	for (int i = 0; i < vers; ++i)
	{
		cout << "从" << start << "到" << verlist[i].ver << "的最短距离是：" << distance[i] << endl;
		cout << "其路径是:";
		printpath(i, prenode);
		cout << endl;
	}
}


template<class TV,class T>
void adjlistgraph<TV, T>::minusshortdistance(TV start, T noedge)const
{
	T* distance = new T[vers];
	int* prenode = new int[vers];
	for (int i = 0; i < vers; ++i) distance[i] = noedge;

	int num;
	for (num = 0; num < vers; ++num)
	{
		if (verlist[num].ver == start)
		{
			break;
		}
	}
	if (num == vers) { cout << "no" << endl; return; }

	queue<int> hehe;
	distance[num] = 0;
	prenode[num] = num;
	hehe.push(num);

	while (!hehe.empty())
	{
		int tmp = hehe.front();
		hehe.pop();
		edgenode*p = verlist[tmp].head;
		while (p)
		{
			if (distance[p->end] > distance[tmp] + p->weight)
			{
				distance[p->end] = distance[tmp] + p->weight;
				prenode[p->end] = tmp;
				hehe.push(p->end);
			}
			p = p->next;
		}

	}

	for (int i = 0; i < vers; ++i)
	{
		cout << "从" << start << "到" << verlist[i].ver << "的最短距离是：" << distance[i] << endl;
		cout << "其路径是:";
		printpath(i, prenode);
		cout << endl;
	}
}


template<class TV,class T>
void adjlistgraph<TV, T>::dagshortdistance(TV start, T noedge)const
{
	T *distance = new T[vers];
	int *prenode = new int[vers];
	int *indegree = new int[vers];

	int num;
	for (num = 0; num < vers; ++num)
	{
		if (verlist[num].ver == start) break;
	}
	if (num == vers) { cout << "no" << endl; return; }

	//需要检查起始点的入度是不是为0
	for (int i = 0; i < vers; ++i) indegree[i] = 0;
	for (int i = 0; i < vers; ++i)
	{
		edgenode*p = verlist[i].head;
		while (p)
		{
			++indegree[p->end];
			p = p->next;
		}
	}
	if (indegree[num] != 0) { cout << "no" << endl; return; }


	//初始化
	for (int i = 0; i < vers; ++i) distance[i] = noedge;
	distance[num] = 0;
	prenode[num] = num;
	queue<int> hehe;
	hehe.push(num);

	//按拓扑排序选择节点并更新 ！！ 可以同步进行！！！
	//拓扑排序在队列进行 出队进行更新即可
	while (!hehe.empty())
	{
		int tmp = hehe.front();
		hehe.pop();
		edgenode*p = verlist[tmp].head;
		while (p)
		{
			//更新后继结点
			if (distance[p->end] > distance[tmp] + p->weight)
			{
				distance[p->end] = distance[tmp] + p->weight;
				prenode[p->end] = tmp;
			}
			//拓扑排序入队
			if (--indegree[p->end] == 0) hehe.push(p->end);
			p = p->next;
		}
	}


	for (int i = 0; i < vers; ++i)
	{
		cout << "从" << start << "到" << verlist[i].ver << "的最短距离是：" << distance[i] << endl;
		cout << "其路径是:";
		printpath(i, prenode);
		cout << endl;
	}
}


int main()
{
	adjmatrixgraph<char, int> hehe(4, "0123",100);
	hehe.insert(0, 2, 3);
	hehe.insert(0, 1, 2);
	hehe.insert(1, 4, 1);
	hehe.insert(2, 3, 4);
	hehe.insert(3, 5, 1);
	hehe.insert(4, 5, 6);
	
	hehe.floyd();

	return 0;
}

