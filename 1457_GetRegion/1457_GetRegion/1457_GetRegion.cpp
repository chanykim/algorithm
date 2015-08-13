
#include <iostream>

using namespace std;

const int MAX_N = 102;
int M, N, K;
int Matrix[MAX_N][MAX_N];	// 2���� �迭
int RECT[MAX_N][MAX_N];		// �簢 ���� ����.
int Region[MAX_N];			// ������ ���� �� ũ��

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void MySolve();
void Backtrack(int X, int Y, int V);
void FillRect(int X1, int Y1, int X2, int Y2);
bool InnerArray(int R, int C);
void ascending_selection_sort(int Array[], int count);
void PrintResult();
int main()
{
	int test_case;
	freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	for (test_case = 1; test_case <= 2; test_case++)
	{
		// �Է�
		cin >> M >> N >> K;
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				Matrix[i][j] = 1;
			}
		}

		for (int i = 0; i < K; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				cin >> RECT[i][j];
			}
		}

		// wirte algorithm
		MySolve();

		// Output
		PrintResult();
	}

	return 0;
}

void MySolve()
{
	for (int i = 0; i < MAX_N; i++)
	{
		Region[i] = 0;
	}

	for (int i = 0; i < K; i++)
	{
		FillRect(RECT[i][0], RECT[i][1], RECT[i][2], RECT[i][3]);
	}

	int Num = 2;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Matrix[i][j] == 1)
			{
				Num += 1;
				Backtrack(i, j, Num);
			}
		}
	}

	// ���� ������ ũ�� ����.
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Matrix[i][j] > 2)
			{
				Region[Matrix[i][j] - 3]++;
			}
		}
	}

	// �������� ����
	int ArraySize = Num - 2;
	ascending_selection_sort(Region, ArraySize);
}

void FillRect(int X1, int Y1, int X2, int Y2)
{
	// ���������� x,y�� ��ǥ�� ǥ���Ǿ����Ƿ� �迭 �����ʹ� �ٸ���.
	// ���� x,y�� ���·� ǥ���� �� �ֵ��� �迭�� col, row�� �����ؾ� �ϴµ�
	// col�� y���� ǥ���ǵ��� row�� x������ ǥ���ǵ��� �����ؾ� �Ѵ�.
	// array[col][row]  ----------> x��,y�� ��ȯ array[row][col]

	for (int i = Y1; i < Y2; i++)
	{
		for (int j = X1; j < X2; j++)
		{
			if (Matrix[i][j] == 2)
				continue;
			Matrix[i][j] = 2;
		}
	}
}

void Backtrack(int X, int Y, int V)
{
	Matrix[X][Y] = V;

	for (int i = 0; i < 4; i++)
	{
		if (InnerArray(X + dx[i], X + dx[i]) &&
			(Matrix[X + dx[i]][Y + dy[i]] == 1))
		{
			Backtrack(X + dx[i], Y + dy[i], V);
		}
	}
}

bool InnerArray(int R, int C)
{
	if ((R >= 0 && R < N) && (C >= 0 && C < N))
	{
		return true;
	}

	return false;
}

void swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;	
}
void ascending_selection_sort(int Array[], int count)
{
	int min = 0;

	for (int i = 0; i < count; i++)
	{
		min = i;
		for (int j = i + 1; j < count; j++)
		{
			if (Array[j] < Array[min])
				min = j;

			if(Array[i] > Array[min])
			{
				swap(&Array[i], &Array[min]);
			}
		}
	}
}

void PrintResult()
{
	int i = 0;
	int ArraySize = 0;

	while (Region[i] != 0)
	{
		ArraySize++;
		i++;
	}

	cout << ArraySize << endl;
	for (int num = 0; num < ArraySize; num++)
	{
		cout << Region[num] << " ";
	}
	cout << endl;
}