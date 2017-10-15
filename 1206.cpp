#include <iostream>
#include <cstring>
#include <stack>

using namespace std;


int main()
{
	stack<char*> hehe;
	char* tmp = new char[50];
	while (cin >> tmp)
	{
		if (strcmp(tmp, "begin") != 0 && strcmp(tmp, "if") != 0 && strcmp(tmp, "then") != 0 &&strcmp(tmp, "else") != 0 && strcmp(tmp, "end") != 0) continue;
		if (strcmp(tmp, "begin") == 0 || strcmp(tmp, "if") == 0 || strcmp(tmp, "then") == 0) {
			hehe.push(tmp); 
			tmp = new char[50]; continue;
		}
		if (strcmp(tmp, "else") == 0)
		{

			if (hehe.empty() || strcmp(hehe.top(), "then") != 0) { cout << "Error!"; return 0; }
			else
			{
				hehe.pop();
				if (hehe.empty() || strcmp(hehe.top(), "if") != 0) { cout << "Error!"; return 0; }
				else
				{
					hehe.pop();
				}
			}
			continue;
		}
		if (strcmp(tmp, "end") == 0)
		{
			int flag = 0; //0表示需要then 1表示需要if
			while (!hehe.empty() && strcmp(hehe.top(), "begin") != 0)
			{
				if (flag)
				{
					if (strcmp(hehe.top(), "if") != 0) { cout << "Error!"; return 0; }
					else
					{
						hehe.pop();
						flag = 0;
					}
				}
				else
				{
					if (strcmp(hehe.top(), "then") != 0) { cout << "Error!"; return 0; }
					else
					{
						hehe.pop();
						flag = 1;
					}
				}
			}
			if (strcmp(hehe.top(), "begin") == 0)
			{
				hehe.pop();
			}
			else
			{
				cout << "Error!"; return 0;
			}
			continue;
		}
	}
	if (hehe.empty()) cout << "Match!";
	else
	{
		int flag = 0; //0表示需要then 1表示需要if
		while (!hehe.empty())
		{
			if (flag)
			{
				if (strcmp(hehe.top(), "if") != 0) { cout << "Error!"; return 0; }
				else
				{
					hehe.pop();
					flag = 0;
				}
			}
			else
			{
				if (strcmp(hehe.top(), "then") != 0) { cout << "Error!"; return 0; }
				else
				{
					hehe.pop();
					flag = 1;
				}
			}
		}
		cout << "Match!";
	}
	return 0;
}

//存进栈的应该是有内存的指针而不是野指针！！！！！