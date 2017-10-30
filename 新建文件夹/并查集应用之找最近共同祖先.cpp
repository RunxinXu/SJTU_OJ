#include <iostream>

using namespace std;

//�ò��鼯˼· ���ҽ�������Ĺ�ͬ����

//�����˳��洢�� ��ô���Բ��ϰѲ�αȽ�����ģ���ͬ�����⣩������Žϴ�ģ����������� �����϶���������ͬһ����� �Ǹ�����
//����Ĺ�ͬ���ȣ�������

//����������͵��� �Ժ����ֵ���Ϊ��
//�����õݹ� ���ú������ �����ĳ������ͬʱ�ҵ����Ǿ��� ���û����ô�ټ���¸�Ȼ�󷵻���һ��

template<class T>
T tree<T>::LCA(node*t, T x, bool& xfind, T y, bool &yfind)
{
	//��Ҫ������־��Ϊtrue ����ֵ�������壡����
	bool xtmp, ytmp;
	node *p;
	T lca;

	if (t == nullptr)
	{
		xfind = yfind = false;
		return x;
	}

	p = t->son;
	while (p != nullptr)
	{
		xtmp = ytmp = false;
		lca = LCA(p, x, xtmp, y, ytmp);
		if (xtmp&&ytmp)
		{
			xfind = yfind = true;
			return lca;
		}
		if (xtmp) xfind = true;
		if (ytmp) yfind = true;
		p = p->brother;
	}


	//��������ķ��ʸ���㲿�֣���
	if (t->data == x) xfind = true;
	if (t->data == y)yfind = true;
	return t->data;
}

int main()
{
	
}
