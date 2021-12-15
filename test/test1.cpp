#include<bits/stdc++.h>

using namespace std;

#define N 100050
#define INF 0x3f3f3f3f

typedef long long LL;

LL n, m, dp[2][N], a[N], Max, ans, k = 0;

int main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1;i <= n;i++) scanf("%lld", &a[i]);
    for (int i = 1;i <= m;i++) {
        k = k ^ 1;
        dp[k][i] = dp[k ^ 1][i - 1] + a[i];
        Max = dp[k ^ 1][i - 1];
        ans = dp[k][i];
        for (int j = i + 1;j <= n;j++) {
            Max = max(Max, dp[k ^ 1][j - 1]);
            dp[k][j] = max(max(Max + a[j], dp[k][j - 1] + a[j]), 0LL);
            ans = max(dp[k][j], ans);
        }
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}