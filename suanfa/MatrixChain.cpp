#include <bits/stdc++.h>

using namespace std;

void MatrixChain(int, int[], int **, int **);
void print(int, int, int **, int);
void CalculateMin(int i, int j, int p[], int **m, int **s);
int i = 1;
int main()
{
	int n;
	while (cin >> n)
	{
		int *tempP = new int[2 * n]; //p[0]为A1的行数；p[i]为Ai的列数
		int *tp = new int[n + 1];
		int *p = new int[n + 1];	//p[0]为A1的行数；p[i]为Ai的列数
		int **m = new int *[n + 1]; //m[i][j]为Ai连乘到Aj的最少乘次数
		int **s = new int *[n + 1]; //s[i][j]为 Ai连乘到Aj的最优解的第一层断开位置
		for (int i = 1; i <= n; i++)
		{
			m[i] = new int[n + 1];
			s[i] = new int[n + 1];
		}

		for (int i = 0; i < n + 1; i++)
		{
			cin >> tp[i];
		}
		tempP[0] = tp[0];
		for (int i = 1; i < n * 2; i++)
		{
			if (i % 2 != 0)
				tempP[i] = tp[i / 2 + 1];
			else
			{
				tempP[i] = tempP[i - 1];
			}
		}

		for (int i = 0; i <= n; i++)
		{
			p[i] = i == 0 ? tempP[0] : tempP[i * 2 - 1];
		}

		MatrixChain(n, p, m, s);
		cout << "Case " << i++ << endl;
		cout << m[1][n] << " "; //最优值存储在m[1][n]
		print(1, n, s, n);		//打印最优计算方式
		cout << endl;
	}
	system("pause");
	return 0;
}

void MatrixChain(int n, int p[], int **m, int **s)
{
	//以下双重循环对m[][]的上三角进行填表
	//填表顺序为自底向上，自左向右
	for (int i = n; i >= 1; i--) //i表示行
	{
		for (int j = i; j <= n; j++) //j表示列，因为只填上三角，所以j的初值为i
		{
			//以下按照矩阵连乘问题的递归公式来求每一个m[i][j]
			if (i == j)
			{
				m[i][j] = 0;
			}
			else
			{
				CalculateMin(i, j, p, m, s);
			}
		}
	}
}

void CalculateMin(int i, int j, int p[], int **m, int **s)
{
	m[i][j] = m[i][i] + m[i + 1][j] + p[i - 1] * p[i] * p[j]; //若i与j不相等，m[i][j]的初值为断开位置为i时的最优值

	s[i][j] = i;					//记录当前断开位置位置为i
	for (int k = i + 1; k < j; k++) //k用于尝试不同的断开位置
	{
		int curr = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
		if (curr < m[i][j]) //当前k值作为Ai连乘到Aj的断开位置能获得更少计算量
		{
			m[i][j] = curr; //刷新最优值
			s[i][j] = k;	//刷新相应断开位置
		}
	}
}

void print(int i, int j, int **s, int n)
{
	if (i == j)
		cout << "A" << i;
	else if (i == 1 && j == n)
	{
		print(i, s[i][j], s, n);
		print(s[i][j] + 1, j, s, n);
	}
	else
	{
		cout << "(";
		print(i, s[i][j], s, n);
		print(s[i][j] + 1, j, s, n);
		cout << ")";
	}
}