//【分治】棋盘覆盖问题
#include <bits/stdc++.h>
using namespace std;

#define N 1024	 // 棋盘行（列）数
int tile = 0;	 // 骨牌编号
int Board[N][N]; // 棋盘
int k, x, y;
int num = 1;
void ChessBoard(int tr, int tc, int dr, int dc, int size);

int main()
{
	while (cin >> k >> x >> y)
	{
		int size = pow(2, k);
		cout << "Case " << num++ << ":"
			 << "n = " << size << endl;
		ChessBoard(0, 0, x, y, size);
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				cout << Board[i][j] << " ";
			}
			cout << endl;
		}
	}
	system("pause");
	return 0;
}

/*
	tr : 棋盘左上角的行号；
	tc : 棋盘左上角的列号；
	dr : 特殊方格左上角的行号；
	dc : 特殊方格左上角的列号；
	size ：size = 2^k 棋盘规格为2^k*2^k
 */
void ChessBoard(int tr, int tc, int dr, int dc, int size)
{
	if (size == 1)
		return;

	int t = ++tile;	  // L型骨牌编号
	int s = size / 2; // 分割棋盘

	// 覆盖左上角子棋盘
	// 特殊方格在此棋盘中（下面三个if-else同理）
	if (dr < tr + s && dc < tc + s)
		ChessBoard(tr, tc, dr, dc, s);
	// 此棋盘中无特殊方格（下面三个if-else同理）
	else
	{
		Board[tr + s - 1][tc + s - 1] = t;			   // 用编号为t的骨牌覆盖右下角
		ChessBoard(tr, tc, tr + s - 1, tc + s - 1, s); // 覆盖其余方格
	}

	// 覆盖右上角子棋盘
	if (dr < tr + s && dc >= tc + s)
		ChessBoard(tr, tc + s, dr, dc, s);
	else
	{
		Board[tr + s - 1][tc + s] = t;				   // 用编号为t的骨牌覆盖左下角
		ChessBoard(tr, tc + s, tr + s - 1, tc + s, s); // 覆盖其余方格
	}

	// 覆盖左下角子棋盘
	if (dr >= tr + s && dc < tc + s)
		ChessBoard(tr + s, tc, dr, dc, s);
	else
	{
		Board[tr + s][tc + s - 1] = t;				   // 用编号为t的骨牌覆盖右上角
		ChessBoard(tr + s, tc, tr + s, tc + s - 1, s); // 覆盖其余方格
	}

	//覆盖右下角子棋盘
	if (dr >= tr + s && dc >= tc + s)
		ChessBoard(tr + s, tc + s, dr, dc, s);
	else
	{
		Board[tr + s][tc + s] = t;					   // 用编号为t的骨牌覆盖左上角
		ChessBoard(tr + s, tc + s, tr + s, tc + s, s); //覆盖其余方格
	}
}
