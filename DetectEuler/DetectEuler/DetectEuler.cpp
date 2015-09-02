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
		// test case�� ���� �������� �ʱ�ȭ
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

			// ���� ���
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
	// ���Ϸ� �׷������� Ȯ���� �ϱ� ���� �˰���
	//
	
	// 1. ��� �������� ���� ����Ǿ� �ִ��� Ȯ��
	if (isConnected() == 0)
	{
		cout << "This graph is not connected!" << endl;
		return;
	}

	// 2. Eulerian Path/Circuit ���� �ƴϸ� Eulerian Graph�� �ƴ��� degree�� Ȯ��.
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

// �־��� ��� �������� ���� ����Ǿ� �ִ��� Ȯ��
// 1. ��� �� �������κ��� �����Ͽ� ��� ������ �湮 �������� Ȯ��.
// 2. DFS �Ǵ� BFS�� ���Ͽ� �������� ��ȸ
// 3. ���̻� �׷����� ��ȸ�� �� ���� ��, unvisited ������ �ִ��� Ȯ��.
// 4. unvisited ������ ���� ��� ��� �������� ����Ǿ� �ִ� ������ �Ǵ�.
int isConnected()
{
	int visited[MAX_N];

	// ��� ������ unvisited�� ǥ��
	for ( int i = 0; i < V; i++)
	{
		visited[i] = 0;
	}

	// ������ �� ������������ ��ȸ
	for (int u = 0; u < V; u++)
	{
		if (visited[u] == 0)
		{
			// �׷��� ��ȸ
			DFS(u, visited);
		}
	}

	// ��� �������� �湮�ߴ��� Ȯ��
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

	// ������Ŀ� �ִ� ������ ���� degree�� ����� �� �ִ�.
	for (int v = 0; v < V; v++)
	{
		// �� ������ �ִ� degree ���� Ȯ��(in-degree, out-degree)
		int degree = 0;

		for (int u = 0; u < V; u++)
		{
			if (Graph[v][u] == 1)
			{
				degree = degree + 1;
			}
		}

		// degree�� ������ Ȧ������ Ȯ��
		if (degree % 2 == 1)
		{
			odd = odd + 1;
		}
	}

	// degree�� Ȧ���� ������ ������ ���� ���Ϸ� �׷��� ������ ����.
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