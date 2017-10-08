

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

#define ARR_MAX 101 
#define APPLE_MAX_SIZE 101
#define CMD_MAX_SIZE 101

enum Direction {
	DEFAULT =0 , UP, DOWN, LEFT, RIGHT
};


typedef struct Apple {
	int posX;
	int posY;

}Apple;

typedef struct Cmd {
	int sec;
	char direction;
}Cmd;


typedef struct Snake {
	
	Direction direction;				//Snake Area ����
	int size;
	vector<pair<int, int>> bodyPos;
}Snake;


typedef struct SnakeArea {

	int posX;
	int posY;
	int visited;

	int isApple;
};

int arrSize;
int appleSize;
int cmdSize;
int applePosX, applePosY;

int runnningTime = 0;

int dx[5] = { 0, 0, 0,-1,1 };
int dy[5] = { 0, -1, 1, 0, 0 };

// 0 

SnakeArea snakeArea[ARR_MAX][ARR_MAX] = { 0, };

Apple apple[APPLE_MAX_SIZE] = {0,};
Cmd cmd[CMD_MAX_SIZE] = { 0, };

void MoveSnake(Snake* snake, int startX, int startY);
void PrintSnakeAreaVisited(); 

queue<Cmd> cmdQ;

void MoveSnake(Snake snake, int startX, int startY)
{
	int posX = 0, posY = 0;

	snakeArea[startX][startY].visited = 1;
	

	while (true)
	{

		snake.bodyPos.push_back(make_pair(posX, posY));


		while (!cmdQ.empty())
		{
			Cmd cmd = cmdQ.front();

			if (runnningTime >= cmd.sec)
			{
				//���� ������ ���鿡�� �ٶ�
				switch (cmd.direction)
				{
				case 'L':
					if (snake.direction == Direction::UP)
						snake.direction = Direction::LEFT;
					else if (snake.direction == Direction::DOWN)
						snake.direction = Direction::RIGHT;
					else if (snake.direction == Direction::LEFT)
						snake.direction = Direction::DOWN;
					else if (snake.direction == Direction::RIGHT)
						snake.direction = Direction::UP;
					break;
				case 'D':
					if (snake.direction == Direction::UP)
						snake.direction = Direction::RIGHT;
					else if (snake.direction == Direction::DOWN)
						snake.direction = Direction::LEFT;
					else if (snake.direction == Direction::LEFT)
						snake.direction = Direction::UP;
					else if (snake.direction == Direction::RIGHT)
						snake.direction = Direction::DOWN;
					break;
				case Direction::DEFAULT:
					break;
				default:
					break;
				}

				cmdQ.pop();
				break;
			}

			break;
		}


		posX = posX + dx[(int)snake.direction];
		posY = posY + dy[(int)snake.direction];


		//////////////////////// Ż������
		//1. ���� �Ӹ��� ��ų�
		if (posX < 0 || posX >= arrSize || posY < 0 || posY >= arrSize)
			break;

		//2. �Ӹ��� ���뿡 ��ų�
		//i�� 0���� ���� ���� ������ �Ӹ��κ��� ���Խ�Ű�� �ʱ� ����
	
		for (int i = 1; i < snake.size; i++)
		{
			int bodyPosX = snake.bodyPos[snake.bodyPos.size() - 1 - i].first;
			int bodyPosY = snake.bodyPos[snake.bodyPos.size() - 1 - i].second;

			if (bodyPosX == posX && bodyPosY == posY)
				break;
		}
		/////////////////////////
		//����� ������ ���� �þ
		//������� �ʿ����... ���� �Ӹ��� ���� �ε����� ������ �����Ƿ� ������ ��ġ������ vector�� �����ص�
		//�׸��� ������ ��ȯ�Ҷ� ���� �˻縦 �ϸ鼭 �ε����� �� �˻��ϸ� ���� ������...
		//������ �����ϰ� ����� �����ؾ� �ǰڱ���...
		//�׷��� �ؾ� ���� ���� ���� ������ �� ����������� ��ġ ���� �� �� �ְڱ���
		if (snakeArea[posX][posY].isApple)
		{
			snake.size += 1;
		}

		snakeArea[posX][posY].visited = 1;

		///////////////// visited ��� ////////////////////
		PrintSnakeAreaVisited();
		cout << endl;
		//////////////////////////////////////////////////

		++runnningTime;

	}
}

void PrintSnakeAreaVisited()
{
	for (int i = 0; i < arrSize; i++)
	{
		for (int j = 0; j < arrSize; j++)
		{
			printf("%d ", snakeArea[j][i].visited);
		}

		cout << endl;
	}

}


int main(void)
{
	// https://www.acmicpc.net/problem/3190
	// 3190�� ����
	// ��
	// Ǫ�� ��

	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	cin >> arrSize;
	cin >> appleSize;

	for (int i = 0; i < appleSize; i++)
	{
		scanf("%d", &apple[i].posY);
		scanf("%d", &apple[i].posX);

		snakeArea[apple[i].posX -1 ][apple[i].posY - 1].isApple = 1; //(0,0) �� ���� �����̶�...
	}

	cin >> cmdSize;

	for (int i = 0; i < cmdSize; i++)
	{
		scanf("%d", &cmd[i].sec);
		cin >> cmd[i].direction;

		cmdQ.push(cmd[i]);
	}

	Snake snake; 
	snake.size = 1;
	snake.direction = Direction::RIGHT;

	MoveSnake(snake, 0, 0);

	printf("%d", runnningTime +1);					//������ �ε��� Ƚ������ �����־�� �ϹǷ� ���⿡�� +1�� ����
	
	return 0;
}