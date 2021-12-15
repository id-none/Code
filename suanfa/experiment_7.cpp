/**
 * 【实验7-装载问题】
 * 有n个集装箱要装上2艘载重量分别为c1和c2的轮船，
 * 其中第i个集装箱的重量为wi，
 * 要求确定是否有一个合理的装载方案可将这个集装箱装上这2艘轮船。
 * 如果有，找出一种装载方案。
 * 
 * 【要求时间复杂度-O(2^n)】
*/
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int N=50;
ll n,c1,c2,ct;
ll w[N];
ll bestw;
string ans;

void dfs(int p,string &vc,ll s1,ll s2)
{
    if(s1>c1 || s2>c2) return ;
    if(p==n+1)
    {
        if(s1>bestw)        ans=vc,bestw=s1;
        // else if(s1==bestw)  ans=max(ans,vc);
        return ;
    }
    vc+='1'; dfs(p+1,vc,s1+w[p],s2); vc.pop_back();
    vc+='0'; dfs(p+1,vc,s1,s2+w[p]); vc.pop_back();
}

void solve1()   //dfs，O(n2^n)
{
    ans="",bestw=-1;
    string tmp="";
    dfs(1,tmp,0,0);
    if(bestw==-1)   cout<<"No\n";
    else            cout<<bestw<<" "<<ans<<"\n";
}

void solve2()   //状压写法，O(n2^n)
{
    bestw=-1,ans="";
    for(int i=0;i<(1<<n);i++)
    {
        ll s1=0,s2=0;
        string cur="";
        for(int j=0;j<n;j++)
            if(i>>j&1)  s1+=w[j+1], cur+='1';
            else        s2+=w[j+1], cur+='0';
        if(s1>c1 || s2>c2) continue;
        if(s1>bestw)        ans=cur,bestw=s1;
        else if(s1==bestw)  ans=max(ans,cur);
    }
    if(bestw==-1)   cout<<"No\n";
    else            cout<<bestw<<" "<<ans<<"\n";
}

int main()
{
    while(cin>>n)
    {
        for(int i=1;i<=n;i++) cin>>w[i];
        cin>>c1>>c2;
        cout<<"Case "<<++ct<<"\n";
        solve1();
    }

    return 0;
}