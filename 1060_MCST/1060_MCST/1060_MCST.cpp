#include <iostream>

using namespace std;

const int MAX_N = 102;
int N;
int Graph[MAX_N][MAX_N];
int EdgeIdx;
int ANSWER = 0;

typedef struct _edge{
	int src;
	int dest;
	int weight;
}EDGE;
// Vertex, Edge, Weight 정보가 각각 들어가므로 배열 크기 고려할 것.
EDGE MCSTEdge[MAX_N*MAX_N];

typedef struct _subsets{
	int parent;
	int rank;
}SUBSETS;

void MySolve();
void KruscalMST();
void SelectionSort(EDGE Arr[], int ArrSize);
void Swap(EDGE* a, EDGE* b);
int Find(SUBSETS Subsets[], int i);
void Union(SUBSETS Subsets[], int x, int y);
int main()
{
	int test_case;
	//freopen("sample_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	//for (test_case = 1; test_case <= 3; test_case++)
	{
		// input
		cin >> N;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				cin >> Graph[i][j];
			}
		}

		// write algorithm
		MySolve();

		// output
		cout << ANSWER << endl;
	}
	return 0;
}

void MySolve()
{
	// 전역변수 초기화
	EdgeIdx = 0;
	ANSWER = 0;

	for (int i = 1; i <= N; i++)
	{
		for (int j = i+1; j <= N; j++)
		{
			if (Graph[i][j] != 0)
			{
				MCSTEdge[EdgeIdx].src = i;
				MCSTEdge[EdgeIdx].dest = j;
				MCSTEdge[EdgeIdx].weight = Graph[i][j];
				EdgeIdx++;
			}
		}
	}
	
	KruscalMST();
}

void KruscalMST()
{
	EDGE result[MAX_N] = { { 0, 0, 0 }, };
	int e = 0;
	int i = 0;

	// 1. increasing order
	SelectionSort(MCSTEdge, EdgeIdx);

	// 
#if 0
	SUBSETS* Subsets = new SUBSETS[N * sizeof(SUBSETS)];
	for (int v = 0; v < N; ++v)
	{
		Subsets[v].parent = v;
		Subsets[v].rank = 0;
	}
#endif
	SUBSETS Subsets[MAX_N] = { { 0, 0 }, };
	for (int v = 1; v <= N; ++v)
	{
		Subsets[v].parent = v;
		Subsets[v].rank = 0;
	}

	while (e < N - 1)
	{
		// 2. Pick the smallest edge.
		EDGE NextEdge = MCSTEdge[i++];

		int x = Find(Subsets, NextEdge.src);
		int y = Find(Subsets, NextEdge.dest);

		if (x != y)
		{
			result[e++] = NextEdge;
			Union(Subsets, x, y);
		}
		else
		{
		}
	}

	for (int i = 0; i < e; i++)
	{
		ANSWER += result[i].weight;
	}

	//delete[] Subsets;
}

void SelectionSort(EDGE Arr[], int ArrSize)
{
	int i, j, min_idx;
	for (i = 0; i < ArrSize - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < ArrSize; j++)
		{
			if (Arr[j].weight < Arr[min_idx].weight)
			{
				min_idx = j;
			}
		}

		// swap
		Swap(&Arr[min_idx], &Arr[i]);
	}
}

void Swap(EDGE* a, EDGE* b)
{
	EDGE temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int Find(SUBSETS Subsets[], int i)
{
	if (Subsets[i].parent != i)
	{
		Subsets[i].parent = Find(Subsets, Subsets[i].parent);
	}

	return Subsets[i].parent;
}

void Union(SUBSETS Subsets[], int x, int y)
{
	int xRoot = Find(Subsets, x);
	int yRoot = Find(Subsets, y);

	if (Subsets[xRoot].rank < Subsets[yRoot].rank)
		Subsets[xRoot].parent = yRoot;
	else if (Subsets[xRoot].rank > Subsets[yRoot].rank)
		Subsets[yRoot].parent = xRoot;
	else
	{
		Subsets[yRoot].parent = xRoot;
		Subsets[xRoot].rank++;
	}
}