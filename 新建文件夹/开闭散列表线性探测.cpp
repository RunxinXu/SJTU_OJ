#include <iostream>


using namespace std;

//����ɢ�к���
//1.ֱ�Ӷ�ַ��
//2.������������ȡģ ��ѡ����
//3.���ַ�����
//4.ƽ��ȡ�з���ƽ��֮��ȡ�м伸λ
//5.�۵�������λ�и�ɼ�����λ�������ȵ�

//��ɢ�б��뿪ɢ�б���������
//���ڱ�ɢ�б���ײ�Ľ����
//1.����̽�ⷨ����ײ�˾�˳����ǰ̽��
//2.����̽�ⷨ��̽����һ�μ�1 2^2 3^2 4^2 ����
//���ַ���һ��Ҫ���Ĵ�С������ ���Ҹ������� Ҳ���Ƿǿյ�Ԫ�ı���Ҫ����0.5
// ����ʽHi=H0+i*i mod M  Hi-1=H0+(i-1)^2 mod M ������Եõ� Hi=Hi-1  + (2*i-1)mod M
// ������ָ������ӳ���0.5 ��ô����Ҫ��ɢ�� �ѱ�Ĺ�ģ��ɶ�����С


//����ɢ�б�����Ҫ��һ�������ɢ�к��� ͬʱ����Ǳ�ɢ�б���Ҫȷ��һ�������ײ�ķ���

template <class T>
class hashtable
{
protected:
	int (*key)(const T&x);  //ȡ��Ԫ��x�ļ���ת�������� ����ָ��
	static int defaultkey(const int &k) { return k; }
	//�����int�Ͳ���ת�� ֱ����
public:
	virtual bool find(const T&x)const = 0;
	virtual bool insert(const T&x) = 0;
	virtual bool remove(const T&x) = 0;
};

//ʵ��һ����ɢ�б�
template<class T>
class closehashtable :public hashtable<T>
{
	struct node
	{
		T data;
		int state;  //��ǰ���״̬ 0Ϊ��1Ϊ��2Ϊ��ɾ��
		node() { state = 0; };
	};

	node* array;
	int size;

public:
	closehashtable(int length = 101, int(*f)(const T&x) = defaultkey)
	{
		size = length;
		key = f;   //������������� �Ǿ�Ҫ����һ������ָ�룡����
		array = new node[size];
	}
	~closehashtable() { delete[]array; }
	bool find(const T&x)const;
	bool insert(const T&x);
	bool remove(const T&x);
	void rehash(); //��ɢ��
};

template<class T>
bool closehashtable<T>::insert(const T&x)
{
	int initpos, pos;
	initpos = pos = key(x) % size; //ʹ��ȡģ�ķ���
	do
	{
		if (array[pos].state != 1)
		{
			//������ԷŽ�ȥ
			array[pos].data = x;
			array[pos].state = 1;
			return true;
		}
		if (array[pos].state == 1 && array[pos].data == x)
			return true;//��ͬ
		pos = (pos + 1) % size; //����̽�ⷨ
	} while (pos != initpos);

	return false; //�Ѿ�û�տ��Բ���
}

template<class T>
bool closehashtable<T>::remove(const T&x)
{
	int initpos, pos;
	initpos = pos = key(x) % size;
	do
	{
		if (array[pos].state == 0) return false;
		if (array[pos].state == 1 && array[pos].data == x)
		{
			array[pos].state = 2; return true;
		}
		pos = (pos + 1) % size;  //������ǰ��
	} while (pos != initpos);

	return false;
}

template<class T>
bool closehashtable<T>::find(const T&x) const
{
	int initpos, pos;
	initpos = pos = key(x) % size;
	do
	{
		if (array[pos].state == 0) return false;
		if (array[pos].state == 1 && array[pos].data == x) return true;
		pos = (pos + 1) % size;

	} while (pos != initpos);

	return false;
}

template<class T>
void closehashtable<T>::rehash()
{
	//������stateΪ2��������ȥ����
	node*tmp = array;
	array = new node[size];
	
	for (int i = 0; i < size; ++i)
	{
		if (array[i].state == 1) insert(tmp[i].data);
	}
	delete[]tmp;

}

//ʵ�ֿ�ɢ�б�
//��ɢ�б���һ��ͷ��㣡����
template<class T>
class openhashtable :public hashtable<T>
{
	struct node
	{
		T data;
		node *next;
		node(const T&d) :data(d), next(nullptr) {};
		node() :next(nullptr) {};
	};
	node **array; //ָ������
	int size;

public:
	openhashtable(int length = 101, int(*f)(const T&x) = defaultkey)
	{
		size = length;
		key = f;
		array = new node*[size];
		for (int i = 0; i < size; ++i) array[i] = new node;
	}
	~openhashtable()
	{
		node*tmp1,tmp2;
		for (int i = 0; i < size; ++i)
		{
			tmp1 = array[i];
			tmp2 = tmp1->next;
			while (tmp2 != nullptr)
			{
				delete tmp1;
				tmp1 = tmp2;
				tmp2 = tmp2->next;
			}
			delete tmp1;
		}
		delete[]array;
	}
	bool find(const T&x) const;
	bool insert(const T&x);
	bool remove(const T&x);
};

template<class T>
bool openhashtable<T>::insert(const T&x)
{
	int pos;
	node* p;

	pos = key(x) % size;
	p = array[pos]->next;
	//�����ǲ����Ѿ����� û���ظ�Ԫ�صĻ��ٲ��뵽��ǰ��
	while (p != nullptr && p->data != x) p = p->next;
	if (p == nullptr)
	{
		//������ǰ��Ŷ��
		p = new node(x);
		p->next = array[pos]->next;
		array[pos]->next = p;
		return true;
	}
	return false;
}

template<class T>
bool openhashtable<T>::remove(const T&x)
{
	int pos;
	node *p, *q;
	pos = key(x) % size;

	p = array[pos];
	while (p->next != nullptr && p->next->data != x) p = p->next;
	if (p->next == nullptr)
	{
		return false;
	}
	else
	{
		q = p->next;
		p->next = q->next;
		delete q;
		return true;
	}
}

template<class T>
bool openhashtable<T>::find(const T&x) const
{
	int pos = key(x) % size;
	node *p;
	p = array[pos];
	while (p->next && p->next->data != x) p = p->next;
	if (p->next == nullptr) return false;
	else return true;
}
int main()
{
	/*hashtable<int>*p = new closehashtable<int>;
	p->insert(5);
	p->insert(100);
	p->insert(20);
	p->insert(121);
	cout << boolalpha << p->find(121) << endl;
	p->remove(20);
	cout << boolalpha << p->find(121) << endl;
	cout << boolalpha << p->find(20) << endl;*/

	hashtable<int>* p = new openhashtable<int>;
	p->insert(5);
	p->insert(100);
	p->insert(20);
	p->insert(121);
	cout << boolalpha << p->find(121) << endl;
	p->remove(20);
	cout << boolalpha << p->find(121) << endl;
	cout << boolalpha << p->find(20) << endl;

	return 0;
}
