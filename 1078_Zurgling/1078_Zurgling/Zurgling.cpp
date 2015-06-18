// 1078_Zugling.cpp 
//
/*
�Է�
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
	// �Է�
	cin >> ROW;		// ���� ũ�� ��
	cin >> COLUMN;		// ���� ũ�� ��

	for (int i = 0; i < COLUMN; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			cin >> Zurg[i][j];
		}
	}

	// ���� ���� ��ġ
	cin >> pos_x;
	cin >> pos_y;

	// �˰���
	MySolve();

	// ���
	cout << TotalTime << endl;
	cout << remainZurg << endl;

	return 0;
}

void MySolve()
{
	int alive = 0;
	int count = 0;

	// ���� �켱Ž��
	// �迭 ������ 0���� �̾ -1�� ��. ���� 1���� �����ϵ��� ���濹��.
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
// �˻� ���� ��->��->��->��
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

void bfs(int x, int y, int time)
{
	bool innerMatrix = false;

	// �湮�� ��ǥ�� �ð� ���� ť�� ����.
	Q.push({ x, y, time });
	Zurg[y][x] = time;			// �������� �־��� ������ x�� y������ �־����� col->y��, row->x�� ��.

	while (!Q.empty())
	{
		// ť�� ������ pop
		KillZurg killzurg = Q.front(); Q.pop();

		// �湮�� ��ǥ���� �����¿� �湮�� �� �ִ� ��쿡 ���� ť�� ����.
		for (int i = 0; i < 4; i++)
		{
			// �������� �־��� ������ x�� y������ �־����� col->y��, row->x�� ��.
			// Zurg �迭 ������ ����.
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