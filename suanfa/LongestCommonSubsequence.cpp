#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> table; // 动态规划表
vector<vector<int>> table2;
set<string> setOfLCS; // set保存所有的LCS
int max(int, int);
string Reverse(string);
int lcs(string, string);
void traceBack(int, int, string, string, string);

int main()
{
	int nums;
	cin >> nums;
	int i = 0;
	while (nums--)
	{
		setOfLCS.clear();
		string X = "", Y = "";
		int m;
		int n;
		cin >> m >> n;
		char c;
		for (int i = 0; i < m; i++)
		{
			cin >> c;
			X += c;
		}
		for (int i = 0; i < n; i++)
		{
			cin >> c;
			Y += c;
		}
		int length = lcs(X, Y);
		cout << "Case " << ++i << endl;
		cout << length << "\n LCS(X,Y): " << endl;
		string str;
		traceBack(m, n, str, X, Y);

		set<string>::iterator beg = setOfLCS.begin();
		for (; beg != setOfLCS.end(); ++beg)
			cout << *beg << endl;
		getchar();

		for (int i = 0; i < m + 1; i++)
		{
			for (int j = 0; j < n + 1; j++)
			{
				cout << table[i][j] << " ";
			}
			cout << endl;
		}
		cout << "\n\n\n\n"
			 << endl;
		for (int i = 0; i < m + 1; i++)
		{
			for (int j = 0; j < n + 1; j++)
			{
				cout << table2[i][j] << " ";
			}
			cout << endl;
		}
	}
	system("pause");
	return 0;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

/** 
 * 字符串逆序
 */
string Reverse(string str)
{
	int low = 0;
	int high = str.length() - 1;
	while (low < high)
	{
		char temp = str[low];
		str[low] = str[high];
		str[high] = temp;
		++low;
		--high;
	}
	return str;
}

/** 
 * 构造表，并返回X和Y的LCS的长度
 */
int lcs(string X, string Y)
{
	// 表的大小为(m+1)*(n+1)
	int m = X.length();
	int n = Y.length();
	table = vector<vector<int>>(m + 1, vector<int>(n + 1));
	table2 = vector<vector<int>>(m + 1, vector<int>(n + 1));
	for (int i = 0; i < m + 1; ++i)
	{
		for (int j = 0; j < n + 1; ++j)
		{
			// 第一行和第一列置0
			if (i == 0 || j == 0)
				table[i][j] = 0;

			else if (X[i - 1] == Y[j - 1])
			{
				table[i][j] = table[i - 1][j - 1] + 1;
				table2[i][j] = 1;
			}

			else if (table[i - 1][j] > table[i][j - 1])
			{
				table[i][j] = table[i - 1][j];
				table2[i][j] = 2;
			}
			else if (table[i - 1][j] == table[i][j - 1])
			{
				table[i][j] = table[i - 1][j];
				table2[i][j] = 4;
			}
			else
			{
				table[i][j] = table[i][j - 1];
				table2[i][j] = 3;
			}
		}
	}

	return table[m][n];
}

/** 
 * 求出所有的最长公共子序列，并放入set中 
 */
void traceBack(int i, int j, string lcs_str, string X, string Y)
{
	while (i > 0 && j > 0)
	{
		if (X[i - 1] == Y[j - 1])
		{
			lcs_str.push_back(X[i - 1]);
			--i;
			--j;
		}
		else
		{
			if (table[i - 1][j] > table[i][j - 1])
				--i;
			else if (table[i - 1][j] < table[i][j - 1])
				--j;
			else // 相等的情况
			{
				traceBack(i - 1, j, lcs_str, X, Y);
				traceBack(i, j - 1, lcs_str, X, Y);
				return;
			}
		}
	}

	setOfLCS.insert(Reverse(lcs_str));
}