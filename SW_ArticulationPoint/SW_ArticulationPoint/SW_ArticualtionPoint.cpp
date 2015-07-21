
/*
입력 예1
3 2
1 2
2 3

출력 예1
2

입력 예
14 15
1 2
1 3
2 4
3 4
4 5
4 9
5 6
6 7
7 8
7 11
7 14
9 10
11 12
12 13
13 14

출력 예
4 5 6 7 9

입력 예
7 7
1 2
1 3
2 4
3 4
4 5
4 6
6 7
출력 예
4 6
*/

#include <iostream>

using namespace std;

const int MAX_N = 50;
int V;
int E;
int Graph[MAX_N][MAX_N];

int Discover[MAX_N];
int Low[MAX_N];			// 하위노드에서 가장 작은 값을 저장.
int Visited[MAX_N] = { 0, };
int Parent[MAX_N];
int AP[MAX_N];

void MySolve();
//void APUtil(int u, int visited[], int discover[], int low[], int parent[], int ap[]);
void APUtil(int u);

#define min(a, b)	((a < b) ? a : b)
#define NIL			-1
int main()
{
	// 입력
	int a, b;
	cin >> V >> E;
	for (int i = 0; i < E; i++)
	{
		cin >> a >> b;
		Graph[a][b] = Graph[b][a] = 1;
	}

	// 알고리즘
	MySolve();

	// 출력

	return 0;
}

void MySolve()
{
	// Initialize parent and visited, and ap(articulation point) arrays     
	for (int i = 0; i < V; i++)
	{
		Parent[i] = NIL;
		Visited[i] = 0;
		AP[i] = 0;
	}

	// 깊이우선탐색을 하면서 Vertex에 번호를 붙인다.
	for (int i = 1; i <= V; i++)
	{
		if (Visited[i] == 0)
		{
			//APUtil(i, Visited, Discover, Low, Parent, AP);
			APUtil(i);
		}
	}

	for (int i = 0; i < V; i++)
	{
		if (AP[i] == true)
		{
			cout << i << endl;
		}
	}
}
void APUtil(int u)
{
	static int time = 0;
	int children = 0;

	// 현재 노드를 방문
	Visited[u] = 1;

	// DFS로 그래프를 탐색하면서 탐색 순서 및 Low값을 저장.
	Discover[u] = Low[u] = ++time;

	for (int i = 1; i <= V; i++)
	{
		int v = i;		// v is current adjacent of u

		if (Graph[u][v])
		{			
			if (!Visited[v])
			{
				children++;
				Parent[v] = u;
				//APUtil(v, Visited, Discover, Low, Parent, AP);
				APUtil(v);

				Low[u] = min(Low[u], Low[v]);

				if (Parent[u] == NIL && children > 1)
				{
					AP[u] = true;
				}

				if (Parent[u] != NIL && Low[v] >= Discover[u])
				{
					AP[u] = true;
				}
			}
			// Update low value of u for parent function calls.
			// 노드의 바로 이전 부모가 아닌 상위 부모일 경우 상위부모의 값으로 저장.
			else if (v != Parent[u])
			{
				Low[u] = min(Low[u], Discover[v]);
			}
		}		
	}
}
#if 0
void APUtil(int u, int visited[], int discover[], int low[], int parent[], int ap[])
{
	static int time = 0;
	int children = 0;

	// 현재 노드를 방문
	visited[u] = 1;

	// 
	discover[u] = low[u] = ++time;

	for (int i = 1; i <= V; i++)
	{
		int v = i;		// v is current adjacent of u

		if (Graph[u][i] && !visited[i])
		{			
			children++;
			parent[v] = u;
			APUtil(v, visited, discover, low, parent, ap);

			low[u] = min(low[u], low[v]);

			if(parent[u] == 0 && children > 1)
			{
				ap[u] = true;
			}

			if (parent[u] != 0 && low[v] >= low[u])
			{
				ap[u] = true;
			}
		}
		else if (v != parent[u])
		{
			low[u] = min(low[u], low[v]);
		}
	}
}
#endif
