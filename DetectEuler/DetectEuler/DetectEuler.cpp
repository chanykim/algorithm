#include <iostream>

using namespace std;

enum {
	NOT_EULER_GRAPH = 0,
	EULER_PATH,
	EULER_CIRCUIT
};
const int MAX_N = 102;
int V, E;
int Graph[MAX_N][MAX_N];

void MySolve();
int isConnected();
void DFS(int v, int visited[]);
int EulerianGraphType();
int main()
{
	int tc;
	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	for (tc = 1; tc <= 3; tc++)
	{
		// test case를 위해 전역변수 초기화
		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < E; j++)
			{
				Graph[i][j] = 0;
			}
		}

		// input
		cin >> V >> E;
		for (int v = 0; v < E; v++)
		{
			int v1, v2;
			cin >> v1 >> v2;

			// 인접 행렬
			Graph[v1][v2] = Graph[v2][v1] = 1;
		}

		// write algotithm
		MySolve();
	}
	return 0;
}

void MySolve()
{
	// 
	// 오일러 그래프인지 확인을 하기 위한 알고리즘
	//
	
	// 1. 모든 정점들이 서로 연결되어 있는지 확인
	if (isConnected() == 0)
	{
		cout << "This graph is not connected!" << endl;
		return;
	}

	// 2. Eulerian Path/Circuit 인지 아니면 Eulerian Graph가 아닌지 degree로 확인.
	int result = -1;
	result = EulerianGraphType();

	if (result == NOT_EULER_GRAPH)
	{
		cout << "Graph is not Eulerian" << endl;
	}
	else if (result == EULER_PATH)
	{
		cout << "Graph is Eulerian Path" << endl;
	}
	else
	{
		cout << "Graph is Eulerian Circuit" << endl;
	}
}

// 주어진 모든 정점들이 서로 연결되어 있는지 확인
// 1. 어느 한 정점으로부터 시작하여 모든 정점이 방문 가능한지 확인.
// 2. DFS 또는 BFS를 통하여 정점들을 순회
// 3. 더이상 그래프를 순회할 수 없을 때, unvisited 정점이 있는지 확인.
// 4. unvisited 정점이 없는 경우 모든 정점들이 연결되어 있는 것으로 판단.
int isConnected()
{
	int visited[MAX_N];

	// 모든 정점을 unvisited로 표시
	for ( int i = 0; i < V; i++)
	{
		visited[i] = 0;
	}

	// 임의의 한 정점에서부터 순회
	for (int u = 0; u < V; u++)
	{
		if (visited[u] == 0)
		{
			// 그래프 순회
			DFS(u, visited);
		}
	}

	// 모든 정점들을 방문했는지 확인
	for (int i = 0; i < V; i++)
	{
		if (visited[i] == 0)
			return 0;
	}

	return 1;
}

void DFS(int v, int visited[])
{
	visited[v] = 1;

	for (int i = 0; i < V; i++)
	{
		if (Graph[v][i])
		{
			if (visited[i] == 0)
			{
				// recursive call
				DFS(i, visited);
			}
		}
	}
}

/* The function returns one of the following values
0 --> If grpah is not Eulerian
1 --> If graph has an Euler path (Semi-Eulerian)
2 --> If graph has an Euler Circuit (Eulerian)  */
int EulerianGraphType()
{
	int EulerType;
	int odd = 0;

	// 인접행렬에 있는 간선을 통해 degree를 계산할 수 있다.
	for (int v = 0; v < V; v++)
	{
		// 각 정점에 있는 degree 개수 확인(in-degree, out-degree)
		int degree = 0;

		for (int u = 0; u < V; u++)
		{
			if (Graph[v][u] == 1)
			{
				degree = degree + 1;
			}
		}

		// degree의 개수가 홀수인지 확인
		if (degree % 2 == 1)
		{
			odd = odd + 1;
		}
	}

	// degree가 홀수인 정점의 개수를 통해 오일러 그래프 종류를 결정.
	switch (odd)
	{
	case 0:
		 EulerType = EULER_CIRCUIT;
		break;

	case 2:
		EulerType = EULER_PATH;
		break;

	default:
		EulerType = NOT_EULER_GRAPH;
		break;
	}

	return EulerType;
}