/*
N-Queen Algorithm.
1. One Queen place on Board.
2. Another Queen placed on Board.
2.1 You can't place on same row.
2.2 You can't place on same column.
2.3 You can't place on ´ë°¢¼±.
3. 
*/
#include <iostream>

using namespace std;

const int MAX_N = 14;
int N;					// number of Queen
int ChessBoard[MAX_N][MAX_N];
int ANSWER[MAX_N];
int index;
int cnt;

void MySolve();
void PlacedQueen(int Row);
bool Promising(int Row, int Column);
int main()
{
	int test_case;
	//freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	for (test_case = 0; test_case < 10; test_case++)
	{
		// read number of Queen
		cin >> N;

		// write algorithm
		MySolve();

		cout << cnt << endl;
	}
	return 0;
}

void MySolve()
{
	PlacedQueen(1);

}

void PlacedQueen(int Row)
{
    if(Row > N)
    {
        // check solution
		for (int i = 0; i < N; i++)
			cout << ANSWER[i] << " ";
		cout << endl;

		cnt++;
        return;
    }

	for(int i = 1; i <= N; i++)	
	{
	    if(Promising(Row, i))
	    {
	        ChessBoard[Row][i] = 1;
			ANSWER[index] = i;
			index++;

			// recursive call
	        PlacedQueen(Row + 1);

			// Backtrack
			ChessBoard[Row][i] = 0;
			index--;
	    }
	}

}

bool Promising(int Row, int Column)
{
	int i, j;

    // check same row and other columns
//    for(i = 1; i <= N; i++)
    for(i = 1; i <= Row; i++)
    {
    	// if you placed queen on same column, it return false.
        if(ChessBoard[i][Column] == 1)
			return false;
    }

	// check Right-Down to Left-Top
//	for(i = 1, j = 1; i <= N && j <= N; i++, j++)
    for(i = Row, j = Column; i >= 1 && j >= 1; i--, j--)
	{
	    if(ChessBoard[i][j] == 1)
			return false;
	}

	// check Left-Down to Right-Top
//	for(i = Row, j = 1; i <= 1 && j <= N; i--, j++)
    for(i = Row, j = Column; i >= 1 && j <= N; i--, j++)
	{
	    if(ChessBoard[i][j] == 1)
	    	return false;
	}

	return true;
}