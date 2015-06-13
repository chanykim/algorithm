/*
문제
철수는 동전 자판기를 자주 이용한다. 그래서 그는 항상 상당히 많은 개수의 동전들을 주머니에 가지고 다니는데, 
동전들이 주머니에서 짤랑거리는 것을 듣기 싫어한다. 
그래서 철수는 동전자판기에서 무언가 살 때는 되도록 많은 개수의 동전을 사용한다. 
철수의 주위에 있는 자판기들은 아주 구형인 모델이어서 지폐를 사용할 수 없고, 또, 정확한 액수만을 넣어야 한다.

이 문제는 철수가 가지고 있는 동전 중 최대 개수의 동전을 이용하여 자판기의 물건을 구입하는 방법을 출력하는 프로그램을 작성하는 것이다.

입력 방식
첫줄에는 자판기에서 구입하려는 물건의 값 W가 주어진다. 
둘째줄에는 6개의 정수가 주어진다. 
각각의 정수는 철수가 가지고 있는 500원짜리, 100원짜리, 50원짜리, 10원짜리, 5원짜리, 1원짜리 동전들의 개수를 순서대로 나타낸다. 
각각의 동전 개수는 1 이상 10이하이다. 정수들 사이에는 빈칸이 하나 있다.

출력 방식
첫 줄에는 물건의 구입에 사용될 수 있는 최대 개수의 동전수를 출력한다. 
둘째줄에는 최대 개수를 구성하는 동전들에 대해 500원짜리부터 시작해여 각각의 개수를 순서대로 출력한다.
즉 6개의 정수가 출력되어야 하며 사용하지 않는 액수의 동전이 있으면 그 액수에 대해서는0을 출력한다.

입력
13
4 5 2 6 3 4

출력
5
0 0 0 0 2 3
*/
#include <iostream>

using namespace std;

int W;							// 물건의 값
int CoinNumber[6] = { 0, };		// 동전의 개수
int CoinCapability[6] = {0,};
int Coin[6] = {500, 100, 50, 10, 5, 1};
int answer;

void MySolve();
void solve();
void dfs(int money, int cnt);

int main()
{
	// 입력
	cin >> W;
	for (int i = 0; i < 6; i++)
	{
		cin >> CoinNumber[i];
	}

	// 알고리즘
	MySolve();

//	solve();

	// 출력
	cout << answer << endl;

	return 0;
}

void MySolve()
{
	int Balance = 0;
	int Flag = 0;
	int Count = 0;

	// 주어진 화폐 단위로 목적값을 지불할 때, 각 화폐별 사용할 수 있는 개수
	// (개수 = 목적값 / 화폐 단위)
	for (int i = 0; i < 6; i++)
	{
		CoinCapability[i] = W / Coin[i];
		if (CoinCapability[i] > CoinNumber[i])
		{
			// 계산된 화폐별 사용 개수가 주어진 개수보다 클 경우 주어진 개수로 변경.
			// 예를 들어 위의 문제에서 13(목적값)을 1원(화폐 단위)로 지불할 때 화폐 사용 개수는 13이다.
			//  그러나 주어진 1원의 개수는 4개 이므로 4개 이상은 사용할 수 없다.
			// 따라서, 화폐 사용 개수 13은 무의미하므로 이 값을 주어진 개수로 변경되도록 넣어준다.
			CoinCapability[i] = CoinNumber[i];
		}
	}

	// 동전을 최대한 많이 사용해야 하므로, 작은 화폐단위부터 사용한다.
	for (int i = 5; i < 0; i--)
	{
		if (Flag == 1)
		{
			// 지불해야 할 계산에 사용되지 않으므로 해당 배열들을 모두 0으로 채움.
			CoinCapability[i] = 0;
		}

		Balance += CoinCapability[i] * Coin[i];
		if (Balance > W)
		{
			// 작은 화폐단위부터 사용하여 누적된 금액이 지불금액보다 커진 경우 더이상 돈을 지불하지 않으므로 누적시키지 않음.
			Flag = 1;
		}
	}

	// 지불 가능한 화폐단위에서 큰 화폐단위를 작은 화폐단위에서 지불 가능한지 확인.
	// 작은 화폐 단위를 많이 사용할 수록 사용되는 동전의 개수가 많아지므로...
	for (int i = 0; i < 6; i++)
	{
		if (CoinCapability[i] != 0 && i != 5)
		{
			if (((CoinCapability[i + 1] * Coin[i + 1]) / Coin[i]) > 0)
			{
				CoinCapability[i] -= ((CoinCapability[i + 1] * Coin[i + 1]) / Coin[i]);
			}
		}
	}

	Balance = 0;

	for (int i = 0; i < 6; i++)
	{
		if (CoinCapability[i] != 0)
		{
			if (i != 5)
			{
				// 지불할 수 있는 동전의 개수보다 클 경우 지불가능한 동전의 수로 변경.
				if (W / Coin[i] < CoinCapability[i])
					CoinCapability[i] = W / Coin[i];
			}
			else
			{
				CoinCapability[i] = W - Balance;
			}

			Balance += Coin[i] * CoinCapability[i];
		}

		Count += CoinCapability[i];
	}

	answer = Count;
}



// ----------------------------------------------------------------------
void solve()
{
	int w = 0, rw = 0;
	int result = 0;
	int flag = 0;

	int coinN[6] = { 0, };
	int coinRN[6] = { 0, };
	int coin[6] = { 500, 100, 50, 10, 5, 1 };

	int n = 0;
	int i = 0;

	scanf_s("%d", &w);
	scanf_s("%d %d %d %d %d %d", &coinN[0], &coinN[1], &coinN[2], &coinN[3], &coinN[4], &coinN[5]);

	for (i = 0; i < 6; i++)
	{
		coinRN[i] = w / coin[i];
		if (coinRN[i] > coinN[i])
		{
			coinRN[i] = coinN[i];
		}
	}

	for (i = 5; i >= 0; i--)
	{
		if (flag == 1)
			coinRN[i] = 0;
		else
		{
			rw += coinRN[i] * coin[i];
			if (w <= rw)
			{
				flag = 1;
			}
		}
	}

	for (i = 0; i < 6; i++)
	{
		if (coinRN[i] != 0 && i != 5)
		{
			if (((coin[i + 1] * coinRN[i + 1]) / coin[i]) > 0)
				coinRN[i] -= ((coin[i + 1] * coinRN[i + 1]) / coin[i]);
		}
	}

	rw = 0;

	for (i = 0; i < 6; i++)
	{
		if (coinRN[i] != 0)
		{
			if (i != 5)
			{
				if ((w / coin[i]) < coinRN[i])
					coinRN[i] = w / coin[i];
			}
			else
				coinRN[i] = w - rw;

			rw += (coinRN[i] * coin[i]);
		}

		n += coinRN[i];

		if (rw == w)
		{
			break;
		}
	}

	printf("%d", n);
	for (i = 0; i < 6; i++)
	{
		printf("%d ", coinRN[i]);
	}
	printf("\r\n");
}
// ----------------------------------------------------------------------