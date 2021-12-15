#include <bits/stdc++.h>
//#include <algorithm>
using namespace std;
struct task
{
    int t; //任务时间
    int d; //截止时间
    int w; //惩罚时间
};
bool cmp(task x, task y)
{
    return x.d < y.d;
}
int main()
{
    int n;
    cin >> n; //输入任务个数
    task a[n + 1];
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i].t >> a[i].w;
        a[i].d = a[i].t + 1;
    }
    sort(a + 1, a + n + 1, cmp); //按照截止时间非减排序
    int p[n + 1][n + 1];
    /*处理第一个任务*/
    for (int i = 0; i <= a[n].d; i++)
    {
        if (i < a[1].t)
            p[1][i] = a[1].w; //罚
        else
            p[1][i] = 0; //做第一个任务
    }
    /*处理第2~n个任务*/
    for (int i = 2; i <= n; ++i)
        for (int j = 0; j <= a[n].d; ++j)
        {
            int x = p[i - 1][j] + a[i].w;
            int y = p[i - 1][min(j, a[i].d) - a[i].t];
            if (j < a[i].t)
            {
                p[i][j] = x; //当前任务无法做
                //cout << x;
            }
            else
            {
                p[i][j] = min(x, y); //可做可不做，选最优
            }
        }
    cout << p[n][a[n].d] << endl;
    system("pause");
    return 0;
}
/*
7
4 70
2 60
4 50
3 40
1 30
4 20
6 80
*/