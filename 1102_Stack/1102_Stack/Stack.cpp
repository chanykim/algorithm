
/*
�Է� ��
7
i 7
i 5
c
o
o
o
c

��� ��
2
5
7
empty
0
*/

#include <iostream>
#include <stack>

using namespace std;

int N;
struct cmdArray{
	char cmdChar;
	int value;
};
void MySolve();
int main()
{
	// �Է�
	cin >> N;

	// �˰���
	MySolve();

	// ���

	return 0;
}

void MySolve()
{
	cmdArray processCmd[100];
	stack<int> MyStack;
	int value;
	int Output;
	
	// Stack�� �Է��ϴ� �κ�.
	for (int i = 0; i < N; i++)
	{
		cin >> processCmd[i].cmdChar;
		if (processCmd[i].cmdChar == 'i')
		{
			cin >> value;
			MyStack.push(value);
		}		
	}

	// �˰��� �����κ�
	for (int i = 0; i < N; i++)
	{
		if (processCmd[i].cmdChar == 'o')
		{
			if (MyStack.empty())
			{
				cout << "empty" << endl;
			}
			else
			{
				Output = MyStack.top();
				MyStack.pop();

				cout << Output << endl;
			}			
		}
		else if (processCmd[i].cmdChar == 'c')
		{
			cout << MyStack.size() << endl;
		}
	}
}