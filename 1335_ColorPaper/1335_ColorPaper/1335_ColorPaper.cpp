// 1335_ColorPaper.cpp : Defines the entry point for the console application.
//

/*
** ����Ǯ�� ����.
** 
*/

/*
�Է� ��
8
1 1 0 0 0 0 1 1
1 1 0 0 0 0 1 1
0 0 0 0 1 1 0 0
0 0 0 0 1 1 0 0
1 0 0 0 1 1 1 1
0 1 0 0 1 1 1 1
0 0 1 1 1 1 1 1
0 0 1 1 1 1 1 1

��� ��
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
	// �Է�
	cin >> N;
	
	// 2���� �迭 �����Ҵ�
	ppColorPaper = new int*[N];
	for (int arr = 0; arr < N; arr++)			// 2���� �迭�� ��
	{
		ppColorPaper[arr] = new int[N];	// 2���� �迭�� �࿡ ���� ��
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> ppColorPaper[i][j];
			
		}
	}

	// �˰��� ����
	partition(0, 0, N);

	// ���
	cout << white << endl;
	cout << blue << endl;

	delete [] ppColorPaper;

	return 0;
}

void partition(int col, int row, int size)
{
	bool SameColor = false;
	int offset = 0;

	// �迭���� ��ҵ��� 0 �Ǵ� 1�� ��� ä���� �ִ��� Ȯ��
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (ppColorPaper[col+i][row+ j] == 1)			// �Ķ������� ä���� �ִ��� �Ǵ�			
			{
				offset++;
			}			
		}
	}

	if (!offset)		// �Ķ������� ä���� �ִ��� ���� Ȯ��
	{
		white++;
		return;
	}
	if (offset == size*size)
	{
		// offset ������ �Ķ����� ���� ������ ����Ǵµ� 
		//�� ������ size*size�� ������ �� size ũ���� matrix�� ��� �Ķ����� ä���� ������ �� �� �ִ�.
		blue++;
		return;
	}

	// �׷��� ���� ��� �ٽ� ������ ����.
	partition(col, row, size / 2);
	partition(col + size / 2, row, size / 2);
	partition(col, row + size / 2, size / 2);
	partition(col + size / 2, row + size / 2, size / 2);
}