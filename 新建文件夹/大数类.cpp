#include <iostream>
#include <cstring>

using namespace std;
const int maxlen = 10000;
class hugeint
{
private:
	
	char num[maxlen];
	int sign; //1Ϊ�� -1Ϊ�� 0Ϊ0
	int length; //ʵ�ʴ洢����
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

	/*  �ӷ�����    */
	hugeint operator+(const hugeint &other)const;
	hugeint operator+(const int &x)const;
	hugeint operator+=(const hugeint &other);
	hugeint operator+=(const int &x);
	hugeint& operator++();//ǰ��  
	hugeint operator++(int);//����  

	/*  ��������    */
	
	hugeint operator-(const hugeint &other)const;
	hugeint operator-(const int &x)const;
	hugeint operator-=(const hugeint &other);
	hugeint operator-=(const int &x);
	hugeint& operator--();//ǰ��  
	hugeint operator--(int);//����  

							/*  �˷�����    */
	hugeint operator*(const hugeint &other)const;
	hugeint operator*(const int &x)const;
	hugeint operator*=(const hugeint &other);
	hugeint operator*=(const int &x);

	/*  ��������    */
	hugeint operator/(const hugeint &other)const;
	hugeint operator/(const int &x)const;
	hugeint operator/=(const hugeint &other);
	hugeint operator/=(const int &x);

	/*  ��ģ����    */ 
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
	for (int i = n.length-1; i >=0; --i)   //����洢��
	{
		output << n.num[i];
	}
	return output;
}

hugeint::hugeint(int x)
{
	memset(num, '0', sizeof(num));                //��ʼ���ǵ���0���ַ�Ŷ����������0
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
	*this = other;  //�ø�ֵ��
}

hugeint::hugeint(char *str)//���ַ���ʼ��
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

//�����������ļӷ�
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
			return(other - x);  //������������� ������ȥ��������ֵ
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


//�������ļ���

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

//�������ĳ˷�

hugeint hugeint::operator*(const hugeint &other) const
{
	if (iszero() || other.iszero()) return hugeint(0);

	hugeint tmp(0);
	tmp.sign = sign*other.sign;
	int i, j;
	for ( i = 0; i < length; ++i)        //���ʻ�������ʽ	
	{
		for ( j = 0; j < other.length; ++j)
		{
			tmp.num[i + j] = tmp.num[i+j]+(num[i] - '0')*(other.num[j] - '0');   //�պ����±�i+j�ط�
			tmp.num[i + j + 1] += (tmp.num[i + j]-'0') / 10;
			tmp.num[i + j] = (tmp.num[i+j]-'0')%10+'0';                                   //�����ǽ�λ
			//����ÿһ�ζ��Ǵ����λ�����λ�ƽ����Ը��㷨�������ĳһλֵ>=10�����
		}
	}
	tmp.length = i - 1 + j - 1 +1;  //���һ���±���i-1+j-1 ���Ⱦ����������һ
	if (tmp.num[tmp.length]!='0') tmp.length++;   //������һ���н�λ�Ļ� lengthҪ��һ
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


//�������ĳ���
int subtract(char *p1, char*p2, int len1, int len2)
{
	//�ó���Ϊlen1�Ĵ�����p1��ȥ����Ϊlen2�Ĵ�����p2 ����p1��
	//����ֵ�������ĳ��� ����������-1 ���ù�����0
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
			p1[i] += 10;  //���λ��λ
			p1[i + 1]--;
		}
	
	}
	for (i = len1 - 1; i >= 0; i--)
	{
		if (p1[i]!='0') return (i + 1);  //���곤�Ȼ���len1
	}
	return 0;  //����պ�Ϊ0
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
			//��λ����λ�����λ�����ڽ��м���
		}
	}
	n2.length = n1.length;
	for (i = 0; i <= t; ++i)    //��������λ ���Խ���t+1��
	{
		while ((z = subtract(n1.num, n2.num + i, n1.length, n2.length - i)) >= 0)    //���n2.num+1��ָ���ƶ�ʹ���鳤�ȼ�һҲ̫���˰�
		{
			n1.length = z;   //ʵʱ���±������ĳ��� ʵ���Ͼ��Ǳ����������˵�ʱ�� ���º󴫸�subtract��᷵��-1
			result.num[t - i]++; //���Ĵ���+1 �Ӹ�λ��ʼ
		}

	}
	for (i = maxlen - 1; i >= 0; --i) if (result.num[i]!='0') break;
	if (i >= 0) result.length = i + 1;           //ʵ���Ͼ���ȥ����λ��0��Ӱ�� �ҵ�ʵ�ʵĳ���
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


//������ʼǣ�
/*
1.��������������0Ϊ��׼���ǡ�0��Ϊ��׼�����������ӣ�����
2.���ִ洢������洢�����ڼ���
3.�����ӷ�����ʽ���� ��carry��ʾ��λ
4.����������ֻҪ��֤�������� ��ô��λֱ���ڸ�λ��ȥ����
5.�����˷���Ҳ����ʽ ��һ�����±�i�ĺ͵ڶ������±�j�ĳ˻����÷���result��i+j�±��� ��λ����i+j+1�� ��Ҫ��������û�н�λ
6.�����������õ��ǲ��ϼ� �������ܼ� ͳ�Ƽ��Ĵ��� ֮����Ƽ�����
7.������ģ��ͬ���� ֻ�ǲ���ά��һ�����Ĵ����Լ�result ֻ��Ҫ�����Ǹ���ʣ������n1


*/
