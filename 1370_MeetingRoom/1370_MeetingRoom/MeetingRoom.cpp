
/*
�Է�
6
1 1 10
2 5 6
3 13 15
4 14 17
5 8 14
6 3 12

���
3
2 5 4
*/
#include <iostream>

using namespace std;

const int MAX_N = 500;
int N;
int Matrix[MAX_N][3];
int numOfReservedRoom = 0;
int *MeetingRoomNumber;

struct ROOM{
	int num;
	int start_time;
	int end_time;
};

int compare(void* context, const void* a, const void* b);
void MySolve();
int main()
{
	// �Է�
	cin >> N;			// ȸ�ǽ� ����

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> Matrix[i][j];
		}
	}

	// �˰���
	MySolve();

	// ���
	cout << numOfReservedRoom << endl;
	for (int i = 0; i < numOfReservedRoom; i++)
	{
		if (i < numOfReservedRoom - 1)
		{
			cout << *(MeetingRoomNumber + i) << " ";
		}
		else
		{
			cout << *(MeetingRoomNumber + i) << endl;
		}
	}
	
	delete[] MeetingRoomNumber;

	return 0;
}

void MySolve()
{
	MeetingRoomNumber = new int[N];

	// �Էµ� ȸ�ǽ� ��ȣ�� ���۽ð�,����ð��� ����ü�� ����
	ROOM *MeetingRoom = new ROOM[N];
	//ROOM MeetingRoom[6];
	for (int i = 0; i < N; i++)
	{
		MeetingRoom[i].num = Matrix[i][0];
		MeetingRoom[i].start_time = Matrix[i][1];
		MeetingRoom[i].end_time = Matrix[i][2];
	}

	// �ַ�� �˰��� : ���� ����Ǵ� ȸ�ǿ� ���� ����

	// ����ð��� ���� ������������ ����
	qsort_s(MeetingRoom, N, sizeof(*MeetingRoom), compare, NULL);

	int time = 0;
	for (int i = 0; i < N; i++)
	{
		if (time <= (MeetingRoom+i)->start_time)
		{
			numOfReservedRoom++;
			time = (MeetingRoom + i)->end_time;
			MeetingRoomNumber[numOfReservedRoom - 1] = (MeetingRoom + i)->num;
		}
	}

	delete [] MeetingRoom;
	//delete[] MeetingRoomNumber;
}

int compare(void* context, const void* a, const void* b)
{
	struct ROOM* arg1 = (struct ROOM*)a;
	struct ROOM* arg2 = (struct ROOM*)b;

	// ������������ ���ĵǵ��� ����.
	if (arg1->end_time < arg2->end_time) return -1;
	else if (arg1->end_time > arg2->end_time) return 1;
	else
		return 0;
	/*
	// ������������ ���ĵǵ��� ����.
	if (arg1->end_time < arg2->end_time) return 1;
	else if (arg1->end_time > arg2->end_time) return -1;
	else
	return 0;
	*/
}