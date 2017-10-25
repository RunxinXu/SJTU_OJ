#include <iostream>

using namespace std;
//B+树性质
//1.根或者是叶子 或者有2到M个儿子
//2.除根之外所有节点儿子数不少于M/2（向上取整） 不多于M
//3.k个儿子的结点有k-1个键 第i个键是i+1子树的最小值
//4.叶节点的指针指向数据块
//5.数据块数据最多为SIZE，最少也得SIZE/2 （向上取整）

//--------实现中用一个void* 可以指datanode也可以指idxnode是亮点---------//


//对于查找算法 比较简单不实现了 在插入算法其实就有了


//对于插入算法 如果可以安然无恙的插入就可以了 但是有时候需要分裂 而且分裂可能到达根 所以公有函数同样要处理
//对于分裂 不管是数据块 还是结点 其思想 是一样的 单独开一个扩展的指针 然后把原来那个爆满的块的内容
//在有序的情况下将一半都移动扩展指针那 然后将扩展指针返回到上一层去处理
// 也就三种情况 数据块的扩展返回扩展的数据块指针 ---------------------insertdata
//              最下面一层索引结点的扩展返回索引结点指针--------------adddatablk
//              不是叶子结点的索引结点的扩展 返回索引结点指针---------addidxblk


//对于删除算法 同样 如果可以删除后不小于最小值M/2 那肯定是好的 但有时候小了 那就需要调整了
//一般来说 先看左边的兄弟 和右边的兄弟 如果他们拿掉一个后也可以 那么就从他们那里借 记得更新上一层的键值就行了
//如果左边和右边的都是已经到达阈值 那么就删除后把两个合并起来！！
//但这会是上一层失去一个儿子 如果很不幸他也小于阈值了 那么就继续递归 坚持先借后合并的原则上溯
//公有函数记得处理根节点两个儿子合并的情况
template<class T,int idxsize,int datablksize>  //后两个是其阶数以及数据块的大小
class btree
{
	struct idxnode
	{
		int type; //0表示下一层是索引结点 1表示下一层是数据结点
		T key[idxsize - 1]; //关键字
		void *idx[idxsize];
		int len;  //有效儿子数
		idxnode() :len(1) { };
	};

	struct datanode
	{
		int len; //有效记录数
		T record[datablksize];
		datanode() :len(1) {};
	};

	idxnode*root;

	void makeempty(idxnode* t);
	idxnode* insert(const T&x, idxnode *t);
	datanode* insertdata(const T&x, datanode*t);
	idxnode *addidxblk(idxnode*n, idxnode*t);
	idxnode *adddatablk(datanode *n, idxnode*t);

public:
	btree() :root(nullptr) {};
	~btree() { makeempty(root); }
	bool find(const &x) const { return find(x, root); }
	void insert(const T&x);
	void remove(const T&x);
};

//有必要说明一下 索引结点是nodedata 其中叶子结点的type是1 其他是0
//而数据块是datanode

template<class T, int idxsize, int datablksize>
void btree<T, idxsize, datablksize>::insert(const T&x)
{
	if (root == nullptr)
	{
		//原来是空树
		root = new idxnode;
		root->type = 1;
		root->idx[0] = new datanode;
		datanode *p = (datanode*)root->idx[0];  //void*型指针的转换
		p->record[0] = x;
		return;
	}

	idxnode *p = insert(x, root); 
	//如果返回不是nullptr 说明有需要扩展的 返回的就是那个扩展的东西的指针
	if (p != nullptr)
	{
		idxnode*t = root;
		root = new idxnode;
		root->type = 0;
		root->len = 2;
		root->idx[0] = t;  //连接原来的
		root->idx[1] = p;//连接新扩展的
		while (p->type == 0) p = (idxnode*)p->idx[0];
		datanode*d = (datanode*)p->idx[0];
		root->key[0] = d->record[0];
		//找到新扩展的数据的最小值作为分割的键值
		//注意由下面的其他函数的实现知道 返回的扩展部分一定是比较大的部分！！！！！
	}
}

template<class T, int idxsize, int datablksize>
btree<T, idxsize, datablksize>::idxnode* btree<T, idxsize, datablksize>::insert(const T&x, idxnode*t)
{
	void* newnode;

	for (int i = 0; i < t->len - 1; ++i)
	{
		if (x < t->key[i]) break; //根据键值找到所要的下级指针
	}

	if (t->type == 0) newnode = insert(x, (idxnode*)t->idx[i]); //如果下面还是索引结点 那么继续向下递归
	else
	{
		newnode = insertdata(x, (datanode*)t->idx[i]); //如果下一层是数据块 那么插入数据
	}

	//newnode 返回若是nullptr 那什么事情没有 如果不是 那返回的就是扩展的东西的指针
	if (newnode == nullptr) return nullptr;
	else
	{
		if (t->type == 0) return addidxblk((idxnode*)newnode, t);  
		//在被t所指的这一层 添加一个索引结点
		else return adddatablk((datanode*)newnode, t);
		//在被t所指的这一层 添加一个数据结点
	}
}

template<class T, int idxsize, int datablksize>
btree<T, idxsize, datablksize>::datanode* btree<T, idxsize, datablksize>::insertdata(const T&x, datanode*t)
{
	//在数据块中插入数据
	if (t->len < datablksize)
	{
		//还可以继续插入
		for (int i = t->len; i > 0 && x < t->record[i - 1]; --i)
		{
			t->record[i] = t->record[i - 1];  //把不小于x的数据都向后移动 给x让出位置 类似与插入排序
		}
		t->record[i] = x;
		t->len++;
		return nullptr;
	}

	//来到这就说明事情不好 需要分开这个数据块了
	datanode *newnode = new datanode;
	int i, j;
	int max = datablksize / 2; 
	newnode->len = max + 1;   //分datablksize/2  + 1 个数据给新节点 !!
	for (i = max, j = datablksize - 1; i >= 0 && t->record[j] > x; --i,--j)
	{
		newnode->record[i] = t->record[j]; //从大到小 把大于x的先放过去新节点
	}
	if (i >= 0)
	{
		//说明接下来的是小于等于x的了 而新节点的还没填满 
		//换句话说就是x应该填到新节点的
		newnode->record[i] = x;
		i--;
	}
	for (; i >= 0; --i) newnode->record[i] = t->record[j--]; //继续填满新节点的

	t->len = datablksize - max;   //原先的结点剩下的数据数
	if (j < t->len - 1)
	{
		//说明x没有被插入到新节点 那惨了 还得依次向后移动给他让位 类似于插入排序
		for (; j >= 0 && x < t->record[j]; --j) t->record[j + 1] = t->record[j];
		t->record[j + 1] = x;
	}
	return newnode;  //把新扩展的返回给上一层 留给增加索引结点或数据结点的函数去处理
}

template<class T, int idxsize, int datablksize>
btree<T, idxsize, datablksize>::idxnode* btree<T, idxsize, datablksize>::adddatablk(datanode * newnode, idxnode*t)
{
	//如果有扩展的数据块newnode 那么就要把他增加到t所指的这一层(索引的最底层） 而如果可以 那就返回nullptr
	//如果还需要向上扩展 由于继续向上 这就是作为idxnode了所以类型是idxnode*
	if (t->len < idxsize)
	{
		//没有满 可以直接插入
		for (int i = t->len - 1; i > 0 && newnode->record[0] < t->key[i - 1]; --i)
		{
			t->key[i] = t->key[i - 1];
			t->idx[i + 1] = t->idx[i];
		}
		t->key[i] = newnode->record[0];
		t->idx[i + 1] = newnode;
		++(t->len);
		return nullptr;
	}

	//来到这 说明得分裂了gg
	idxnode* newidx = new idxnode;
	newidx->type = 1;
	int max = idxsize / 2;
	newidx->len = max + 1;  //这个是新结点的规模
	int i, j;

	if (newnode->record[0] > t->key[idxsize - 2])
	{
		//如果增加的是数据块是最大的 那么直接把他挂到新节点 并且把原来的一半也挂过去
		newidx->key[max - 1] = newnode->record[0];
		newidx->idx[max] = newnode;
	}
	else
	{
		//如果不是 那么先把比他的大的挂过去新节点
		//如果新结点挂满了还没能挂上数据块 那数据块就挂在原来的结点
		//如果挂着挂着轮到新数据块 那就上！
		newidx->key[max - 1] = t->key[idxsize - 2];
		newidx->idx[max] = t->idx[idxsize - 1];  //把最大的挂过去
		for (int i = t->len - 2; i > 0 && newnode->record[0] < t->key[i - 1]; --i)
		{
			t->key[i] = t->key[i - 1];
			t->idx[i + 1] = t->idx[i];  //给他让位 又类似于插入排序
		}
		t->key[i] = newnode->record[0];
		t->idx[i + 1] = newnode;

	}

	//把一半东西挂过去！
	for (i = max - 1, j = idxsize - 1; i > 0; --i, --j)
	{
		newidx->idx[i] = t->idx[j];
		newidx->key[i - 1] = t->key[j - 1];
	}
	newidx->idx[0] = t->idx[j];

	t->len = idxsize - max;
	return newidx;
}

template<class T, int idxsize, int datablksize>
btree<T, idxsize, datablksize>::idxnode* btree<T, idxsize, datablksize>::addidxblk(idxnode*newnode, idxnode*t)
{
	//同上
	idxnode*p = newnode;
	while (p->type == 0) p->(idxnode*)p->idx[0];
	datanode*d = (datanode*)p->idx[0];
	T min = d->record[0];  
	//找到扩展结点的最小值

	if (t->len < idxsize)
	{
		//没有满 直接加
		for (int i = t->len - 1; i > 0 && min < t->key[i - 1]; --i)
		{
			t->key[i] = t->key[i - 1];
			t->idx[i + 1] = t->idx[i];
		}
		t->idx[i + 1] = newnode;
		t->key[i] = min;
		++(t->len);
		return nullptr;
	}

	//需要分裂
	idxnode* newidx = new idxnode;
	newidx->type = 0;
	int max = idxsize / 2;
	newidx->len = max + 1;
	int i, j;

	if (min > t->key[idxsize - 2])
	{
		newidx->key[max - 1] = min;
		newidx->idx[max] = newnode;
	}
	else
	{
		newidx->key[max - 1] = t->key[idxsize - 2];
		newidx->idx[max] = t->idx[idxsize - 1];
		for (int i = t->len - 2; i > 0 && min < t->key[i - 1]; --i)
		{
			t->key[i] = t->key[i - 1];
			t->idx[i + 1] = t->idx[i];
		}
		t->key[i] = min;
		t->idx[i + 1] = newnode;

	}

	//以上 基本和上一个函数类似 想法也相同

	for (i = max - 1, j = idxsize - 1; i > 0; --i, --j)
	{
		newidx->idx[i] = t->idx[j];
		newidx->key[i - 1] = t->key[j - 1];
	}
	newidx->idx[0] = t->idx[j];
	t->len = idxsize - max;
	return newidx;
}

int main()
{

}
	