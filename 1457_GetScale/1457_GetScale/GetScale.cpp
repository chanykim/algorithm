
/*
�Է�
5 7 3
0 2 4 4
1 1 2 5
4 0 6 2

���
3
1 7 13
*/
#include <iostream>
//#include <algorithm>

using namespace std;

// ��������
int M;
int N;
int K;
int **ppRECT;
int Matrix[100][100] = {0,};
int setValue = 2;

int size[10] = {0, };		// �簢�� ũ�⿡ ���� �������.
// ���� ������ ����� 4�� �����¿�� �̵� ���� �����ϴ� �迭.
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

// �־��� ��ǥ�� ���� �簢��
void getRect(int x1, int y1, int x2, int y2);
// �迭 ������ ����� �ʵ��� ����
bool Safe(int col, int row);
// ���� sort �ϱ� ����
int compare(void* context, const void* a, const void* b);

// ���̿켱Ž�� ���
void dfs(int a, int b, int nFlag);

void MySolve();


int main()
{
	// �Է�
	cin >> M >> N >> K;

	ppRECT = new int*[N];
	for (int arr = 0; arr < M; arr++)		// ��
	{
		ppRECT[arr] = new int[N];			// ��
	}
	
	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cin >> ppRECT[i][j];
		}
	}
	
	// �˰���
	MySolve();

	// ���
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
	// MxN �迭 ������ 1�� �ʱ�ȭ
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

	// �־��� ��ǥ�� �簢���� �ƴ� �κ� (�簢�� ���� = 2, �簢���� �ƴ� �κ� = 1)
	for (int x = 0; x < M; x++)
	{
		for (int y = 0; y < N; y++)
		{
			if (Matrix[x][y] == 1)
			{
				setValue++;
				// ���̿켱Ž��
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

	// �ø��������� ����
	//sort(size, size + (setValue-2));
	qsort_s(size, setValue - 2, sizeof(int), compare, NULL);
}

void dfs(int a, int b, int nFlag)
{
	Matrix[a][b] = nFlag;

	// �����¿쿡 �簢�� ������ �ƴ� �κ�(=1)�� �ִ��� Ȯ��
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
	// ���������� x,y�� ��ǥ�� ǥ���Ǿ����Ƿ� �迭 �����ʹ� �ٸ���.
	// ���� x,y�� ���·� ǥ���� �� �ֵ��� �迭�� col, row�� �����ؾ� �ϴµ�
	// col�� y���� ǥ���ǵ��� row�� x������ ǥ���ǵ��� �����ؾ� �Ѵ�.
	// array[col][row]  ----------> x��,y�� ��ȯ array[row][col]
	for (int i = y1; i < y2; i++)
	{
		for (int j = x1; j < x2; j++)
		{
			Matrix[i][j] = 2;			// �־��� ��ǥ�� �����簢�� ���� ���� 1�� ����.
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