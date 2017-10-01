

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <list>

using namespace std;

#define MAX 500

typedef struct Customer 
{
	int id;	//���� �ο����� ��ȣ
	int visitTime; // ���� ���µ� ���� �ɸ��� �ð�

	int totalTime;		//�� �ɸ��� �ð�
}Customer;


int T ;

int receptionSize; 
int receptionLeadTime;

int repairSize; 
int repairLeadTime; 

int customerNum; 
int customVisitTime[11] = { 0, };

Customer* customer;

queue<Customer> waitingQ;
queue<Customer> receptionQ;
queue<Customer> repairQ;

//������ �ΰ� �� ���� �̿��� ���� â����ȣ A�� ���� â����ȣ B�� �־�����.
//k��° ���� ���� ����Ҹ� �湮�ϴ� �ð� tk�� ������� K�� �־�����.

int sReceptionNum;
int sRepairNum;

int curTime = 0;

void ProcessRepairQ(Customer front)
{
	while (1)
	{
		curTime++;
		if (curTime == repairLeadTime)
		{
			front.totalTime += curTime;
			break;
		}
	}

	curTime = 0;
}

void ProcessReceptionQ(Customer front)
{
	while (1)
	{
		curTime++;

		if (curTime == receptionLeadTime)
		{
			if (repairQ.size() >= receptionSize)
				break;

			front.totalTime += curTime;
			repairQ.push(front);
		}
	}

	curTime = 0;
}


int main(void)
{
	// https://www.acmicpc.net/problem/14500
	// 14500�� ����
	// ��Ʈ�ι̳�
	// Ǫ�� ��

	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	scanf("%d", &T);

	int test_case = 0;

	while (T--)
	{
		printf("�׽�Ʈ ���̽� : %d\n", ++test_case);

		cin >> receptionSize; cin >> repairSize; cin >> customerNum;
		cin >> sReceptionNum; cin >> sRepairNum;

		cin >> receptionLeadTime; cin >> repairLeadTime;

		customer = (Customer*)malloc(sizeof(Customer)*customerNum);

		for (int k = 0; k < customerNum; k++)
		{
			customer[k].id = k;
			customer[k].totalTime = 0;
			cin >> customer[k].visitTime;
			//�ʱ� ����
		}

		int waitingCurTime = 0;
		
		for (int k = 0; k < customerNum; k++)
		{
			waitingCurTime = 0;

			while (1)
			{
				waitingCurTime++;

				if (waitingCurTime == customer[k].visitTime)
				{
					if (receptionQ.size() < receptionSize)
					{
						receptionQ.push(customer[k]);
						continue;
					}
				}
			}
		}
	

		//�ȳ�����ũ ����
		while (!receptionQ.empty())
		{
			Customer front = receptionQ.front();
			receptionQ.pop();

			printf("�ȳ�����ũ ��� ����ȣ : %d\n", front.id+1);
			ProcessReceptionQ(front);
		}

		while (!repairQ.empty())
		{
			curTime = 0;
			Customer front = repairQ.front();
			repairQ.pop();

			printf("����� ��� ����ȣ : %d\n", front.id+1);
			ProcessRepairQ(front);
		}

		for (int k = 0; k < customerNum; k++)
			printf("�� �ð�: %d\n", customer[k].totalTime);

		printf("\n\n");
		
	}
	return 0;
}