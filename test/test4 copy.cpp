#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ms(a,b) memset(a,b,sizeof(a))
#define INF 0x7f7f7f7f
const int maxn=1e3+10;
const int mod=1e9+7;
using namespace std;
char ch[maxn];
// dp[i][j]表示第i个单词末尾放到位置j的最小难看程度
int dp[maxn][maxn];
int len[maxn];
int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    int cnt=0;
    while(cin>>ch)
        len[++cnt]=strlen(ch);
    ms(dp,INF);
    dp[1][n]=500;
    dp[1][len[1]]=0;
    for(int i=2;i<=cnt;i++)
        for(int j=len[i];j<=n;j++)
        {
            int res=j-len[i];
            // 如果是某行的第一个单词，继承上一行的最后一个状态
            if(!res)
                dp[i][j]=dp[i-1][n];
            else
            {
                if(j==n)
                    dp[i][j]=dp[i-1][j]+500;
                for(int k=0;k<res;k++)
                    dp[i][j]=min(dp[i][j],dp[i-1][k]+(res-k-1)*(res-k-1));
            }
        }
    cout<<"Minimal badness is "<<dp[cnt][n]<<"."<<endl;
    return 0;
}
