#include <iostream>
#include<cstdlib>
#include <ctime>
using namespace std;

//素数检测
//之前也有写过一个素数检测 
//方法是 特殊情况直接返回 2是素数 1不是素数
//       然后一次检测2 3 5 7 （奇数） ……  sqrt(n) 


//如果是特别大的数的话 可以用
//理论依据： 1. 费马小定理：若p为素数 且0<A<p 那么A^(p-1) % p =1
//           2. 若p为素数 且0<A<p 那么方程x^2 % p=1 的解只能为x=1 或x =p-1
//那么我们可以以1为主要 进行多次判断 在判断过程中 刚好可以判断2
//但是 如果算法指出p不是素数 那么它不是素数
//     如果算法指出p是素数 那么他不一定是素数


const int trial = 5;
int witness(long int a, long int i, long int p)  //检测a^(i) %p
{
	if (i == 0) return 1;  //肯定正确
	
	int x = witness(a, i / 2, p);
	//这里用了递归的思想  如果i为偶数 那么a^i = a^(i/2) * a^(i/2)
	//如果i为奇数 那么a^i= a^(i/2) * a^(i/2) * a 在后面会做处理
	//这个递归其中的精妙还是很耐人寻味了


	if (x == 0) return 0;

	int y = (x*x) % p;

	//顺便判断定理2
	if (y == 1 && x != 1 && x != p - 1) return 0;

	//处理i为奇数
	if (i % 2 != 0) y = (a*y) % p;
	return y;

}

bool isprime(long int p)
{
	srand(time(0));

	//随机选择
	for (int i = 0; i < trial; ++i)
	{
		if (witness(rand()*(p - 2) / RAND_MAX + 2, p - 1, p) != 1) return false;
	}
	return true;
}


int main()
{

	cout << boolalpha << isprime(40487);


	return 0;
	
}