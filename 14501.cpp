#include<stdio.h>
#include<iostream>
#include<string>

using namespace std;
#define ARR_MAX 15+1
#define TERM_MAX 5+1
#define PROFIT_MAX 1000

int arr[ARR_MAX][TERM_MAX] = { 0, };
int N = 0;
int res = 0;
//(1 �� Ti �� 5, 1 �� Pi �� 1, 000)

int max(int res, int cur_res) {
	if (cur_res > res)
		return cur_res;
	else
		return res;
}

int _term(int n) {
	//���� �ε����� ����� �ִ� �� Ž�� �� 
	for (int i = 1;i <= TERM_MAX;i++)
	{
		int term = 0;
		//����� ������ ������ �ϳ��� �ִ�
		if (arr[n][i] > 0)
			return i;
	}
	return 0;
}

void dfs(int n, int term, int profit) {
	profit += arr[n][term];
	res = max(res, profit);
	int cur_n = n + term;
	for (int i = cur_n;i <= N;i++)
	{
		int term = _term(i);
		if (i == N && term == 1)
		{
			//������ ��¥�� �ɷ��� ��, �Ⱓ�� 1�̶��
			//�������� �����Ѵ�.
			profit += arr[i][term];
			res = max(res, profit);
			return;
		}

		//���� ��찡 ������ �Ѿ��
		if (i >= N)
			return;
		//term�� 1�� �ƴ� ���, i�� �����ϱ⿡, 
		//term�� 1�� �ƴϸ� N+1�� ������ �������� �ʴ´�. 
		if (i + term > N + 1)
			return;

		dfs(i, term, profit);
	}
}

int main() {

	freopen("test_case/4.txt", "r", stdin);
	scanf("%d", &N);

	for (int i = 1;i <= N;i++) {
		int term, profit;
		scanf("%d%d", &term, &profit);
		arr[i][term] = profit; //True
	}

	dfs(1, 0, 0);
	printf("%d", res);
}