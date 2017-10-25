#include <iostream>

using namespace std;
//B+������
//1.��������Ҷ�� ������2��M������
//2.����֮�����нڵ������������M/2������ȡ���� ������M
//3.k�����ӵĽ����k-1���� ��i������i+1��������Сֵ
//4.Ҷ�ڵ��ָ��ָ�����ݿ�
//5.���ݿ��������ΪSIZE������Ҳ��SIZE/2 ������ȡ����

//--------ʵ������һ��void* ����ָdatanodeҲ����ָidxnode������---------//


//���ڲ����㷨 �Ƚϼ򵥲�ʵ���� �ڲ����㷨��ʵ������


//���ڲ����㷨 ������԰�Ȼ���Ĳ���Ϳ����� ������ʱ����Ҫ���� ���ҷ��ѿ��ܵ���� ���Թ��к���ͬ��Ҫ����
//���ڷ��� ���������ݿ� ���ǽ�� ��˼�� ��һ���� ������һ����չ��ָ�� Ȼ���ԭ���Ǹ������Ŀ������
//�����������½�һ�붼�ƶ���չָ���� Ȼ����չָ�뷵�ص���һ��ȥ����
// Ҳ��������� ���ݿ����չ������չ�����ݿ�ָ�� ---------------------insertdata
//              ������һ������������չ�����������ָ��--------------adddatablk
//              ����Ҷ�ӽ�������������չ �����������ָ��---------addidxblk


//����ɾ���㷨 ͬ�� �������ɾ����С����СֵM/2 �ǿ϶��Ǻõ� ����ʱ��С�� �Ǿ���Ҫ������
//һ����˵ �ȿ���ߵ��ֵ� ���ұߵ��ֵ� ��������õ�һ����Ҳ���� ��ô�ʹ���������� �ǵø�����һ��ļ�ֵ������
//�����ߺ��ұߵĶ����Ѿ�������ֵ ��ô��ɾ����������ϲ���������
//���������һ��ʧȥһ������ ����ܲ�����ҲС����ֵ�� ��ô�ͼ����ݹ� ����Ƚ��ϲ���ԭ������
//���к����ǵô�����ڵ��������Ӻϲ������
template<class T,int idxsize,int datablksize>  //��������������Լ����ݿ�Ĵ�С
class btree
{
	struct idxnode
	{
		int type; //0��ʾ��һ����������� 1��ʾ��һ�������ݽ��
		T key[idxsize - 1]; //�ؼ���
		void *idx[idxsize];
		int len;  //��Ч������
		idxnode() :len(1) { };
	};

	struct datanode
	{
		int len; //��Ч��¼��
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

//�б�Ҫ˵��һ�� ���������nodedata ����Ҷ�ӽ���type��1 ������0
//�����ݿ���datanode

template<class T, int idxsize, int datablksize>
void btree<T, idxsize, datablksize>::insert(const T&x)
{
	if (root == nullptr)
	{
		//ԭ���ǿ���
		root = new idxnode;
		root->type = 1;
		root->idx[0] = new datanode;
		datanode *p = (datanode*)root->idx[0];  //void*��ָ���ת��
		p->record[0] = x;
		return;
	}

	idxnode *p = insert(x, root); 
	//������ز���nullptr ˵������Ҫ��չ�� ���صľ����Ǹ���չ�Ķ�����ָ��
	if (p != nullptr)
	{
		idxnode*t = root;
		root = new idxnode;
		root->type = 0;
		root->len = 2;
		root->idx[0] = t;  //����ԭ����
		root->idx[1] = p;//��������չ��
		while (p->type == 0) p = (idxnode*)p->idx[0];
		datanode*d = (datanode*)p->idx[0];
		root->key[0] = d->record[0];
		//�ҵ�����չ�����ݵ���Сֵ��Ϊ�ָ�ļ�ֵ
		//ע�������������������ʵ��֪�� ���ص���չ����һ���ǱȽϴ�Ĳ��֣���������
	}
}

template<class T, int idxsize, int datablksize>
btree<T, idxsize, datablksize>::idxnode* btree<T, idxsize, datablksize>::insert(const T&x, idxnode*t)
{
	void* newnode;

	for (int i = 0; i < t->len - 1; ++i)
	{
		if (x < t->key[i]) break; //���ݼ�ֵ�ҵ���Ҫ���¼�ָ��
	}

	if (t->type == 0) newnode = insert(x, (idxnode*)t->idx[i]); //������滹��������� ��ô�������µݹ�
	else
	{
		newnode = insertdata(x, (datanode*)t->idx[i]); //�����һ�������ݿ� ��ô��������
	}

	//newnode ��������nullptr ��ʲô����û�� ������� �Ƿ��صľ�����չ�Ķ�����ָ��
	if (newnode == nullptr) return nullptr;
	else
	{
		if (t->type == 0) return addidxblk((idxnode*)newnode, t);  
		//�ڱ�t��ָ����һ�� ���һ���������
		else return adddatablk((datanode*)newnode, t);
		//�ڱ�t��ָ����һ�� ���һ�����ݽ��
	}
}

template<class T, int idxsize, int datablksize>
btree<T, idxsize, datablksize>::datanode* btree<T, idxsize, datablksize>::insertdata(const T&x, datanode*t)
{
	//�����ݿ��в�������
	if (t->len < datablksize)
	{
		//�����Լ�������
		for (int i = t->len; i > 0 && x < t->record[i - 1]; --i)
		{
			t->record[i] = t->record[i - 1];  //�Ѳ�С��x�����ݶ�����ƶ� ��x�ó�λ�� �������������
		}
		t->record[i] = x;
		t->len++;
		return nullptr;
	}

	//�������˵�����鲻�� ��Ҫ�ֿ�������ݿ���
	datanode *newnode = new datanode;
	int i, j;
	int max = datablksize / 2; 
	newnode->len = max + 1;   //��datablksize/2  + 1 �����ݸ��½ڵ� !!
	for (i = max, j = datablksize - 1; i >= 0 && t->record[j] > x; --i,--j)
	{
		newnode->record[i] = t->record[j]; //�Ӵ�С �Ѵ���x���ȷŹ�ȥ�½ڵ�
	}
	if (i >= 0)
	{
		//˵������������С�ڵ���x���� ���½ڵ�Ļ�û���� 
		//���仰˵����xӦ����½ڵ��
		newnode->record[i] = x;
		i--;
	}
	for (; i >= 0; --i) newnode->record[i] = t->record[j--]; //���������½ڵ��

	t->len = datablksize - max;   //ԭ�ȵĽ��ʣ�µ�������
	if (j < t->len - 1)
	{
		//˵��xû�б����뵽�½ڵ� �ǲ��� ������������ƶ�������λ �����ڲ�������
		for (; j >= 0 && x < t->record[j]; --j) t->record[j + 1] = t->record[j];
		t->record[j + 1] = x;
	}
	return newnode;  //������չ�ķ��ظ���һ�� �������������������ݽ��ĺ���ȥ����
}

template<class T, int idxsize, int datablksize>
btree<T, idxsize, datablksize>::idxnode* btree<T, idxsize, datablksize>::adddatablk(datanode * newnode, idxnode*t)
{
	//�������չ�����ݿ�newnode ��ô��Ҫ�������ӵ�t��ָ����һ��(��������ײ㣩 ��������� �Ǿͷ���nullptr
	//�������Ҫ������չ ���ڼ������� �������Ϊidxnode������������idxnode*
	if (t->len < idxsize)
	{
		//û���� ����ֱ�Ӳ���
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

	//������ ˵���÷�����gg
	idxnode* newidx = new idxnode;
	newidx->type = 1;
	int max = idxsize / 2;
	newidx->len = max + 1;  //������½��Ĺ�ģ
	int i, j;

	if (newnode->record[0] > t->key[idxsize - 2])
	{
		//������ӵ������ݿ������� ��ôֱ�Ӱ����ҵ��½ڵ� ���Ұ�ԭ����һ��Ҳ�ҹ�ȥ
		newidx->key[max - 1] = newnode->record[0];
		newidx->idx[max] = newnode;
	}
	else
	{
		//������� ��ô�Ȱѱ����Ĵ�Ĺҹ�ȥ�½ڵ�
		//����½������˻�û�ܹ������ݿ� �����ݿ�͹���ԭ���Ľ��
		//������Ź����ֵ������ݿ� �Ǿ��ϣ�
		newidx->key[max - 1] = t->key[idxsize - 2];
		newidx->idx[max] = t->idx[idxsize - 1];  //�����Ĺҹ�ȥ
		for (int i = t->len - 2; i > 0 && newnode->record[0] < t->key[i - 1]; --i)
		{
			t->key[i] = t->key[i - 1];
			t->idx[i + 1] = t->idx[i];  //������λ �������ڲ�������
		}
		t->key[i] = newnode->record[0];
		t->idx[i + 1] = newnode;

	}

	//��һ�붫���ҹ�ȥ��
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
	//ͬ��
	idxnode*p = newnode;
	while (p->type == 0) p->(idxnode*)p->idx[0];
	datanode*d = (datanode*)p->idx[0];
	T min = d->record[0];  
	//�ҵ���չ������Сֵ

	if (t->len < idxsize)
	{
		//û���� ֱ�Ӽ�
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

	//��Ҫ����
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

	//���� ��������һ���������� �뷨Ҳ��ͬ

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
	