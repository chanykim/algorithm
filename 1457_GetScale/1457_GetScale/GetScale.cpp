
/*
입력
5 7 3
0 2 4 4
1 1 2 5
4 0 6 2

출력
3
1 7 13
*/
#include <iostream>
//#include <algorithm>

using namespace std;

// 전역변수
int M;
int N;
int K;
int **ppRECT;
int Matrix[100][100] = {0,};
int setValue = 2;

int size[10] = {0, };		// 사각형 크기에 대해 저장공간.
// 현재 지점과 연결된 4곳 상하좌우로 이동 양을 저장하는 배열.
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

// 주어진 좌표에 대한 사각형
void getRect(int x1, int y1, int x2, int y2);
// 배열 범위를 벗어나지 않도록 설정
bool Safe(int col, int row);
// 값을 sort 하기 위해
int compare(void* context, const void* a, const void* b);

// 깊이우선탐색 방법
void dfs(int a, int b, int nFlag);

void MySolve();


int main()
{
	// 입력
	cin >> M >> N >> K;

	ppRECT = new int*[N];
	for (int arr = 0; arr < M; arr++)		// 행
	{
		ppRECT[arr] = new int[N];			// 열
	}
	
	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cin >> ppRECT[i][j];
		}
	}
	
	// 알고리즘
	MySolve();

	// 출력
	int cnt = setValue - 2;
	cout << cnt << endl;
	for (int i = 0; i <= cnt; i++)
	{
		if (i < cnt)
		{
			cout << size[i] << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}

void MySolve()
{	
	// MxN 배열 영역을 1로 초기화
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Matrix[i][j] = 1;
		}
	}

	for (int col = 0; col < K; col++)
	{
		getRect(ppRECT[col][0], ppRECT[col][1], ppRECT[col][2], ppRECT[col][3]);
	}

	// 주어진 좌표의 사각형이 아닌 부분 (사각형 영역 = 2, 사각형이 아닌 부분 = 1)
	for (int x = 0; x < M; x++)
	{
		for (int y = 0; y < N; y++)
		{
			if (Matrix[x][y] == 1)
			{
				setValue++;
				// 깊이우선탐색
				dfs(x, y, setValue);
			}
		}
	}
	
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Matrix[i][j] > 2)
			{
				size[Matrix[i][j] - 3]++;
			}
		}
	}

	// 올림차순으로 정렬
	//sort(size, size + (setValue-2));
	qsort_s(size, setValue - 2, sizeof(int), compare, NULL);
}

void dfs(int a, int b, int nFlag)
{
	Matrix[a][b] = nFlag;

	// 상하좌우에 사각형 영역이 아닌 부분(=1)이 있는지 확인
	if (Safe(a+1, b) && Matrix[a+1][b] == 1)
	{
		dfs(a + 1, b, nFlag);
	}
	if (Safe(a - 1, b) && Matrix[a - 1][b] == 1)
	{
		dfs(a - 1, b, nFlag);
	}
	if (Safe(a, b + 1) && Matrix[a][b + 1] == 1)
	{
		dfs(a, b + 1, nFlag);
	}
	if (Safe(a, b - 1) && Matrix[a][b - 1] == 1)
	{
		dfs(a, b - 1, nFlag);
	}
}

void getRect(int x1, int y1, int x2, int y2)
{
	// 문제에서는 x,y축 좌표로 표현되었으므로 배열 순서와는 다르다.
	// 따라서 x,y축 형태로 표현될 수 있도록 배열의 col, row를 변경해야 하는데
	// col은 y축을 표현되도록 row은 x축으로 표현되도록 변경해야 한다.
	// array[col][row]  ----------> x축,y축 변환 array[row][col]
	for (int i = y1; i < y2; i++)
	{
		for (int j = x1; j < x2; j++)
		{
			Matrix[i][j] = 2;			// 주어진 좌표의 직각사각형 내의 값을 1로 설정.
		}
	}
}

 bool Safe(int col, int row)
{
	bool innerMatrix = false;

	if ( ((col >= 0) && (col <= M)) ||
		((row >= 0) && (row <= 0)) )
	{
		innerMatrix = true;
	}
	
	return innerMatrix;
}

 int compare(void* context, const void* a, const void* b)
 {
	 int arg1 = *(const int*)a;
	 int arg2 = *(const int*)b;

	 if (arg1 > arg2) return 1;	 
	 else if (arg1 < arg2) return -1;
	 else
		 return 0;
 }