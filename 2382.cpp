#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <queue>

using namespace std;

#define AREA_MAX 100
#define BUG_MAX 1000 

enum Direction
{
	DEFAULT = 0, UP = 1, DOWN, LEFT, RIGHT,

	
};

typedef struct BugFlock
{
	int posX;
	int posY;

	Direction direction;
	int bugSize;

}BugFlock;

typedef struct BugArea
{
	int posX;
	int posY;
	int value;

	vector<BugFlock> ExistBug;

}BugArea;

BugArea Area[AREA_MAX+1][AREA_MAX+1] ;
BugFlock bugFlock[BUG_MAX+1] ;

int matSize, time, bugFlockSize;


void InitBugFlock();
void InitArea();
void InitRealArea();
void PrintArea();
void MoveBug();

queue<BugArea> bugAreaQ;

void InitBugFlock()
{
	for (int i = 0; i < bugFlockSize; i++)
	{
		bugFlock[i].bugSize = 0;
		bugFlock[i].posX = 0;
		bugFlock[i].posY = 0;
		bugFlock[i].direction = Direction::DEFAULT;

	}
}

void InitArea()
{
	for (int i = 0; i < matSize; i++)
	{
		for (int j = 0; j < matSize; j++)
		{
			Area[i][j].value = 1;
		}
	}

}

void InitRealArea()
{
	for (int i = 1; i < matSize-1; i++)
	{
		for (int j = 1; j < matSize-1; j++)
		{
			Area[i][j].value = 0;
			Area[i][j].ExistBug.clear();
			
		}
	}

}

void PrintArea()
{
	for (int i = 0; i < matSize; i++)
	{
		for (int j = 0; j < matSize; j++)
		{
			if (!Area[i][j].ExistBug.empty())
			{
				printf("%d ", Area[i][j].ExistBug[0].bugSize);
			}
				
			else
				printf("%d ", Area[i][j].value);
		}
		
		cout << endl;
	}
		
}

void MoveBug()
{
	int dx[5] = { -1000, 0,0,-1,1 };
	int dy[5] = { -1000, 1,-1,0,0 };

	int newX = 0;
	int newY = 0;

	queue<BugArea> newBugAreaQ;

	while (!bugAreaQ.empty())
	{
		BugArea bugArea_front = bugAreaQ.front();
		bugAreaQ.pop();
		//�����̹Ƿ� ������ ����Ű�� �̻��� ������ ��� �����ְ�
		//ť���� �ϳ��� ���鼭 Move �����ش�

		//�̻��� ������ ó������ ��ǰ ó�� �� ������ ������ 
		//
		//if (bugFlock_front->posX == 0 || bugFlock_front->posY == 0 || bugFlock_front->posX == matSize - 1 || bugFlock_front->posY == matSize - 1)
		//{
		//	Direction tmpDirection = Direction::DEFAULT;
		//	if (bugFlock_front->direction == Direction::UP)
		//		tmpDirection = Direction::DOWN;
		//	else if (bugFlock_front->direction == Direction::DOWN)
		//		tmpDirection = Direction::UP;
		//	else if (bugFlock_front->direction == Direction::LEFT)
		//		tmpDirection = Direction::RIGHT;
		//	else if (bugFlock_front->direction == Direction::RIGHT)
		//		tmpDirection = Direction::LEFT;

		//	Area[newX][newY].pExistBug.push_back(bugFlock_front->pBugFlock);
		//	newPosQ.push(make_pair(bugFlock_front->posX, bugFlock_front->posY));
		//	continue;
		//}


		newX = bugArea_front.posX + dx[(int)bugArea_front.ExistBug[0].direction];
		newY = bugArea_front.posY + dy[(int)bugArea_front.ExistBug[0].direction];

		BugFlock bugFlock;
		bugFlock.posX = newX;
		bugFlock.posY = newY;
		bugFlock.bugSize = bugArea_front.ExistBug[0].bugSize;
		bugFlock.direction = bugArea_front.ExistBug[0].direction;

		Area[newX][newY].posX = newX;
		Area[newX][newY].posY = newY;
		Area[newX][newY].ExistBug.push_back(bugFlock);
		newBugAreaQ.push(Area[newX][newY]);
	}



	while (!newBugAreaQ.empty())
	{
		//��� ������ ����ó�� �Ǿ ť�� ������
		BugArea bugArea_front = newBugAreaQ.front();
		newBugAreaQ.pop();

		int bugSum = 0;
		int maxBugSize = -1;
		Direction tmpDirection = Direction::DEFAULT;

		//���� �Ŀ� 
		//�ݺ����� ���� �̻����� ������ �����Ҷ����� �����ְ�, �׵θ��� ���� ��� �ݰ� ������
		for (int i = 0; i < bugArea_front.ExistBug.size(); i++)
		{
			//��ǰ����, ������ �ݰ��ǰ� ������ ����
			//�ϳ��ۿ� �� ����
			if (bugArea_front.ExistBug[0].posX == 0 || bugArea_front.ExistBug[0].posY == 0 || bugArea_front.ExistBug[0].posX == matSize - 1 || bugArea_front.ExistBug[0].posY == matSize - 1)
			{
				//������ �ݰ��ǰ�
				bugSum = (int)Area[bugArea_front.posX][bugArea_front.posY].ExistBug[0].bugSize / 2;
			
				//������ �ݴ��
				
				if (bugArea_front.ExistBug[0].direction == Direction::UP)
					tmpDirection = Direction::DOWN;
				else if (bugArea_front.ExistBug[0].direction == Direction::DOWN)
					tmpDirection = Direction::UP;
				else if (bugArea_front.ExistBug[0].direction == Direction::LEFT)
					tmpDirection = Direction::RIGHT;
				else if (bugArea_front.ExistBug[0].direction == Direction::RIGHT)
					tmpDirection = Direction::LEFT;

				break;
				
			}

			// �������� �϶��� �����ص�
			bugSum += bugArea_front.ExistBug[i].bugSize;

			if (maxBugSize < bugArea_front.ExistBug[i].bugSize)
				tmpDirection = bugArea_front.ExistBug[i].direction;
				
		}

		// �ִ� �� ��� ���� �����ְ�
		bugArea_front.ExistBug.clear();

		BugFlock bugFlock;
		bugFlock.bugSize = bugSum;
		bugFlock.direction = tmpDirection;
		bugFlock.posX = bugArea_front.posX;
		bugFlock.posY = bugArea_front.posY;

		// �ٽ� �ϳ� �ִ´�.
		Area[bugArea_front.posX][bugArea_front.posY].ExistBug.push_back(bugFlock);
		bugAreaQ.push(Area[bugArea_front.posX][bugArea_front.posY]);
		//�׸��� ���� ť�� �ٽ� �ֱ�

	}	


}

int main(void)
{

	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	int T;
	cin >> T;

	while (T--)
	{
		cin >> matSize;
		cin >> time ;
		cin >> bugFlockSize; 


		InitArea();
		InitRealArea();



		for (int i = 0; i < BUG_MAX; i++)
		{
			bugFlock[i].posX = 0;
			bugFlock[i].posY = 0;
			bugFlock[i].bugSize = 0;
			bugFlock[i].direction = Direction::DEFAULT;
		}

		
		
		for (int i = 0; i < bugFlockSize; i++)
		{
			scanf("%d", &bugFlock[i].posX);
			scanf("%d", &bugFlock[i].posY);
			scanf("%d", &bugFlock[i].bugSize);
			scanf("%d", &bugFlock[i].direction);

			printf("%d, %d, %d, %d\n", bugFlock[i].posX, bugFlock[i].posY, bugFlock[i].bugSize, bugFlock[i].direction);
			
			int area_posX = bugFlock[i].posX;
			int area_posY = bugFlock[i].posY;


			Area[area_posX][area_posY].posX = area_posX;
			Area[area_posX][area_posY].posY = area_posY;

			Area[area_posX][area_posY].ExistBug.clear();
			Area[area_posX][area_posY].ExistBug.push_back(bugFlock[i]);

			//�ش� ������ ������ �ϳ� �ۿ� ������ �ȵǹǷ�
			//�ϳ��� ���� �ϴ� �ִ´�
			bugAreaQ.push(Area[area_posX][area_posY]);
		}

		PrintArea();

		cout << endl;
		//�ʱ�

		while (time--)
		{
			MoveBug();
		}

		cout << endl;

		PrintArea();
	}


	

	return 0;
}
