
/*
입력 예
7 8
0 0 1 0 0 0 0
0 0 1 1 0 0 0
0 0 0 1 1 0 0
1 0 1 1 1 1 1
1 1 1 1 0 1 1
0 0 1 1 1 0 0
0 0 1 1 1 0 0
0 0 0 1 0 0 0
3 5

출력 예
9
0
*/
#include <iostream>

using namespace std;

const int MAX_COL = 100;
const int MAX_ROW = 100;

int Column, Row;
int Pos_x, Pos_y;
int Zurg[MAX_COL][MAX_ROW];
int TotalTime, remainZurg;

// 상하좌우 탐색을 위한 조건
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void MySolve();
void dfs(int x, int y, int time);
bool Inner(int x, int y);
int main()
{
	// 입력
	cin >> Row;
	cin >> Column;

	for (int i = 0; i < Column; i++)
	{
		for (int j = 0; j < Row; j++)
		{
			cin >> Zurg[i][j];
		}
	}

	cin >> Pos_x >> Pos_y;

	// 알고리즘
	MySolve();

	// 출력
	cout << TotalTime << endl;
	cout << remainZurg << endl;

	return 0;
}

void MySolve()
{
	int alive = 0;
	int count = 0;

	// 깊이우선탐색
	//dfs(Pos_x, Pos_y, 3);
	dfs(Pos_y-1, Pos_x-1, 3);

	for (int i = 0; i < Column; i++)
	{
		for (int j = 0; j < Row; j++)
		{
			if (Zurg[i][j] == 1)
			{
				// 살아남은 저그의 수
				alive++;
			}

			if (Zurg[i][j] > count)
			{
				count = Zurg[i][j];
			}
		}
	}

	TotalTime = count;
	remainZurg = alive;
}

void dfs(int x, int y, int time)
{
	if (Zurg[x][y] != 1 && Zurg[x][y] <= time)
	{
		// 이 조건에 해당하는 경우 이미 visit해서 값을 time으로 변경을 하고,
		// 상하좌우 탐색을 할 때, 현재 dfs 함수에 의해 동작중인 time보다 적은 경우는
		// dfs 함수를 하지 않도록 구현함.
		return;
	}
	else
	{
		Zurg[x][y] = time;
	}

	// 상하좌우에 1이 있는지 탐색.
	for (int i = 0; i < 4; i++)
	{
		// 주어진 col x row 영역안쪽이면서 셀에 1이 있는지 확인
		if (Inner(x + dx[i], y + dy[i]) && Zurg[x + dx[i]][y + dy[i]] == 1)
		{
			// 깊이우선 탐색
			// 위치의 값을 시간에 해당하는 값으로 변경.
			dfs(x + dx[i], y + dy[i], time + 1);
		}
		else if (Inner(x + dx[i], y + dy[i]) && Zurg[x + dx[i]][y + dy[i]] > time + 1)
		{
			// 재귀함수에 의해 이전에 값이 변경된 경우 이에 대해 다시 값을 재조정하기 위해...
			dfs(x + dx[i], y + dy[i], time + 1);
		}
	}

}

bool Inner(int x, int y)
{
	bool inner = false;

	if ((x >= 0 && x < Column) && (y >= 0 && y < Row))
	{
		inner = true;
	}

	return inner;
}