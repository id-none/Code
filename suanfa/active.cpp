#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (__typeof(b) i = a; i <= (b); i++)
/*struct act
{
    int l, r;
    bool vis = 0;
    friend bool operator<(act a, act b)
    {
        return a.r < b.r;
    }
};*/

int active[20], bacitve[20];
//int n;

int slove();
int main()
{
    int n;
    scanf("%d", &n);
    rep(i, 1, n) scanf("%d %d", active + i, bacitve + i);
    sort(active + 1, active + n + 1);
    sort(bacitve + 1, bacitve + n + 1);
    int j = 1;
    int ans = 0;
    rep(i, 1, n)
    {
        if (active[i] < bacitve[j])
            ans++;
        else
            j++;
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}

/*int solve()
{
    int res = n, ret = 0;
    while (1)
    {
        rep(i, 1, n) cout << active[i].vis << ' ';
        cout << endl;
        bool f = 0;
        int last = -1;
        rep(i, 1, n)
        {
            if (!active[i].vis && active[i].l > last)
            {
                last = active[i].r;
                active[i].vis = 1;
                f = 1;
            }
        }
        if (!f)
            break;
        ret++;
    }
    return ret;
}*/