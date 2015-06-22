
#include <iostream>

using namespace std;

char StringBuf[10000] = { 0, };
int nKOI = 0, nIOI = 0;

void MySolve();
void MySolve1();
int main()
{
	// �Է�
	cin >> StringBuf;

	// �˰���
	MySolve();
	//MySolve1();

	// ���
	cout << nKOI << endl;
	cout << nIOI << endl;
	return 0;
}

void MySolve()
{
	// ���� ���ڿ�
	char *pKOI = "KOI";
	char *pIOI = "IOI";
	char temp[4];

	// �Էµ� ���ڿ� ����
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

// strcmp �Լ� ������� �ʰ�, char �ϳ��� ��.
void MySolve1()
{
	// �Էµ� ���ڿ� ����
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

		i++;		// ���ڿ��� �ϳ��� ������Ű�鼭 ��.
	}
}