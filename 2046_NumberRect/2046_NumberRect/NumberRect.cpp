
#include <iostream>

using namespace std;

int N;
int M;
int Rect[100][100];

void MySolve();
int main()
{
	// �Է�
	cin >> N >> M;

	// �˰���
	MySolve();

	// ���
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
	// �Էµ� M�� ���� Type ����.
	if (M == 1)
	{
		// �Էµ� N�� ���ؼ� MxM �迭 ����
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
		// �Էµ� N�� ���ؼ� MxM �迭 ����
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