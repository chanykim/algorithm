/*
입력 예
5 5
0 2 2 5 9
2 0 3 4 8
2 3 0 7 6
5 4 7 0 5
9 8 6 5 0

출력 예
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
    // 입력
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> Matrix[i][j];
		}
	}

    // 알고리즘
	MySolve();
	//MySolve2();

    // 출력
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

    // Floyd-Washall 알고리즘
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
	int i, j;           // 카운터
	int k;              // 중간 정점 카운터
	int through_k;      // 정점 K를 경유하는 거리

	for (k = 1; k <= N; k++)
	{
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= N; j++)
			{
                // K 중간지점을 두어서 i -> k -> j 로 이동했을 때의 거리 합을 구하고,
                // K를 경유한 값이 i->j로 직접 이동했을 때와 비교해서 작은 값으로 인접행렬을 Update함.
				through_k = Matrix[i][k] + Matrix[k][j];
				if (through_k < Matrix[i][j])
				{
					Matrix[i][j] = through_k;
				}
			}
		}
	}
}

// 시작점과 종료점을 받아서 최단거리 계산 및 경유한 경로 표시
int FindPath(int Start, int End)
{
	int ShortestPath = -1;
    
    // 최단거리 계산
    // 인접행렬에 거리가 Updat되어 있으므로 인접행렬 값을 Read
	ShortestPath = Matrix[Start][End];
	ANSWER = ShortestPath;

	return 1;
}

void MySolve2()
{
    // Dijkstra 알고리즘
	Dijkstra(1, M);
}
int Parent[MAX_N];
void Dijkstra(int Start, int End)
{
	bool intree[MAX_N];
	int distance[MAX_N];
	int v;          
	int w;          // 이웃정점
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

				// 정점간의 거리 비교하여 정점간의 최소값으로 거리를 Updaat하고,
				// 정점과 부모 노드와의 관계를 Update 함.
				if (distance[w] > distance[v] + weight)
				{
					distance[w] = distance[v] + weight;
					Parent[w] = v;
				}
			}            
		}

        // 정점 A와 정점 B가 직접적으로 연결되어 있지 않을 경우
        // 거리는 무한대이다.
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

    // 시작점과 종료점의 최단거리
	ANSWER = distance[End];
	cout << ANSWER << endl;
    // 경유한 경로
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
        // 재귀함수로 Parent[] 배열에 들어 있는 값을 추출하여
        // Stack에 넣는다. 
        //따라서, End에서부터 추출해서 Stack에 저장하면, Start부터 차례대로 출력.
		Dijkstra_FindPath(Start, parents[End], parents);
		cout << End;
	}
}