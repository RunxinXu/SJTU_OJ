#include <iostream>
#include <cstring>

using namespace std;
const int maxlen = 10000;
class hugeint
{
private:
	
	char num[maxlen];
	int sign; //1为正 -1为负 0为0
	int length; //实际存储长度
	bool iszero() const;
public:
	hugeint(int a = 0);
	hugeint(char *str);
	hugeint(const hugeint&);
	hugeint& operator=(const hugeint&);

	bool operator==(const hugeint&) const;
	bool operator==(const int&) const;
	bool operator != (const hugeint&) const;
	bool operator !=(const int&)const;

	bool operator>(const hugeint&) const;
	bool operator>(const int &)const;
	bool operator>=(const hugeint&other)const;
	bool operator>=(const int &x)const;

	bool operator<(const hugeint &other)const;
	bool operator<(const int &x)const;
	bool operator<=(const hugeint &other)const;
	bool operator<=(const int &x)const;

	/*  加法运算    */
	hugeint operator+(const hugeint &other)const;
	hugeint operator+(const int &x)const;
	hugeint operator+=(const hugeint &other);
	hugeint operator+=(const int &x);
	hugeint& operator++();//前置  
	hugeint operator++(int);//后置  

	/*  减法运算    */
	
	hugeint operator-(const hugeint &other)const;
	hugeint operator-(const int &x)const;
	hugeint operator-=(const hugeint &other);
	hugeint operator-=(const int &x);
	hugeint& operator--();//前置  
	hugeint operator--(int);//后置  

							/*  乘法运算    */
	hugeint operator*(const hugeint &other)const;
	hugeint operator*(const int &x)const;
	hugeint operator*=(const hugeint &other);
	hugeint operator*=(const int &x);

	/*  除法运算    */
	hugeint operator/(const hugeint &other)const;
	hugeint operator/(const int &x)const;
	hugeint operator/=(const hugeint &other);
	hugeint operator/=(const int &x);

	/*  求模运算    */ 
	hugeint operator%(const hugeint &other)const;//to do:debug  
	int operator%(const int &x)const;
	hugeint operator%=(const hugeint &other);
	int operator%=(const int &x);
	
	friend ostream& operator<<(ostream& output, const hugeint& n);
};

bool hugeint::iszero() const
{
	return sign == 0;
}

ostream& operator<<(ostream& output, const hugeint& n)
{
	if (n.sign == -1)
	{
		output << "-";
	}
	for (int i = n.length-1; i >=0; --i)   //逆序存储的
	{
		output << n.num[i];
	}
	return output;
}

hugeint::hugeint(int x)
{
	memset(num, '0', sizeof(num));                //初始化记得是0的字符哦！！！不是0
	if (x == 0) 
	{
		sign = 0;
		length = 1;
	}
	else
	{
		length = 0;
		if (x > 0)
		{
			sign = 1;
		}
		else
		{
			sign = -1;
			x = -x;
		}
		while (x > 0)
		{
			num[length] = x % 10 +'0';
			length++;
			x /= 10;
		}
	}
}

hugeint::hugeint(const hugeint& other)
{
	*this = other;  //用赋值号
}

hugeint::hugeint(char *str)//用字符初始化
{
	memset(num, '0', sizeof(num));
	if (str[0] == '-') sign = -1;
	else sign = 1;
	int i = 0;
	while (str[i]<'0' || str[i]>'9') i++;
	if (i == strlen(str))
	{
		sign = 0;
		length = 1;
		num[0] = '0';
	}
	else
	{
		length = strlen(str) - i;
		int k = i;
		for (int j = length - 1; j >= 0; --j)
		{
			num[j] = str[k];
			k++;
		}
	}
}

hugeint& hugeint::operator=(const hugeint & other)
{
	if (this == &other) return *this;

	sign = other.sign;
	length = other.length;
	for (int i = 0; i < length; ++i)
	{
		num[i] = other.num[i];

	}
	return *this;
}

bool hugeint::operator==(const hugeint &other)const
{
	if (this->sign != other.sign)return false;
	if (this->length != other.length)return false;
	int i;
	for (i = 0; i<length; ++i)
		if (this->num[i] != other.num[i])
			return false;
	return true;
}

bool hugeint::operator==(const int &x)const
{
	return ((*this) == hugeint(x));
}

bool hugeint::operator!=(const hugeint &other)const
{
	return !((*this) == other);
}

bool hugeint::operator!=(const int &x)const
{
	return !((*this) == x);
}

bool hugeint::operator>(const hugeint &other)const
{
	if (this->sign == other.sign)
	{
		bool flag = (sign == 1);
		if (this->length != other.length)
			return flag&(this->length > other.length);
		else
		{
			int i;
			for (i = length - 1; i >= 0; --i)
				if (this->num[i] > other.num[i])
					return (flag ? true : false);
				else if (this->num[i] < other.num[i])
					return (flag ? false : true);
			return false;
		}
	}
	else
		return (this->sign > other.sign);
}

bool hugeint::operator>(const int &x)const
{
	return ((*this) > hugeint(x));
}

bool hugeint::operator>=(const hugeint &other)const
{
	return (((*this) > other) || ((*this) == other));
}

bool hugeint::operator>=(const int &x)const
{
	return ((*this) >= hugeint(x));
}

bool hugeint::operator<(const hugeint &other)const
{
	return !((*this) >= other);
}

bool hugeint::operator<(const int &x)const
{
	return ((*this) < hugeint(x));
}

bool hugeint::operator<=(const hugeint &other)const
{
	return !((*this) > other);
}

bool hugeint::operator<=(const int &x)const
{
	return ((*this) < hugeint(x));
}

//两个大整数的加法
hugeint hugeint::operator+(const hugeint & other) const
{
	if (sign == 0) return other;
	if (other.sign == 0) return *this;

	if (sign == other.sign)
	{
		hugeint x;
		x.sign = sign;

		int carry = 0;
		int i = 0, j = 0, k = 0;
		while (i < length && j < other.length)
		{
			int tmp = num[i] - '0' + other.num[j] - '0' + carry;

			x.num[k] = tmp % 10 + '0';
			carry = tmp / 10;
			k++; i++; j++;
		}
		while (i < length)
		{
			int tmp = num[i] - '0' + carry;
			x.num[k] = tmp % 10 + '0';
			carry = tmp / 10;
			k++; i++;
		}
		while (j < other.length)
		{
			int tmp = other.num[i] - '0' + carry;
			x.num[k] = tmp % 10 + '0';
			carry = tmp / 10;
			k++; j++;
		}
		if (carry != 0)
		{
			x.num[k] = carry + '0';
			k++;
			x.length = k;
		}
		else
		{
			x.length = k;
		}
		return x;
	}
	else
	{
		if (sign == -1)
		{
			hugeint x = *this;
			x.sign = 1;
			return(other - x);  //负数加正数变成 正数减去负数绝对值
		}
		else
		{
			hugeint x = other;
			x.sign = 1;
			return(*this - x);
		}
	}
}

hugeint hugeint::operator+(const int &x)const
{
	return ((*this) + hugeint(x));
}

hugeint hugeint::operator+=(const hugeint &other)
{
	(*this) = (*this) + other;
	return *this;
}

hugeint hugeint::operator+=(const int &x)
{
	(*this) = (*this) + hugeint(x);
	return *this;
}

hugeint& hugeint::operator++()
{
	(*this) = (*this) + hugeint(1);
	return *this;
}

hugeint hugeint::operator++(int)
{
	hugeint temp(*this);
	(*this) = (*this) + hugeint(1);
	return temp;
}


//大整数的减法

hugeint hugeint::operator-(const hugeint &other)const
{
	if (*this < other)
	{
		hugeint tmp = other - (*this);
		tmp.sign = -1;
		return tmp;
	}
	if (*this == other) return hugeint(0);
	hugeint tmp(*this);
	tmp.sign = 1;

	for (int i = 0; i < tmp.length; ++i)
	{
		tmp.num[i] = tmp.num[i] - other.num[i]+'0';
		if (tmp.num[i] -'0'< 0)
		{
			tmp.num[i] += 10;
			tmp.num[i + 1]--;
		}
		
	}
	for (int i = tmp.length - 1; i >= 0; i--)
	{
		if (tmp.num[i]!='0' ) {
			tmp.length = i + 1; break;
		}
	}
	return tmp;
}

hugeint hugeint::operator-(const int &x)const
{
	return ((*this) - hugeint(x));
}

hugeint hugeint::operator-=(const hugeint &other)
{
	(*this) = (*this) - other;
	return *this;
}

hugeint hugeint::operator-=(const int &x)
{
	(*this) = (*this) - hugeint(x);
	return *this;
}

hugeint& hugeint::operator--()
{
	(*this) = (*this) - hugeint(1);
	return *this;
}

hugeint hugeint::operator--(int)
{
	hugeint temp(*this);
	(*this) = (*this) - hugeint(1);
	return temp;
}

//大整数的乘法

hugeint hugeint::operator*(const hugeint &other) const
{
	if (iszero() || other.iszero()) return hugeint(0);

	hugeint tmp(0);
	tmp.sign = sign*other.sign;
	int i, j;
	for ( i = 0; i < length; ++i)        //本质还是算竖式	
	{
		for ( j = 0; j < other.length; ++j)
		{
			tmp.num[i + j] = tmp.num[i+j]+(num[i] - '0')*(other.num[j] - '0');   //刚好在下标i+j地方
			tmp.num[i + j + 1] += (tmp.num[i + j]-'0') / 10;
			tmp.num[i + j] = (tmp.num[i+j]-'0')%10+'0';                                   //这里是进位
			//由于每一次都是从最低位向最高位推进所以该算法不会出现某一位值>=10的情况
		}
	}
	tmp.length = i - 1 + j - 1 +1;  //最后一步下标是i-1+j-1 长度就是这个加上一
	if (tmp.num[tmp.length]!='0') tmp.length++;   //如果最后一步有进位的话 length要加一
	return tmp;
}

hugeint hugeint::operator*(const int &x)const
{
	return (*this)*hugeint(x);
}

hugeint hugeint::operator*=(const hugeint &other)
{
	(*this) = (*this) * other;
	return *this;
}

hugeint hugeint::operator*=(const int &x)
{
	return (*this)*hugeint(x);
}


//大整数的除法
int subtract(char *p1, char*p2, int len1, int len2)
{
	//用长度为len1的大整数p1减去长度为len2的大整数p2 存在p1中
	//返回值代表结果的长度 不够减返回-1 正好够返回0
	int i;
	if (len1 < len2) return -1;
	if (len1 == len2)
	{
		for (i = len1 - 1; i >= 0; i--)
		{
			if (p1[i] > p2[i]) break;
			else if (p1[i] < p2[i]) return -1;
		}
	}
	for (i = 0; i <= len1 - 1; i++)
	{
		p1[i] = p1[i] - p2[i] + '0';
		if (p1[i] < '0')
		{
			p1[i] += 10;  //向高位借位
			p1[i + 1]--;
		}
	
	}
	for (i = len1 - 1; i >= 0; i--)
	{
		if (p1[i]!='0') return (i + 1);  //减完长度还是len1
	}
	return 0;  //减完刚好为0
}
hugeint hugeint::operator/(const hugeint& other) const
{
	if (length < other.length) return hugeint(0);

	int i, t, z;
	hugeint result(0), n1(*this), n2(other);

	result.sign = n1.sign*n2.sign;
	t = n1.length - n2.length;
	if (t > 0)
	{
		for (i = n1.length-1; i >= 0; --i)
		{
			if (i >= t) n2.num[i] = n2.num[i - t];
			else n2.num[i] = '0';
			//移位到高位对齐的位置用于进行减法
		}
	}
	n2.length = n1.length;
	for (i = 0; i <= t; ++i)    //减法后移位 可以进行t+1次
	{
		while ((z = subtract(n1.num, n2.num + i, n1.length, n2.length - i)) >= 0)    //这个n2.num+1的指针移动使数组长度减一也太妙了吧
		{
			n1.length = z;   //实时更新被减数的长度 实际上就是被减到缩减了的时候 更新后传给subtract则会返回-1
			result.num[t - i]++; //减的次数+1 从高位开始
		}

	}
	for (i = maxlen - 1; i >= 0; --i) if (result.num[i]!='0') break;
	if (i >= 0) result.length = i + 1;           //实际上就是去除高位的0的影响 找到实际的长度
	else return hugeint(0);
	return result;
}
hugeint hugeint::operator/(const int &x)const
{
	return (*this) / hugeint(x);
}

hugeint hugeint::operator/=(const hugeint &other)
{
	(*this) = (*this) / other;
	return *this;
}

hugeint hugeint::operator/=(const int &x)
{
	return (*this) / hugeint(x);
}

hugeint hugeint::operator%(const hugeint&other)const
{
	if (length < other.length) return *this;

	int i, t, z;
	hugeint n1(*this), n2(other);
	 t = n1.length - n2.length;
	if (t > 0)
	{
		for ( i = n1.length - 1; i >= 0; --i)
		{
			if (i >= t) n2.num[i] = n2.num[i - t];
			else n2.num[i] = '0';
		}
	}
	n2.length = n1.length;
	for (i = 0; i <= t; ++i)
	{
		while ((z = subtract(n1.num, n2.num + i, n1.length, n2.length - i)) >= 0)
		{
			n1.length = z;
			if (z == 0) return hugeint(0);
		}
	}
	return n1;
}
hugeint hugeint::operator%=(const hugeint &other)
{
	(*this) = (*this) % other;
	return *this;
}

int hugeint::operator%(const int &x)const
{
	hugeint tmp=(*this) % hugeint(x);
	if (tmp.length == 0) return 0;

	int xx=0;
	
	for (int i = 0; i < tmp.length; ++i)
	{
		xx = xx * 10 + tmp.num[i];
	}
	return xx;
}

int hugeint::operator%=(const int &x)
{
	int tmp = (*this) % x;
	(*this) = hugeint(tmp);
	return tmp;
}
int main()
{
	hugeint a("9984564621"), b("1321321");
	hugeint c = a + b;
	cout << c << endl;
	c = a - b;
	cout << c << endl;
	c = b - a;
	cout << c << endl;
	c = a*b;
	cout << c << endl;
	c = a / b;
	cout << c << endl;
	c = a%b;
	cout << c << endl;
	return 0;
}


//大数类笔记：
/*
1.分清你是以数字0为基准还是‘0’为基准！！！！！坑！！！
2.数字存储是逆序存储，便于计算
3.大数加法：竖式计算 用carry表示进位
4.大数减法：只要保证被减数大 那么借位直接在高位减去即可
5.大数乘法：也是竖式 第一个数下标i的和第二个数下标j的乘积正好放在result的i+j下标中 进位则在i+j+1中 需要检查最后有没有进位
6.大数除法：用的是不断减 减到不能减 统计减的次数 之后后移继续减
7.大数的模：同除法 只是不用维护一个减的次数以及result 只需要最后的那个减剩下来的n1


*/
