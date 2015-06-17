
/*
�Է� ��
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

��� ��
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

// �����¿� Ž���� ���� ����
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void MySolve();
void dfs(int x, int y, int time);
bool Inner(int x, int y);
int main()
{
	// �Է�
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

	// ���̿켱Ž��
	//dfs(Pos_x, Pos_y, 3);
	dfs(Pos_y-1, Pos_x-1, 3);

	for (int i = 0; i < Column; i++)
	{
		for (int j = 0; j < Row; j++)
		{
			if (Zurg[i][j] == 1)
			{
				// ��Ƴ��� ������ ��
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
		// �� ���ǿ� �ش��ϴ� ��� �̹� visit�ؼ� ���� time���� ������ �ϰ�,
		// �����¿� Ž���� �� ��, ���� dfs �Լ��� ���� �������� time���� ���� ����
		// dfs �Լ��� ���� �ʵ��� ������.
		return;
	}
	else
	{
		Zurg[x][y] = time;
	}

	// �����¿쿡 1�� �ִ��� Ž��.
	for (int i = 0; i < 4; i++)
	{
		// �־��� col x row ���������̸鼭 ���� 1�� �ִ��� Ȯ��
		if (Inner(x + dx[i], y + dy[i]) && Zurg[x + dx[i]][y + dy[i]] == 1)
		{
			// ���̿켱 Ž��
			// ��ġ�� ���� �ð��� �ش��ϴ� ������ ����.
			dfs(x + dx[i], y + dy[i], time + 1);
		}
		else if (Inner(x + dx[i], y + dy[i]) && Zurg[x + dx[i]][y + dy[i]] > time + 1)
		{
			// ����Լ��� ���� ������ ���� ����� ��� �̿� ���� �ٽ� ���� �������ϱ� ����...
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