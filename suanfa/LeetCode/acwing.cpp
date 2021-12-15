#include <bits/stdc++.h>
#include <math.h>
using namespace std;

void zero_one_bag()
{
    int N, V;
    cin >> N >> V;
    vector<int> v, w;
    vector<vector<int>> f;
    w.clear();
    v.clear();
    f.clear();
    v.push_back(0);
    w.push_back(0);
    for (int i = 0; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        v.push_back(a);
        w.push_back(b);
    }
    for (int i = 0; i <= N; i++)
    {
        vector<int> buff(V + 1, 0);
        f.push_back(buff);
    }
    for (int i = 1; i <= N; i++)
    {
        for (int j = V; j > 0; j++)
        {
            if (j > v[i])
            {
                f[i][j] = max(f[i - 1][j], f[i - 1][j - v[i]] + w[i]);
            }
            else
            {
                f[i][j] = f[i-1][j];
            }
        }
    }
    cout << f[N][V];
}

int main()
{
    zero_one_bag();
    system("pause");
    return 0;
}