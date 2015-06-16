
#include <iostream>

using namespace std;

const int MAX_N = 10;
char S[MAX_N];
int X;

void MySolve();
int myatoi(char* str, int len);
int main()
{
	// �Է�
	cin >> S;
	cin >> X;

	// �˰���
	MySolve();

	// ���

	return 0;
}

void MySolve()
{
	int len = 0;
	int sa = 0, sb = 0;
	char* p;

	// ���ڿ� �迭�� 0��°���� �ϳ��� �߶� ������ �κа� ���� ���غ���.
	len = strlen(S);
	for (int i = 1; i < len; i++)
	{
		sa = myatoi(S, i);
		p = S + i;			// ������ p�� S[i] ���Ŀ��� ���ڿ� �������� ����Ų��.
		sb = myatoi(p, strlen(p));

		if (sa + sb == X)
		{
			break;
		}
	}

	if (sa + sb == X)
	{
		cout << sa << "+" << sb << "=" << X << endl;
	}
	else
	{
		cout << "NONE" << endl;
	}
}

int myatoi(char* str, int len)
{
	int ret = 0;
	for (int i = 0; i < len; i++)
	{
		ret = ret * 10 + str[i] - '0';		// 10�� ���ϴ� ������ for �� �ݺ��� �� ��, �ڸ����� �ϳ��� �ø��� ���ؼ�
	}

	return ret;
}