
/*
입력 예
3
3 5
10 7
6 4
0 0
10 10

출력 예
34

입력 예2
5
10 7
25 50
34 60
80 35
70 30
0 0
100 100

출력 예2
260

입력 예3
3 
10 20
30 40
40 50
0 0
5 5

출력 예3
170

입력 예4
10 
35 10 
10 10 
36 40 
90 30 
70 30 
40 50 
60 70 
80 90 
100 100 
5 5
80 35
81 20

출력 예4
394
*/

#include <iostream>

using namespace std;

const int MAX_N = 20;
int N;
int XPos[MAX_N], YPos[MAX_N];
int StartX, StartY, EndX, EndY;
int ANSWER = 99999;
int Visited[MAX_N] = { 0, };

struct POSITION{
	int x;
	int y;
};
POSITION pos[MAX_N];

void MySolve();
void DFS(int Depth, int Vertex, int ParentVertex, int Dist);
int Distance(POSITION &Pos1, POSITION &Pos2);

int main()
{
	// 입력
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> XPos[i] >> YPos[i];
	}
	cin >> StartX >> StartY;
	cin >> EndX >> EndY;

	// 알고리즘
	MySolve();

	// 출력
	cout << "ANSWER = " << ANSWER << endl;

	return 0;
}

void MySolve()
{
	pos[0].x = StartX;
	pos[0].y = StartY;
	for (int i = 1; i <= N; i++)
	{
		pos[i].x = XPos[i];
		pos[i].y = YPos[i];
	}
	pos[N + 1].x = EndX;
	pos[N + 1].y = EndY;

	DFS(0, 0, 0, 0);
}

void DFS(int Depth, int Vertex, int ParentVertex, int Dist)
{
	// 정점(Vertex)에 방문했을 때
	Dist += Distance(pos[ParentVertex], pos[Vertex]);
	
	// 고객을 모두 방문후에 End지점에 오는 경우
	if (Depth >= N)
	{
		// 고객을 모두 방문하고 End 지점으로 가는 길의 거리
		Dist += Distance(pos[Vertex], pos[N + 1]);

		if (ANSWER > Dist)
		{
			ANSWER = Dist;
		}
		return;
	}

	// 출발점에서부터 고객을 방문
	for (int i = 0; i < N; i++)
	{
		if (Visited[i] == 0)
		{
			Visited[i] = 1;

			// 깊이우선탐색
			// 부모 Vertex를 알기위해서 깊이우선 탐색하기 전에 현재의 Vertex를 ParentVertex에 저장.
			DFS(Depth + 1, i + 1, Vertex, Dist);

			// 백트래킹으로 반환되었을 때, 방문했음을 삭제.
			Visited[i] = 0;
		}
	}
}

int Distance(POSITION &Pos1, POSITION &Pos2)
{
	POSITION Dist;

	if (Pos1.x < Pos2.x)
	{
		Dist.x = Pos2.x - Pos1.x;
	}
	else
	{
		Dist.x = Pos1.x - Pos2.x;
	}

	if (Pos1.y < Pos2.y)
	{
		Dist.y = Pos2.y - Pos1.y;
	}
	else
	{
		Dist.y = Pos1.y - Pos2.y;
	}

	return Dist.x + Dist.y;
}
