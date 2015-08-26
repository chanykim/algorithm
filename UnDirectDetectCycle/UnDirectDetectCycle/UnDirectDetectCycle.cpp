/*
Detect Cycle in Undirected Graph Algorithm
1. when vertex is visited, visit array set true.
2. do DFS traversal.
3. when vertex v is visited to adjacent vertex u, set parent vertex[u] = v.
4. while DFS traversal doing,
if adjacent vertex u is already visited and u is not parent of v, then it is cycle.
else it is not cycle.
*/
/*
5 5
1 0
0 2
2 1
0 3
3 4



8 10
1 3 30
1 4 7
2 4 27
3 4 12
3 6 28
3 7 8
4 7 15
4 8 23
5 8 20
2 5 20
*/
#include <iostream>

using namespace std;

const int MAX_N = 50;
int V, E;
int Graph[MAX_N][MAX_N];
int Visited[MAX_N * MAX_N];

void MySolve();
bool UndirectedCycle(int V, int Parent);
int main()
{
	// input
	cin >> V >> E;
	for (int i = 0; i < E; i++)
	{
		int v1, v2;
		cin >> v1 >> v2;

		Graph[v1][v2] = Graph[v2][v1] = 1;
	}

	// write algorithm
	MySolve();

	return 0;
}

void MySolve()
{
	int *visited = new int[V];
	for (int i = 0; i < V; i++)
	{
		visited[i] = 0;
	}

	// determine to detect cycle
	for (int u = 0; u < V; u++)
	{
		if (UndirectedCycle(u, -1))
		{
			// 
		}
		
	}

	delete[] visited;
}

bool UndirectedCycle(int Vertex, int Parent)
{

	// Mark current vertex as visited
	Visited[Vertex] = 1;

	// search adjacent vertex u in adjacent matrix.
	for (int i = 0; i < V; i++)
	{
		if (Graph[Vertex][i])
		{
			// find adjacent vertex u.
			if (!Visited[i])
			{
				// recursive call & save Parent Vertex
				if (UndirectedCycle(i, Vertex))
					return true;
			}
			// adjacent vertex u is already visited and u is not parent of v
			else if (Visited[Vertex] && (Vertex != Parent))
			{
				// cycle graph
				return true;
			}
		}			
	}

	return false;
}