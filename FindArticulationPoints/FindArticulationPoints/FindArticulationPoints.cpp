
#include <iostream>

using namespace std;

#define min(a, b)	(((a) < (b)) ? (a) : (b))

const int MAX_N = 102;
int N, M;
int Graph[MAX_N][MAX_N];
int Visited[MAX_N];
int DFSNum;

typedef struct _vertex{
	//int Vertex;
	int DFN;
	int Low;
}VERTEX;
VERTEX Vertex[MAX_N * MAX_N];

void MySolve();
void FindAP(int V, int Parent);
int main()
{
	int test_case;
	//freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	//for (test_case = 1; test_case <= 3; test_case++)
	{
		// input
		cin >> N >> M;
		for (int i = 0; i < M; i++)
		{
			int v1, v2;
			cin >> v1 >> v2;

			Graph[v1][v2] = Graph[v2][v1] = 1;
		}

		// write algorithm
		MySolve();
	}
	return 0;
}

void MySolve()
{
	// test_case를 위해 초기화 [
	DFSNum = -1;
	for (int i = 0; i < N; i++)
	{
		Visited[i] = 0;
	}
	// ]

	for (int i = 0; i < N; i++)
	{
		Vertex[i].DFN = -1;
		Vertex[i].Low = -1;
		//Vertex[i].Vertex = -1;
	}

	// 임의이 정점에서 시작하기 위해 모든 Vertex에게 가능성을 부여함.
	for (int v = 0; v < N; v++)
	{
		// DFS를 시작하려는 임의의 정점에서 DFS Number가 정의 되지 않은 경우.
		// 즉, 임의의 정점에서 아직 DFS 순회를 하지 않은 경우.
		if (Vertex[v].DFN == -1)
		{
			FindAP(v, -1);
		}
	}
}

void FindAP(int V, int Parent)
{
	int children = 0;

	// visit Vertex
	Visited[V] = 1;

	Vertex[V].DFN = ++DFSNum;
	Vertex[V].Low = Vertex[V].DFN;

	// 인접행렬에 있는 Vertex를 기반으로 탐색.
	for (int i = 0; i < N; i++)
	{
		if (Graph[V][i])
		{
			if (!Visited[i])
			{
				children++;

				FindAP(i, V);
				
				// Backtrak
				//Vertex[V].Low = Vertex[i].Low;
				Vertex[V].Low = min(Vertex[V].Low, Vertex[i].Low);

				// Find Articulation Point
				// V is Root of DFS Tree and if V has two or more children.
				if (Parent == -1 && children > 1)
				{
					cout << "Root is AP = " << V << endl;
				}
				// If V is not Root
				if (Parent != -1)
				{
					if (Vertex[i].Low >= Vertex[V].DFN)
					{
						cout << "Find AP = " << V << endl;
					}
				}
			}
			else if (Parent != i)
			{
				// detect cycle or it is back edge.
				//Vertex[V].Low = Vertex[i].Low;
				Vertex[V].Low = min(Vertex[V].Low, Vertex[i].DFN);
			}
		}
	}
}