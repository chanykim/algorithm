
/*
�Է� ��
9 14
1 2 4
1 8 8
2 3 8
2 8 11
3 4 7
3 6 4
3 9 2
4 5 9
4 6 14
5 6 10
6 7 2
7 8 1
7 9 2
8 9 7

��� ��

�Է� �� 2
7 11
1 2 47
1 3 69
2 4 57
2 5 124
3 4 37
3 5 59
3 6 86
4 6 27
4 7 94
5 7 21
6 7 40

��� �� 2
149
*/
#include <iostream>

using namespace std;

const int MAX_N = 20;
int Graph[MAX_N][MAX_N];
int N, M, W;
int Visited[MAX_N];
int ANSWER = INT_MAX;

const int MAX_V = 100;
const int MAX_DEGREE = 50;
int parent[MAX_V];
struct EDGE{
	int v;			// neighboring vertex
	int weight;		// edge weight
};
struct GRAPH{
	EDGE edges[MAX_V + 1][MAX_DEGREE];	// ������ ���� ���� ����
	int degree[MAX_V + 1];				// �� ������ ��� ����
	int nVertices;						// �׷����� �ִ� ���� ��
	int nEdges;							// �׷����� �ִ� ���� ��
};
void Dijkstra(GRAPH* G, int start);
void Read_Graph(GRAPH* G, bool Directed);
void Insert_Edge(GRAPH* G, int x, int y, bool Directed, int w);

void MySolve();
void DFS(int V, int W);
void Dijkstra_Matrix(int start);
void Find_Path(int start, int end, int parents[]);
int main()
{
	// �Է�
#if 1
	cin >> N >> M;
	for (int i = 1; i <= M; i++)
	{
		int s, t, w;
		cin >> s >> t >> w;
		Graph[s][t] = Graph[t][s] = w;
	}
#endif
#if 0
	GRAPH G;
	Read_Graph(&G, false);
	Dijkstra(&G, 1);

#endif
	// �˰���
	MySolve();

	// ���
	cout << ANSWER << endl;

	return 0;
}

void MySolve()
{
	// ��üŽ����
#if 0
	for (int i = 1; i <= N; i++)
	{
		if (Visited[i] == 0)
			DFS(i, 0);
	}
#endif
	DFS(1, 0);

	// Dijkstra �˰���
	Dijkstra_Matrix(1);

	for (int i = 1; i <= N; i++)
	{
		Find_Path(1, i, parent);
	}
	cout << endl;
}

void DFS(int V, int W)
{
	if (V == N)
	{
		// �������� ������ 
		if (ANSWER > W)
			ANSWER = W;
		
		return;
	}

	for (int i = 1; i <= N; i++)
	{
		if (Graph[V][i] && !Visited[i])
		{
			Visited[V] = 1;

			DFS(i, W + Graph[V][i]);

			Visited[i] = 0;
		}
	}
}
#if 1
void Initialize_Graph(GRAPH* G)
{
	G->nVertices = 0;
	G->nEdges = 0;

	for (int i = 0; i < MAX_V; i++)
	{
		G->degree[i] = 0;
	}
}

void Read_Graph(GRAPH* G, bool Directed)
{
	// 
	Initialize_Graph(G);

	cin >> G->nVertices >> M;

	for (int i = 1; i <= M; i++)
	{
		int x, y, w;
		cin >> x >> y >> w;

		Insert_Edge(G, x, y, Directed, w);
	}
}

void Insert_Edge(GRAPH* G, int x, int y, bool Directed, int w)
{
	if (G->degree[x] > MAX_DEGREE)
		cout << "Warning: insertion exceeds degree bound" << endl;

	G->edges[x][G->degree[x]].v = y;
	G->edges[x][G->degree[x]].weight = w;
	G->degree[x]++;

	if (Directed == false)
		Insert_Edge(G, y, x, true, w);
	else
		G->nEdges++;
}

void Dijkstra(GRAPH* G, int start)
{
	bool intree[MAX_V];			// ������ Ʈ���� ����ִ��� ����
	int distance[MAX_V];		// ���������κ����� �Ÿ�
	int v;						// ���� ó���ؾ��� ����
	int w;						// ���� ���� �ĺ�
	int weight;					// edge ����ġ

	for (int i = 1; i <= G->nVertices; i++)
	{
		intree[i] = false;
		distance[i] = INT_MAX;		// �������� ���������� ����Ǿ� �������� ��� �Ÿ��� ���Ѵ�� ǥ��
		parent[i] = -1;
	}

	// Distance of source vertex from itself is always 0
	distance[start] = 0;
	v = start;

	while (intree[v] == false)
	{
		intree[v] = true;
		for (int i = 0; i < G->degree[v]; i++)
		{
			w = G->edges[v][i].v;
			weight = G->edges[v][i].weight;
			if (distance[w] > distance[v] + weight)
			{
				distance[w] = distance[v] + weight;
				parent[w] = v;
			}
		}

		v = 1;
		
	}
}

void Find_Path(int start, int end, int parents[])
{
	if ((start == end) || (end == -1))
	{
		cout << start << endl;
	}
	else
	{
		Find_Path(start, parents[end], parents);
		cout << end << endl;
	}
}
#if 1
void Dijkstra_Matrix(int start)
{
	bool intree[MAX_V];			// ������ Ʈ���� ����ִ��� ����
	int distance[MAX_V];		// ���������κ����� �Ÿ�
	int v;						// ���� ó���ؾ��� ����
	int w;						// ���� ���� �ĺ�
	int weight;					// edge ����ġ
	int dist;					// ���� �ִ� �Ÿ�

	for (int i = 1; i <= N; i++)
	{
		intree[i] = false;
		distance[i] = INT_MAX;		// �������� ���������� ����Ǿ� �������� ��� �Ÿ��� ���Ѵ�� ǥ��
		parent[i] = -1;
	}

	// Distance of source vertex from itself is always 0
	distance[start] = 0;
	v = start;

	while (intree[v] == false)
	{
		intree[v] = true;

		for (int i = 1; i <= N; i++)
		{
			if (Graph[v][i])
			{
				// �̿�����(Neighbor Vertex)�� ���� ������ ������ ��.
				w = i;
				weight = Graph[v][i];

				if (distance[w] > (distance[v] + weight))
				{
					distance[w] = distance[v] + weight;
					parent[w] = v;
				}
			}
		}

		// Dijstra �˰����� ���Ǹ� ����,
		// ��� ���� ������� �θ���� ������ �ְ�, �� �Ÿ��� ���Ѵ��̴�.
		v = 1;
		dist = INT_MAX;

		// 
		for (int j = 1; j <= N; j++)
		{
			if ((intree[j] == false) && (dist > distance[j]))
			{
				dist = distance[j];
				v = j;
			}
		}
	}
}
#endif
#endif