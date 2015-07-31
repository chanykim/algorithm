
#include <iostream>

using namespace std;

int Board[102][102];
int Answer[20002];
int N;
int AnswerLength;

// 코드 추가 [
int dCol[8] = { 1, 1, 1, 1, 0, -1, -1, -1 };
int dRow[8] = { 0, 1, 0, -1, -1, -1, 0, 1 };

int Seq;

int Solve(int *Answer);
void DFS(int C, int R, int V);
bool InnerArray(int C, int R);
// ]
int main()
{
	int test_case;

	freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);
	int T = 2;
	for (test_case = 1; test_case <= T; test_case++)
	{
		// 입력
		cin >> N;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				cin >> Board[i][j];
			}
		}

		cout << "#" << test_case << " ";
		AnswerLength = Solve(Answer);
		for (int i = 0; i < AnswerLength; i++)
			cout << Answer[i * 2] << " " << Answer[i * 2 + 1] << " ";
		cout << endl;
	}
}

int Solve(int *Answer)
{
	// 전역변수 값을 초기화해야 함. - 중요
	Seq = 0;

	// 코드 추가 [
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (Board[i][j] == 0)
			{
				Board[i][j] = 2;
			}
		}
	}
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (Board[i][j] == 2)
			{
				DFS(i, j, 3);
			}
		}
	}

	AnswerLength = Seq;

	return AnswerLength/2;
// ]
}
// 코드 추가 [
void DFS(int C, int R, int V)
{
	Board[C][R] = V;

	Answer[Seq] = C;
	Answer[Seq + 1] = R;
	Seq += 2;

	for (int i = 0; i < 8; i++)
	{
		if (InnerArray(C + dCol[i], R + dRow[i]) && (Board[C + dCol[i]][R + dRow[i]] == 2))
		{
			DFS(C + dCol[i], R + dRow[i], 3);
			Seq -= 2;
		}
	}
}

bool InnerArray(int C, int R)
{
	bool inner = false;
	if ((C >= 0 && C < N) && (R >= 0 && R < N))
	{
		inner = true;
	}

	return inner;
}
// ]