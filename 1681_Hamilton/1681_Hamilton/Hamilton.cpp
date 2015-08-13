
/*
입력 예
5
0 14 4 10 20
14 0 7 8 7
4 5 0 7 16
11 7 9 0 2
18 7 17 4 0

출력 예
30

입력 예
12
0 79 44 27 22 48 18 65 79 93 25 49
77 0 13 95 42 17 55 34 28 4 26 87
8 66 0 65 78 3 0 0 38 0 0 37
0 91 33 0 60 95 60 78 46 81 54 12
46 49 1 97 0 70 64 86 26 0 63 64
16 0 0 74 97 0 97 90 52 27 33 69
34 33 33 19 16 65 0 0 29 63 66 35
12 37 0 87 4 9 38 0 87 0 44 42
69 0 32 8 19 19 17 43 0 2 63 49
0 53 0 78 84 8 9 38 78 0 32 41
73 70 81 72 19 91 63 76 91 10 0 75
14 0 22 0 69 93 35 86 0 43 77 0

출력 예
202
*/

#if 1
#include <iostream>

using namespace std;

const int MAX_N = 12;
int N;
int Graph[MAX_N][MAX_N];
int ANSWER = -1;
int ShortestPath = 0x7FFFFFFF;

void MySolve();
bool Hamilton(int Path[], int Pos, int Distance);
bool Promising(int V, int Path[], int Pos);
int main()
{
	int test_case;

	freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	for (test_case = 1; test_case <= 2; test_case++)
	{
		// 입력 
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> Graph[i][j];
			}
		}

		// 알고리즘 
		MySolve();

		// 출력 
		ANSWER = ShortestPath;
		cout << ANSWER << endl;
	}
	return 0;
}

void MySolve()
{
	// 중요 - Test Case를 위해 초기화
	ShortestPath = 0x7FFFFFFF;

	int *path = new int[N];
	for (int i = 0; i < N; i++)
	{
		path[i] = -1;
	}

	path[0] = 0;
	Hamilton(path, 1, 0);
}

bool Hamilton(int Path[], int Pos, int Distance)
{
	if (Pos >= N)
	{
		if (Graph[Path[Pos - 1]][Path[0]] != 0)
		{
			Distance += Graph[Path[Pos - 1]][Path[0]];
			if (ShortestPath > Distance)
				ShortestPath = Distance;

			return true;
		}
		else
		{
			return false;
		}
	}


	// 전체탐색을 하면서 현재 구해진 최소값보다 큰 값이 있을 경우
	// 더 이상 탐색할 필요가 없으므로 return.
	if (ShortestPath < Distance)
	{
		return false;
	}

	for (int v = 1; v < N; v++)
	{
		if (Promising(v, Path, Pos))
		{
			Path[Pos] = v;
			Distance += Graph[Path[Pos - 1]][Path[Pos]];

			Hamilton(Path, Pos + 1, Distance);

			Distance -= Graph[Path[Pos - 1]][Path[Pos]];
			Path[Pos] = -1;
		}
	}
}

bool Promising(int V, int Path[], int Pos)
{
	// check whether it can be Hamilton path.
	if (Graph[Path[Pos - 1]][V] == 0)
		return false;

	for (int i = 0; i < Pos; i++)
	{
		if (Path[i] == V)
			return false;
	}

	return true;
}
#endif