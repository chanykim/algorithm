
#include <iostream>

using namespace std;

int N;		// 2���� �迭�� ũ��
// �˻����� (������ -> �Ʒ� -> ���� -> ����)
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

const int MAX_N = 100;
int Matrix[MAX_N][MAX_N];

void MySolve();
bool Inner(int col, int row);
int main()
{
	// �Է�
	cin >> N;

	// �˰���
	MySolve();

	// ���
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (j < N - 1)
			{
				cout << Matrix[i][j] << " ";
			}
			else if (j == N - 1)
			{
				cout << Matrix[i][j] << endl;
			}			
		}
	}
	return 0;
}

void MySolve()
{
	int num = 1;
	int i = 0, j = 0;
	bool visit = false;
	int EndNumber = N*N;

	// �־��� ũ���� �迭�� ��� 0���� ä��
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Matrix[i][j] = 0;
		}
	}

	Matrix[0][0] = num;
	while (num < EndNumber)
	{
		// row���� ���� ��, left �������� �����ϸ鼭 ���� 0���� Ȯ��
		while (Matrix[i][j + 1] == 0)
		{
			if (Inner(i, j + 1))
			{
				num++;
				Matrix[i][j + 1] = num;
				j++;
			}
			else
				break;
		}

		// �Ʒ� �������� ����
		while (Matrix[i + 1][j] == 0)
		{
			if (Inner(i + 1, j))
			{
				num++;
				Matrix[i + 1][j] = num;
				i++;
			}
			else
				break;
		}
		
		// ���� ����
		while (Matrix[i][j - 1] == 0)
		{
			if (Inner(i, j - 1))
			{
				num++;
				Matrix[i][j - 1] = num;
				j--;
			}
			else
				break;
		}

		// ���� ����
		while (Matrix[i-1][j] == 0)
		{
			if (Inner(i - 1, j))
			{
				num++;
				Matrix[i - 1][j] = num;
				i--;
			}
			else
				break;
		}
	}
}

bool Inner(int col, int row)
{
	bool inner = false;

	if ((col >= 0 && col < N) && (row >= 0 && row < N))
	{
		inner = true;
	}

	return inner;
}