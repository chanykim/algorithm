
#include <iostream>

using namespace std;

const int MAX_N = 1002;
int M, N;
int Box[MAX_N][MAX_N];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int ANSWER = -1;

typedef struct _Tomato{
	int Row;
	int Column;
	int Day;
}TOMATO;

void MySolve();
void BFS(int R, int C, int D);
int InnerArray(int Row, int Column);
int main()
{
	int test_case;
	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	for (test_case = 1; test_case <= 1; test_case++)
	{
		// input
		cin >> M >> N;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				cin >> Box[i][j];
			}
		}

		// write algorithm
		MySolve();

		// Output
		cout << ANSWER << endl;
	}
	return 0;
}

TOMATO Q[MAX_N];
int front, rear;
void MySolve()
{
	front = 0, rear = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			// 익은 토마토가 놓여있는 위치 검색하여 Queue에 저장.
			if (Box[i][j] == 1)
			{
				Box[i][j] = 10;
				Q[rear].Row = i;
				Q[rear].Column = j;
				Q[rear].Day = 10;
				rear++;
			}
		}
	}

	// Quene에 저장된 위치를 BFS로 탐색
	BFS(Q[front].Row, Q[front].Column, 10);

	// 결과값
	int TotalDay = 0;
	int nRemainTomato = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			// 토마토가 모두 익지 못하는 상황
			if (Box[i][j] == 0)
			{
				nRemainTomato = -1;
			}
			else if (Box[i][j] > 1)
			{
				if (Box[i][j] > TotalDay)
				{
					TotalDay = Box[i][j];
				}
			}
		}
	}

	if (nRemainTomato == -1)
	{
		ANSWER = -1;
	}
	else
	{
		ANSWER = TotalDay - 10;
	}
}

void BFS(int R, int C, int D)
{
	TOMATO Tomato;

	Tomato.Row = R;
	Tomato.Column = C;
	Tomato.Day = D;

	// Q 배열에 들어있는 모든것을 탐색할때까지
	while (front <= rear)
	{
		Tomato.Row = Q[front].Row;
		Tomato.Column = Q[front].Column;
		Tomato.Day = Q[front].Day;

		for (int i = 0; i < 4; i++)
		{
			int Row = Tomato.Row + dy[i];
			int Column = Tomato.Column + dx[i];

			if (InnerArray(Row, Column) &&
				(Box[Row][Column] == 0))
			{
				Box[Row][Column] = Tomato.Day + 1;
				Q[rear].Row = Row;
				Q[rear].Column = Column;
				Q[rear].Day = Tomato.Day + 1;
				rear++;
			}
		}

		front++;
	}
}

#if 0
#include <queue>
queue <TOMATO> Q;
void MySolve()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			// 익은 토마토가 놓여있는 위치 검색
			if (Box[i][j] == 1)
			{
				Box[i][j] = 10;
				Q.push({i, j, 10});
			}
		}
	}

	// 너비우선 탐색
	TOMATO Tomato;
	Tomato = Q.front();
	BFS(Tomato.Row, Tomato.Column, Tomato.Day);

	// 결과값
	int TotalDay = 0;
	int nRemainTomato = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			// 토마토가 모두 익지 못하는 상황
			if (Box[i][j] == 0)
			{
				nRemainTomato = -1;
			}
			else if (Box[i][j] > 1)
			{
				if (Box[i][j] > TotalDay)
				{
					TotalDay = Box[i][j];
				}
			}
		}
	}

	if (nRemainTomato == -1)
	{
		ANSWER = -1;
	}
	else
	{
		ANSWER = TotalDay - 10;
	}
}

void BFS(int R, int C, int D)
{
	TOMATO Tomato;

	while (!Q.empty())
	{
		Tomato = Q.front();
		Q.pop();

		// 우/하/좌/상 탐색
		for (int i = 0; i < 4; i++)
		{
			int Row = Tomato.Row + dy[i];
			int Column = Tomato.Column + dx[i];

			if (InnerArray(Row, Column) &&
				(Box[Row][Column] == 0))
			{				
				Box[Row][Column] = Tomato.Day + 1;
				Q.push({ Row, Column, Tomato.Day + 1});
			}
		}
	}
}
#endif

int InnerArray(int Row, int Column)
{
	if ((Row >= 0 && Row < N) && (Column >= 0 && Column < M))
	{
		return 1;
	}

	return 0;
}
