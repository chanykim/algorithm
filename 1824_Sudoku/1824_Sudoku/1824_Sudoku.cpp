/*
-------------------------- Sudoku Algorithm --------------------------
Find row, col of an unassigned cell
If there is none, return true
For digits from 1 to 9
a) If there is no conflict for digit at row,col
assign digit to row,col and recursively try fill in rest of grid
b) If recursion successful, return true
c) Else, remove digit and try another
If all digits have been tried and nothing worked, return false
*/

/*
입력 예
9
0 3 5 4 6 9 2 7 8
7 8 2 1 0 5 6 0 9
0 6 0 2 7 8 1 3 5
3 2 1 0 4 6 8 9 7
8 0 4 9 1 3 5 0 6
5 9 6 8 2 0 4 1 3
9 1 7 6 5 2 0 8 0
6 0 3 7 0 1 9 5 2
2 5 8 3 9 4 7 6 0

*/
#include <iostream>

using namespace std;

int N;
const int MAX_N = 9;
int Sudoku[MAX_N][MAX_N];

const int UNASSIGNED = 0;
void MySolve();
bool SudokuSolve();
bool FindUnassignedCell(int& Row, int& Column);
bool Promising(int Row, int Column, int Num);
bool UsedInRow(int Row, int Num);
bool UsedInColumn(int Column, int Num);
bool UsedInBox(int StartRow, int StartColumn, int Num);
void PrintSudokuSolve();
int main()
{
	int test_case;

	//freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	for (test_case = 1; test_case <= 10; test_case++)
	{
		// 입력
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> Sudoku[i][j];
			}
		}

		// write Algorithm
		MySolve();

		// Output
		PrintSudokuSolve();
	}
	return 0;
}

void MySolve()
{
	SudokuSolve();
    
}

bool SudokuSolve()
{
    int row, column;
	int solution = false;
	
    // 스도쿠에서 비어있는 셀을 찾으면 true, 비어있는 셀이 없으면 false
    if(!FindUnassignedCell(row, column))
		return true;	// 스도쿠에 비어있는 부분이 없으므로 더이상 처리하지 않고, return

	// 1 부터 N까지 숫자를 넣어서 유효한 값인지를 판단한다.
	for(int num = 1; num <= N; num++)
	{
	    if(Promising(row, column, num))
	    {
		    // 임의의 값으로 잠정적(tentative)으로 할당해본다.
		    Sudoku[row][column] = num;

			// recursive call
			solution = SudokuSolve();
			if(solution)
				return true;

			// if failure, unmake & try again!
			Sudoku[row][column] = UNASSIGNED;
	    }
	}

	return false;
}

// 
bool FindUnassignedCell(int & Row, int & Column)
{
    for(Row = 0; Row < N; Row++)
    {
		for(Column = 0; Column < N; Column++)
		{
		    if(Sudoku[Row][Column] == UNASSIGNED)
		    {
		        return true;
		    }
		}
	}

	return false;
}

/* Returns a boolean which indicates whether it will be legal to assign
   num to the given row,col location. */
bool Promising(int Row, int Column, int Num)
{
	bool isPromising = false;

	/* Check if 'num' is not already placed in current row,
       current column and current 3x3 box */
	if(!UsedInRow(Row, Num) &&
		!UsedInColumn(Column, Num) &&
		!UsedInBox(Row - Row%3, Column - Column%3, Num))
	{
		isPromising = true;
	}

	return isPromising;
}

bool UsedInRow(int Row, int Num)
{
	for(int column = 0; column < N; column++)
	{
		if(Sudoku[Row][column] == Num)
			return true;
	}

	return false;
}

bool UsedInColumn(int Column, int Num)
{
	for(int row = 0; row < N; row++)
	{
		if(Sudoku[row][Column] == Num)
			return true;
	}

	return false;
}

/* Returns a boolean which indicates whether any assigned entry
   within the specified 3x3 box matches the given number. */
bool UsedInBox(int StartRow, int StartColumn, int Num)
{
	for(int row = 0; row < 3; row++)
	{
		for(int column = 0; column < 3; column++)
		{
			if(Sudoku[row+StartRow][column+StartColumn] == Num)
				return true;
		}
	}
	return false;
}

void PrintSudokuSolve()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cout << Sudoku[i][j] << " ";
        }
		cout << endl;
    }
}