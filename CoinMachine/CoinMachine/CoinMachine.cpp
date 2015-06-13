/*
����
ö���� ���� ���Ǳ⸦ ���� �̿��Ѵ�. �׷��� �״� �׻� ����� ���� ������ �������� �ָӴϿ� ������ �ٴϴµ�, 
�������� �ָӴϿ��� ©���Ÿ��� ���� ��� �Ⱦ��Ѵ�. 
�׷��� ö���� �������Ǳ⿡�� ���� �� ���� �ǵ��� ���� ������ ������ ����Ѵ�. 
ö���� ������ �ִ� ���Ǳ���� ���� ������ ���̾ ���� ����� �� ����, ��, ��Ȯ�� �׼����� �־�� �Ѵ�.

�� ������ ö���� ������ �ִ� ���� �� �ִ� ������ ������ �̿��Ͽ� ���Ǳ��� ������ �����ϴ� ����� ����ϴ� ���α׷��� �ۼ��ϴ� ���̴�.

�Է� ���
ù�ٿ��� ���Ǳ⿡�� �����Ϸ��� ������ �� W�� �־�����. 
��°�ٿ��� 6���� ������ �־�����. 
������ ������ ö���� ������ �ִ� 500��¥��, 100��¥��, 50��¥��, 10��¥��, 5��¥��, 1��¥�� �������� ������ ������� ��Ÿ����. 
������ ���� ������ 1 �̻� 10�����̴�. ������ ���̿��� ��ĭ�� �ϳ� �ִ�.

��� ���
ù �ٿ��� ������ ���Կ� ���� �� �ִ� �ִ� ������ �������� ����Ѵ�. 
��°�ٿ��� �ִ� ������ �����ϴ� �����鿡 ���� 500��¥������ �����ؿ� ������ ������ ������� ����Ѵ�.
�� 6���� ������ ��µǾ�� �ϸ� ������� �ʴ� �׼��� ������ ������ �� �׼��� ���ؼ���0�� ����Ѵ�.

�Է�
13
4 5 2 6 3 4

���
5
0 0 0 0 2 3
*/
#include <iostream>

using namespace std;

int W;							// ������ ��
int CoinNumber[6] = { 0, };		// ������ ����
int CoinCapability[6] = {0,};
int Coin[6] = {500, 100, 50, 10, 5, 1};
int answer;

void MySolve();
void solve();
void dfs(int money, int cnt);

int main()
{
	// �Է�
	cin >> W;
	for (int i = 0; i < 6; i++)
	{
		cin >> CoinNumber[i];
	}

	// �˰���
	MySolve();

//	solve();

	// ���
	cout << answer << endl;

	return 0;
}

void MySolve()
{
	int Balance = 0;
	int Flag = 0;
	int Count = 0;

	// �־��� ȭ�� ������ �������� ������ ��, �� ȭ�� ����� �� �ִ� ����
	// (���� = ������ / ȭ�� ����)
	for (int i = 0; i < 6; i++)
	{
		CoinCapability[i] = W / Coin[i];
		if (CoinCapability[i] > CoinNumber[i])
		{
			// ���� ȭ�� ��� ������ �־��� �������� Ŭ ��� �־��� ������ ����.
			// ���� ��� ���� �������� 13(������)�� 1��(ȭ�� ����)�� ������ �� ȭ�� ��� ������ 13�̴�.
			//  �׷��� �־��� 1���� ������ 4�� �̹Ƿ� 4�� �̻��� ����� �� ����.
			// ����, ȭ�� ��� ���� 13�� ���ǹ��ϹǷ� �� ���� �־��� ������ ����ǵ��� �־��ش�.
			CoinCapability[i] = CoinNumber[i];
		}
	}

	// ������ �ִ��� ���� ����ؾ� �ϹǷ�, ���� ȭ��������� ����Ѵ�.
	for (int i = 5; i < 0; i--)
	{
		if (Flag == 1)
		{
			// �����ؾ� �� ��꿡 ������ �����Ƿ� �ش� �迭���� ��� 0���� ä��.
			CoinCapability[i] = 0;
		}

		Balance += CoinCapability[i] * Coin[i];
		if (Balance > W)
		{
			// ���� ȭ��������� ����Ͽ� ������ �ݾ��� ���ұݾ׺��� Ŀ�� ��� ���̻� ���� �������� �����Ƿ� ������Ű�� ����.
			Flag = 1;
		}
	}

	// ���� ������ ȭ��������� ū ȭ������� ���� ȭ��������� ���� �������� Ȯ��.
	// ���� ȭ�� ������ ���� ����� ���� ���Ǵ� ������ ������ �������Ƿ�...
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
				// ������ �� �ִ� ������ �������� Ŭ ��� ���Ұ����� ������ ���� ����.
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