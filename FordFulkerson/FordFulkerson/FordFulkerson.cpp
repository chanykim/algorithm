/*
입력 예1
10 6
0 1 16
0 2 13
1 2 10
1 3 12
2 1 4
2 4 14
3 2 9
3 5 20
4 3 7
4 5 4

출력 예1
23

입력 예2
7 6
0 1 7
0 3 6
1 2 3
1 4 6
2 5 4
3 4 9
4 5 8

출력 예2
11

*/
#include <iostream>

using namespace std;

#define min(a, b) (((a) < (b)) ? a : b)
const int MAX_N = 10;
int N, M;
int Matrix[MAX_N][MAX_N];
int ANSWER = -1;

void MySolve();
int FordFulkerson(int S, int T);
bool BFS(int rGraph[MAX_N][MAX_N], int S, int T, int parent[]);
int main()
{
	// 입력
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		int x, y, w;
		cin >> x >> y >> w;
		Matrix[x][y] = Matrix[y][x] = w;
	}

	// 알고리즘
	MySolve();

	// 출력
	cout << ANSWER << endl;

	return 0;
}

void MySolve()
{
	FordFulkerson(1, M);
}

int FordFulkerson(int S, int T)
{
	int u, v;

	// Create a residual graph and fill the residual graph with
	// given capacities in the original graph as residual capacities
	// in residual graph
	int rGraph[MAX_N][MAX_N];	// Residual graph where rGraph[i][j] indicates 
								// residual capacity of edge from i to j (if there
								// is an edge. If rGraph[i][j] is 0, then there is not)  
	for (u = 1; u <= M; u++)
	{
		for (v = 1; v <= M; v++)
		{
			rGraph[u][v] = Matrix[u][v];
		}
	}

	int parent[MAX_N];			// This array is filled by BFS and to store path

	int max_flow = 0;			// There is no flow initially

	while (BFS(rGraph, S, T, parent))
	{
		// Find minimum residual capacity of the edges along the
		// path filled by BFS. Or we can say find the maximum flow
		// through the path found.
		int path_flow = INT_MAX;
		for (v = T; v != S; v = parent[v])
		{
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}

		// update residual capacities of the edges and reverse edges
		// along the path
		for (v = T; v != S; v = parent[v])
		{
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

		// Add path flow to overall flow
		max_flow += path_flow;
	}

	ANSWER = max_flow;

	return max_flow;
}

#include <queue>
/* Returns true if there is a path from source 's' to sink 't' in
residual graph. Also fills parent[] to store the path */
bool BFS(int rGraph[MAX_N][MAX_N], int S, int T, int parent[])
{
	// Create a visited array and mark all vertices as not visited
	int visited[MAX_N];
	memset(visited, 0, sizeof(visited));

	// Create a queue, enqueue source vertex and mark source vertex
	// as visited
	queue<int> q;
	q.push(S);
	visited[S] = 1;
	parent[S] = -1;

	// Standard BFS Loop
	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		for (int v = 1; v <= M; v++)
		{
			if (visited[v] == 0 && rGraph[u][v])
			{
				q.push(v);
				parent[v] = u;
				visited[v] = 1;
			}
		}
	}

	// If we reached sink in BFS starting from source, then return
	// true, else false
	return (visited[T] == true);
}