// 1335_ColorPaper.cpp : Defines the entry point for the console application.
//

/*
** 문제풀이 생각.
** 
*/

/*
입력 예
8
1 1 0 0 0 0 1 1
1 1 0 0 0 0 1 1
0 0 0 0 1 1 0 0
0 0 0 0 1 1 0 0
1 0 0 0 1 1 1 1
0 1 0 0 1 1 1 1
0 0 1 1 1 1 1 1
0 0 1 1 1 1 1 1

출력 예
9
7
*/
#include "stdafx.h"

#include <iostream>

using namespace std;

int N;
int **ppColorPaper;
int blue = 0, white = 0;

void partition(int col, int row, int size);
int _tmain(int argc, _TCHAR* argv[])
{
	// 입력
	cin >> N;
	
	// 2차원 배열 동적할당
	ppColorPaper = new int*[N];
	for (int arr = 0; arr < N; arr++)			// 2차원 배열의 행
	{
		ppColorPaper[arr] = new int[N];	// 2차원 배열의 행에 대한 열
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> ppColorPaper[i][j];
			
		}
	}

	// 알고리즘 구현
	partition(0, 0, N);

	// 출력
	cout << white << endl;
	cout << blue << endl;

	delete [] ppColorPaper;

	return 0;
}

void partition(int col, int row, int size)
{
	bool SameColor = false;
	int offset = 0;

	// 배열안의 요소들이 0 또는 1로 모두 채워져 있는지 확인
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (ppColorPaper[col+i][row+ j] == 1)			// 파랑색으로 채워져 있는지 판단			
			{
				offset++;
			}			
		}
	}

	if (!offset)		// 파랑색으로 채워져 있는지 여부 확인
	{
		white++;
		return;
	}
	if (offset == size*size)
	{
		// offset 값에는 파랑색인 셀의 개수가 저장되는데 
		//그 개수와 size*size가 같으면 그 size 크기의 matrix에 모두 파랑색이 채워져 있음을 알 수 있다.
		blue++;
		return;
	}

	// 그렇지 않을 경우 다시 반절로 나눔.
	partition(col, row, size / 2);
	partition(col + size / 2, row, size / 2);
	partition(col, row + size / 2, size / 2);
	partition(col + size / 2, row + size / 2, size / 2);
}