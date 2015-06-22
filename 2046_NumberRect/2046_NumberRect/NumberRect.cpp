
#include <iostream>

using namespace std;

int N;
int M;
int Rect[100][100];

void MySolve();
int main()
{
	// 입력
	cin >> N >> M;

	// 알고리즘
	MySolve();

	// 출력
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (j < N)
			{
				cout << Rect[i][j] << " ";
			}		
		}
		if (j == N)
		{
			cout << endl;
		}
	}
	return 0;
}

void MySolve()
{
	// 입력된 M에 의해 Type 결정.
	if (M == 1)
	{
		// 입력된 N에 의해서 MxM 배열 생성
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				Rect[i][j] = i + 1;
			}
		}
	}
	else if (M == 2)
	{
		// 입력된 N에 의해서 MxM 배열 생성
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (i % 2 == 0)
				{
					Rect[i][j] = j + 1;
				}
				else
				{
					Rect[i][j] = N - j;
				}				
			}
		}
	}
	else if (M == 3)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				Rect[i][j] = (i + 1) * (j + 1);
			}
		}
	}
}