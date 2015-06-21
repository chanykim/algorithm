
/*
입력 예
5
4 9 5 2 2 1 3 5 1 4

출력 예
2

입력 예
3
1 3 2 2 3 1

출력 예
3
*/
#include <iostream>

using namespace std;

struct SAUSAGE{
	int SL;			// 길이
	int SW;			// 너비
	};

int N;
SAUSAGE Sausage[5000];

void MySolve();
int Compare(void* context, const void* a, const void* b);
int main()
{
	// 입력
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> Sausage[i].SL >> Sausage[i].SW;
	}

	// 알고리즘
	MySolve();

	// 출력

	return 0;
}

void MySolve()
{
	int WorkingTime = 1;		// 

	// 소시지 너비(SW)로 오름차순 정렬
	qsort_s(Sausage, N, sizeof(*Sausage), Compare, NULL);

	// 위에서 정렬된 내용을 통해 준비작업 최소화 
	int Prev_Sausage = 0;
	for (int i = 0; i < N; i++)
	{
		if (Prev_Sausage <= Sausage[i].SL)
		{
			Prev_Sausage = Sausage[i].SL;
		}
		else if(Prev_Sausage > Sausage[i].SL)
		{
			Prev_Sausage = Sausage[i].SL;
			WorkingTime++;
		}
	}

	cout << WorkingTime << endl;
}

int Compare(void* context, const void* a, const void* b)
{
	struct SAUSAGE arg1 = *(const struct SAUSAGE*)a;
	struct SAUSAGE arg2 = *(const struct SAUSAGE*)b;

	// SW로 오름차순 정렬
	if (arg1.SW < arg2.SW) return -1;
	else if (arg1.SW > arg2.SW) return 1;
	else
		return 0;
}


#if 0
struct SAUSAGE{
	int SL;			// 길이
	int SW;			// 너비
	int visit;
};
void MySolve()
{
	bool visit_flag = true;
	int prev_sw = 0;
	int delay_time = -1;

	qsort_s(Sausage, N, sizeof(*Sausage), Compare, NULL);

	while (visit_flag != 0)
	{
		visit_flag = 0;
		prev_sw = 0;
		delay_time++;

		for (int i = 0; i < N; i++)
		{
			if (Sausage[i].visit == 0)
			{
				visit_flag = 1;
				if (Sausage[i].SW >= prev_sw)
				{
					Sausage[i].visit = 1;
					prev_sw = Sausage[i].SW;
				}
			}
		}
	}

	cout << delay_time << endl;
}

int Compare(void* context, const void* a, const void* b)
{
	if ((*(SAUSAGE *)a).SL > (*(SAUSAGE *)b).SL)
		return 1;
	else if ((*(SAUSAGE *)a).SL < (*(SAUSAGE *)b).SL)
		return -1;
	else
	{
		if ((*(SAUSAGE *)a).SW >(*(SAUSAGE *)b).SW)
			return 1;
		else if ((*(SAUSAGE *)a).SW > (*(SAUSAGE *)b).SW)
			return -1;
		else
			return 0;
	}
}
#endif