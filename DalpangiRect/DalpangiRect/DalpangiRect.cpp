
#include <iostream>

using namespace std;

int N;		// 2차원 배열의 크기
// 검색순서 (오른쪽 -> 아래 -> 왼쪽 -> 위쪽)
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

const int MAX_N = 100;
int Matrix[MAX_N][MAX_N];

void MySolve();
bool Inner(int col, int row);
int main()
{
	// 입력
	cin >> N;

	// 알고리즘
	MySolve();

	// 출력
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

	// 주어진 크기의 배열을 모두 0으로 채움
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
		// row열이 증가 즉, left 방향으로 증가하면서 값이 0인지 확인
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

		// 아래 방향으로 증가
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
		
		// 왼쪽 방향
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

		// 위쪽 방향
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