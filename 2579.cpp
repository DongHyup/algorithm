#include <stdio.h>
#include <iostream>

using namespace std;

int cache[10001] = { 0, };
int stair[10001] = { 0, };


// ���� 0�� => cache[n-1]
// �ѹ��� ���ӵȰ� ���� ������, ������ �ö�°ű��� ����
// ���� 1�� => cache[n-2] + stair[n]
// ������ �ö� ����� �ö�ͼ��� �ȵ�, �׸��� �� �������� �������
// ���� 2�� => cache[n-3] + stair[n-1] + stair[n]
// ���� 2���̱� ������, �� ������ �ö�°Ŷ� ���� ����� ������ �ö󰡾ߵǰ� �� �������� �ö�ͼ��� �ȵ�. �������� �������

int main(void)
{

	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	int T;
	cin >> T;

	for (int i = 1; i <= T; i++)
		scanf("%d", &stair[i]);

	cache[1] = stair[1];
	cache[2] = stair[1] + stair[2];

	for (int i = 3; i <= T; i++)
	{

		if (cache[i] < cache[i - 2] + stair[i])
			cache[i] = cache[i - 2] + stair[i];
		if (cache[i] < cache[i - 3] + stair[i] + stair[i - 1])
			cache[i] = cache[i - 3] + stair[i] + stair[i - 1];

	}


	printf("%d", cache[T]);


	return 0;
}
