
#include <iostream>

using namespace std;

char StringBuf[10000] = { 0, };
int nKOI = 0, nIOI = 0;

void MySolve();
void MySolve1();
int main()
{
	// 입력
	cin >> StringBuf;

	// 알고리즘
	MySolve();
	//MySolve1();

	// 출력
	cout << nKOI << endl;
	cout << nIOI << endl;
	return 0;
}

void MySolve()
{
	// 비교할 문자열
	char *pKOI = "KOI";
	char *pIOI = "IOI";
	char temp[4];

	// 입력된 문자열 길이
	int length = strlen(StringBuf);
	for (int i = 0; i < length-2; i++)
	{
		strncpy_s(temp, StringBuf + i, 3);
		if (!strncmp("KOI", temp, 3))
		{
			nKOI++;
		}
		else if (!strncmp("IOI", temp, 3))
		{
			nIOI++;
		}
	}
}

// strcmp 함수 사용하지 않고, char 하나씩 비교.
void MySolve1()
{
	// 입력된 문자열 길이
	int length = strlen(StringBuf);

	int i = 0;
	while (StringBuf[i + 2] != '\0')
	{
		if ((StringBuf[i] == 'K') && (StringBuf[i + 1] == 'O') && (StringBuf[i + 2] == 'I'))
		{
			nKOI++;
		}
		else if ((StringBuf[i] == 'I') && (StringBuf[i + 1] == 'O') && (StringBuf[i + 2] == 'I'))
		{
			nIOI++;
		}

		i++;		// 문자열을 하나씩 증가시키면서 비교.
	}
}