#include <iostream>
#include <stack>
#include <queue>


using namespace std;

//走迷宫 分别用BFS （队列） 与 回溯法（栈） 实现

void find_path_bfs(int**maze, int m, int n)
{
	struct node
	{
		int x, y;
	};
	queue<node> a;
	node tmp;
	tmp.x = 0; tmp.y = 0;
	a.push(tmp);
	maze[0][0] = 2;
	while (!a.empty())   //不断标记 如果可以走且使其标记数字变小那么就更新 然后将其入队
	{
		tmp = a.front();
		a.pop();
		int x = tmp.x, y = tmp.y;
		if (x != 0 && maze[x - 1][y] != 1 && (maze[x - 1][y] > maze[x][y] + 1||maze[x-1][y]==0))
		{
			maze[x - 1][y] = maze[x][y] + 1;
			node hehe; hehe.x = x - 1; hehe.y = y;
			a.push(hehe);
		}
		if (x != m - 1 && maze[x + 1][y] != 1 && (maze[x + 1][y] > maze[x][y] + 1 || maze[x + 1][y] == 0))
		{
			maze[x + 1][y] = maze[x][y] + 1;
			node hehe; hehe.x = x + 1; hehe.y = y;
			a.push(hehe);
		}
		if (y != 0 && maze[x][y - 1] != 1 && (maze[x][y - 1] > maze[x][y] + 1 || maze[x ][y-1] == 0))
		{
			maze[x][y - 1] = maze[x][y] + 1;
			node hehe; hehe.x = x; hehe.y = y-1;
			a.push(hehe);
		}
		if (y != n-1 && maze[x][y + 1] != 1 && (maze[x][y + 1] > maze[x][y] + 1 || maze[x ][y+1] == 0))
		{
			maze[x][y + 1] = maze[x][y] + 1;
			node hehe; hehe.x = x; hehe.y = y+1;
			a.push(hehe);
		}
	}
	//BFS遍历结束
	int size = maze[m - 1][n - 1] - 1;  //最短路径一共经过size个点 
	
	//从终点逆向查找最短路径并压入栈  
	stack<node> result;
	int x = m - 1, y = n - 1;
	node xixi; xixi.x = x; xixi.y = y;
	result.push(xixi);
	
	for (int i = 0; i < size-1; ++i)
	{
		if (x != 0 && maze[x - 1][y] == maze[x][y] - 1)
		{
			node hehe; hehe.x = x - 1; hehe.y = y;
			result.push(hehe);
			x--;
			continue;
		}
		if (x != m-1 && maze[x + 1][y] == maze[x][y] - 1)
		{
			node hehe; hehe.x = x + 1; hehe.y = y;
			result.push(hehe);
			x++;
			continue;

		}
		if (y!= 0 && maze[x ][y-1] == maze[x][y] - 1)
		{
			node hehe; hehe.x = x; hehe.y = y-1;
			result.push(hehe);
			y--;
			continue;
		}
		if (y != n-1 && maze[x][y + 1] == maze[x][y] - 1)
		{
			node hehe; hehe.x = x; hehe.y = y + 1;
			result.push(hehe);
			y++;
			continue;
		}

	}
	//打印正序的路径
	while (!result.empty())
	{
		node hehe = result.top();
		result.pop();
		cout << hehe.x << hehe.y << endl;
	}

}

//回溯法相对而言稍逊一筹 因为他目光短浅 只能找到走出迷宫的路 但是不能确保就是最短的路程
void find_path_back(int**maze, int m, int n)
{
	struct node
	{
		int x;
		int y;
		int dir;  //0上1右2下3左

		node(int xx, int yy, int ddir) :x(xx), y(yy), dir(ddir) {};
	};

	stack<node> result;
	node tmp(0, 0, -1);
	maze[0][0] = 2;
	node hehe(0,0,0);
	result.push(tmp);
	int flag = 0;


	//我这个代码可能和书有不同 但是都可以
	//dir表示的意思是下一个方向往哪走 我每次新的结点进去都是dir=-1 之后使用前会dir++ 从0开始到3 如果是4直接gg踢出去 并且将迷宫的标记去除
	while (!result.empty())
	{
		tmp = result.top();
		result.pop();

		tmp.dir++;
		if (tmp.dir == 4)
		{
			maze[tmp.x][tmp.y] = 0;
			continue;
		}
		switch (tmp.dir)
		{
		case 0:
			if (tmp.x != 0 && maze[tmp.x - 1][tmp.y] == 0)
			{
				hehe.x = tmp.x - 1; hehe.y = tmp.y;hehe.dir=-1;
				maze[hehe.x][hehe.y] = 2;
				flag = 1;
			}
			break;
		case 1:
			if (tmp.y != n-1 && maze[tmp.x ][tmp.y+1] == 0)
			{
				hehe.x = tmp.x; hehe.y = tmp.y + 1;hehe.dir= -1;

				maze[hehe.x][hehe.y] = 2;
				flag = 1;
			}
			break;
		case 2:
			if (tmp.x != m-1 && maze[tmp.x + 1][tmp.y] == 0)
			{
				hehe.x = tmp.x + 1; hehe.y = tmp.y;hehe.dir=-1;

				maze[hehe.x][hehe.y] = 2;
				flag = 1;
			}
			break;
		case 3:
			if (tmp.y != 0 && maze[tmp.x][tmp.y-1] == 0)
			{
				hehe.x = tmp.x; hehe.y = tmp.y - 1;hehe.dir=-1;
				maze[hehe.x][hehe.y] = 2;
				flag = 1;
			}
			break;
		default: continue;
		}

		result.push(tmp);
		if(flag)result.push(hehe);
		flag = 0;
		

		//如果找到出口  及时break
		if (hehe.x == m - 1 && hehe.y == n - 1)
		{
			break;
		}
		
	}

	stack<node> true_result;
	while (!result.empty())
	{
		node xixi = result.top();
		result.pop();
		true_result.push(xixi);
	}
	while (!true_result.empty())
	{
		node xixi = true_result.top();
		true_result.pop();
		cout << xixi.x << xixi.y << endl;
	}

	
}

int main()
{
	int m = 10, n = 10; //10*10的迷宫
	int **maze = new int*[10];
	for (int i = 0; i < 10; ++i) maze[i] = new int[10];
	int maze_tmp[10][10]= { {0,0,1,1,1,1,1,0,0,0},{1,0,1,0,0,0,0,0,1,1},{1,0,0,0,1,1,0,1,1,1},{1,1,0,1,1,1,0,1,1,1},{1,1,0,1,1,1,0,0,0,1},
	{1,0,0,1,1,1,0,1,1,1},{1,1,0,0,0,0,0,1,1,1},{1,1,0,1,1,0,1,1,1,1},{1,1,1,1,1,0,0,0,0,0},{1,1,1,1,1,0,1,1,0,0} };
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
			maze[i][j] = maze_tmp[i][j];
	}
	//由于节省空间 所以寻找路径之后maze是会被标记的 不能重复使用！！！
	find_path_bfs(maze,m,n);
	cout << endl;

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
			maze[i][j] = maze_tmp[i][j];
	}

	find_path_back(maze, m, n);
	cout << endl;

	for (int i = 0; i < 10; ++i)
		delete[]maze[i];
	delete[]maze;

	


	return 0;
}