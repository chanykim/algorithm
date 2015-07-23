/*
�Է� ��
5 5
0 2 2 5 9
2 0 3 4 8
2 3 0 7 6
5 4 7 0 5
9 8 6 5 0

��� ��
8
1 3 5
*/
#include <iostream>

using namespace std;

const int MAX_N = 100;
int N;
int M;
int Matrix[MAX_N][MAX_N];
int ANSWER = -1;

void MySolve();
void FloydWashall();
int FindPath(int Start, int End);
void MySolve2();
void Dijkstra(int Start, int End);
void Dijkstra_FindPath(int Start, int End, int parents[]);
int main()
{
    // �Է�
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> Matrix[i][j];
		}
	}

    // �˰���
	MySolve();
	//MySolve2();

    // ���
	//cout << ANSWER << endl;

	return 0;
}

void MySolve()
{
	for(int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cout << Matrix[i][j];
		}
		cout << endl;
	}
	cout << endl;

    // Floyd-Washall �˰���
	FloydWashall();
	FindPath(1, M);

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cout << Matrix[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void FloydWashall()
{
	int i, j;           // ī����
	int k;              // �߰� ���� ī����
	int through_k;      // ���� K�� �����ϴ� �Ÿ�

	for (k = 1; k <= N; k++)
	{
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= N; j++)
			{
                // K �߰������� �ξ i -> k -> j �� �̵����� ���� �Ÿ� ���� ���ϰ�,
                // K�� ������ ���� i->j�� ���� �̵����� ���� ���ؼ� ���� ������ ��������� Update��.
				through_k = Matrix[i][k] + Matrix[k][j];
				if (through_k < Matrix[i][j])
				{
					Matrix[i][j] = through_k;
				}
			}
		}
	}
}

// �������� �������� �޾Ƽ� �ִܰŸ� ��� �� ������ ��� ǥ��
int FindPath(int Start, int End)
{
	int ShortestPath = -1;
    
    // �ִܰŸ� ���
    // ������Ŀ� �Ÿ��� Updat�Ǿ� �����Ƿ� ������� ���� Read
	ShortestPath = Matrix[Start][End];
	ANSWER = ShortestPath;

	return 1;
}

void MySolve2()
{
    // Dijkstra �˰���
	Dijkstra(1, M);
}
int Parent[MAX_N];
void Dijkstra(int Start, int End)
{
	bool intree[MAX_N];
	int distance[MAX_N];
	int v;          
	int w;          // �̿�����
	int weight;
	int dist;

	for (int i = 1; i <= N; i++)
	{
		intree[i] = false;
		distance[i] = INT_MAX;
		Parent[i] = -1;
	}

	distance[Start] = 0;
	v = Start;

	while (intree[v] == false)
	{
		intree[v] = true;

		for (int i = 1; i <= N; i++)
		{
			if (Matrix[v][i])
			{
				w = i;
				weight = Matrix[v][i];

				// �������� �Ÿ� ���Ͽ� �������� �ּҰ����� �Ÿ��� Updaat�ϰ�,
				// ������ �θ� ������ ���踦 Update ��.
				if (distance[w] > distance[v] + weight)
				{
					distance[w] = distance[v] + weight;
					Parent[w] = v;
				}
			}            
		}

        // ���� A�� ���� B�� ���������� ����Ǿ� ���� ���� ���
        // �Ÿ��� ���Ѵ��̴�.
		v = 1;
		dist = INT_MAX;

        // 
		for (int i = 1; i <= N; i++)
		{
			if ((intree[i] == false) && (dist > distance[i]))
			{
				dist = distance[i];
				v = i;
			}
		}

	}

    // �������� �������� �ִܰŸ�
	ANSWER = distance[End];
	cout << ANSWER << endl;
    // ������ ���
	Dijkstra_FindPath(Start, End, Parent);
	cout << endl;
}

void Dijkstra_FindPath(int Start, int End, int parents[])
{
	if ((Start == End) || (Start == -1))
	{
		cout << Start;
	}
	else
	{
        // ����Լ��� Parent[] �迭�� ��� �ִ� ���� �����Ͽ�
        // Stack�� �ִ´�. 
        //����, End�������� �����ؼ� Stack�� �����ϸ�, Start���� ���ʴ�� ���.
		Dijkstra_FindPath(Start, parents[End], parents);
		cout << End;
	}
}