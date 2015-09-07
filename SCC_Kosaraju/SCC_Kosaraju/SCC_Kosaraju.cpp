
#include <iostream>

using namespace std;

const int MAX_N = 102;
int V, E;
int Graph[MAX_N][MAX_N];
int RevGraph[MAX_N][MAX_N];
int sp;
int NumSCC;

void MySolve();
void Kosaraju(int visited[]);
int DFS(int vertex, int visited[], int stack[]);
void CreateRevGraph();
int RevDFS(int vertex, int visited[]);
int main()
{
	int tc;
	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	for (tc = 1; tc <= 3; tc++)
	{
		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < V; j++)
			{
				Graph[i][j] = 0;
			}
		}
		// input
		cin >> V >> E;
		for (int i = 0; i < E; i++)
		{
			int v1, v2;
			cin >> v1 >> v2;

			Graph[v1][v2] = 1;
		}

		// write algorithm
		MySolve();

		// output
		cout << "Num Of SCC = " << NumSCC << endl;
	}
	return 0;
}

void MySolve()
{
	sp = -1;
	NumSCC = 0;

	// write to Kosaraju algorithm.
	int visited[MAX_N];
	for (int i = 0; i < V; i++)
	{
		visited[i] = 0;
	}	
	
	Kosaraju(visited);
}

void Kosaraju(int visited[])
{
	// 1. 스택 생성, 임의의 정점에서부터 DFS 순회
	int stack[MAX_N];
	for (int i = 0; i < V; i++)
	{
		stack[i] = -1;
	}

	for (int i = 0; i < V; i++)
	{
		if (visited[i] == 0)
		{
			// 2 ~ 5. DFS Traversal
			if (DFS(i, visited, stack))
			{

			}
			else
			{
				stack[++sp] = i;
			}
		}
	}

	// 6. Create Transpose Vertex
	CreateRevGraph();

	int RevVisited[MAX_N];
	for (int i = 0; i < V; i++)
	{
		RevVisited[i] = 0;
	}

	// 8. Stack이 empty할 때까지 반복.
	while (sp != -1)
	{
		// 7. 
		int v = stack[sp--];

		if (RevVisited[v] == 0)
		{
			if (RevDFS(v, RevVisited))
			{
			}
			else
			{
				cout << v;
				cout << endl;

				// count SCC Group
				NumSCC++;
			}
		}
	}
}

int DFS(int vertex, int visited[], int stack[])
{
	visited[vertex] = 1;

	for (int u = 0; u < V; u++)
	{
		if (Graph[vertex][u])
		{
			if (visited[u] == 0)
			{
				if (DFS(u, visited, stack))
					return 1;

				// 2. do backtrack...
				// push visited Vertex to Stack
				stack[++sp] = u;
			}
		}
	}

	return 0;
}

int RevDFS(int vertex, int visited[])
{
	visited[vertex] = 1;

	for (int u = 0; u < V; u++)
	{
		if (RevGraph[vertex][u])
		{
			if (visited[u] == 0)
			{
				if (RevDFS(u, visited))
					return 1;

				cout << u << " ";
			}
		}
	}

	return 0;
}
void CreateRevGraph()
{
	int v1, v2;

	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			RevGraph[i][j] = 0;
		}
	}

	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			if (Graph[i][j])
			{
				v1 = i;
				v2 = j;
				RevGraph[v2][v1] = 1;
			}
		}
	}
}