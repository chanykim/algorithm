// 1078_Zugling.cpp 
//
/*
입력
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
*/

#include <iostream>
#include <queue>

using namespace std;

const int MAX_N = 100;
const int MAX_M = 100;

int COLUMN, ROW;
int Zurg[MAX_N][MAX_M];
int pos_x, pos_y;
int TotalTime, remainZurg;

void MySolve();
void bfs(int x, int y, int time);
bool Inner(int x, int y);
int main()
{
	// 입력
	cin >> ROW;		// 지도 크기 열
	cin >> COLUMN;		// 지도 크기 행

	for (int i = 0; i < COLUMN; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			cin >> Zurg[i][j];
		}
	}

	// 방사능 오염 위치
	cin >> pos_x;
	cin >> pos_y;

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

	// 넓이 우선탐색
	// 배열 시작이 0부터 이어서 -1을 함. 추후 1부터 시작하도록 변경예정.
	bfs(pos_x - 1, pos_y - 1, 3);

	for (int i = 0; i < COLUMN; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			if (Zurg[i][j] == 1)
			{
				alive++;
			}

			if (count < Zurg[i][j])
			{
				count = Zurg[i][j];
			}
		}
	}

	remainZurg = alive;
	TotalTime = count;
}

struct KillZurg{
	int x;
	int y;
	int time;
};

queue <KillZurg> Q;
// 검색 순서 상->우->하->좌
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

void bfs(int x, int y, int time)
{
	bool innerMatrix = false;

	// 방문한 좌표와 시간 값을 큐에 저장.
	Q.push({ x, y, time });
	Zurg[y][x] = time;			// 문제에서 주어진 순서가 x축 y축으로 주어져서 col->y로, row->x로 함.

	while (!Q.empty())
	{
		// 큐의 내용을 pop
		KillZurg killzurg = Q.front(); Q.pop();

		// 방문한 좌표에서 상하좌우 방문할 수 있는 경우에 대해 큐에 저장.
		for (int i = 0; i < 4; i++)
		{
			// 문제에서 주어진 순서가 x축 y축으로 주어져서 col->y로, row->x로 함.
			// Zurg 배열 순서에 주의.
			innerMatrix = Inner(killzurg.x + dx[i], killzurg.y + dy[i]);
			if (innerMatrix && Zurg[killzurg.y + dy[i]][killzurg.x + dx[i]] == 1)
			{
				Zurg[killzurg.y + dy[i]][killzurg.x + dx[i]] = killzurg.time + 1;
				Q.push({ killzurg.x + dx[i], killzurg.y + dy[i], killzurg.time + 1 });
			}
		}
	}
}

bool Inner(int x, int y)
{
	bool inner = false;

	if ((x >= 0 && x < ROW) && (y >= 0 && y < COLUMN))
	{
		inner = true;
	}

	return inner;
}