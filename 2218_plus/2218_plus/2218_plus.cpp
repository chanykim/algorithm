
#include <iostream>

using namespace std;

const int MAX_N = 10;
char S[MAX_N];
int X;

void MySolve();
int myatoi(char* str, int len);
int main()
{
	// 입력
	cin >> S;
	cin >> X;

	// 알고리즘
	MySolve();

	// 출력

	return 0;
}

void MySolve()
{
	int len = 0;
	int sa = 0, sb = 0;
	char* p;

	// 문자열 배열의 0번째부터 하나씩 잘라서 나머지 부분과 합을 구해본다.
	len = strlen(S);
	for (int i = 1; i < len; i++)
	{
		sa = myatoi(S, i);
		p = S + i;			// 포인터 p는 S[i] 이후에서 문자열 끝까지를 가리킨다.
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
		ret = ret * 10 + str[i] - '0';		// 10을 곱하는 이유는 for 문 반복을 할 때, 자릿수를 하나씩 올리기 위해서
	}

	return ret;
}