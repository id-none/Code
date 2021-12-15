/**
 * 【实验5-Dijkstra算法】
 * 对给定的一个（无向）图G，及G中的两点s、t，确定一条从s到t的最短路径。
 * 
 * 要求：
 * 1.如果从顶点s到顶点t有不止一条最短路径，那么输出路段数最少者；
 * 2.如果具有最短路径并且路段数也是最少的路径至少有2条，
 *   那么输出按顶点编号的字典序最小者。
 * 
*/
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const ll N=100,inf=1e18;
ll g[N][N],fa[N];
ll n,ct;
ll s,t;

struct node //三关键字比较，优先级： dis > seg > id
{
    ll dis,seg,id;  //距离；路段数；字典序
    bool operator<(const node & a) const
    {
        if(dis==a.dis)
        {
            if(seg==a.seg) return id<a.id;
            return seg<a.seg;
        }
        return dis<a.dis;
    }
    bool operator>(const node & a) const
    {
        if(dis==a.dis)
        {
            if(seg==a.seg) return id>a.id;
            return seg>a.seg;
        }
        return dis>a.dis; 
    }
};


void dfs(ll u)
{
    if(fa[u]!=s) dfs(fa[u]);
    cout<<fa[u]<<"->";
    if(u==t) cout<<t<<"\n";
}

int main()
{
    while(cin>>n)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                cin>>g[i][j];

        cout<<"Case "<<(++ct)<<"\n";

        cin>>s>>t;
        //初始化
        vector<bool> vis(n+10,0);
        vector<node> dis(n+10);
        for(int i=1;i<=n;i++) dis[i]={inf,inf,i};
        memset(fa,0,sizeof(fa));
        //Dijkstra
        priority_queue<node,vector<node>,greater<node>> q;
        dis[s]={0,0,s};
        q.push(dis[s]);
        while(q.size())
        {
            auto p=q.top(); q.pop();
            ll u=p.id,w=p.dis;
            vis[u]=1;
            for(int v=1;v<=n;v++)
            {
                if(vis[v] || g[u][v]==-1) continue;
                node to = {w+g[u][v],p.seg+1,v};
                if(to < dis[v])     //重载了node的比较运算符
                    dis[v]=to,q.push(to),fa[v]=u;
            }
        }

        cout<<"The least distance from "<<s<<"->"<<t<<" is ";
        if(dis[t].dis==inf) cout<<"-1\n";
        else
        {
            cout<<dis[t].dis<<"\n";
            cout<<"the path is ", dfs(t);
        }
    }    
    system("pause");
    return 0;
}

/*
5
-1 10  -1 30 100
-1 -1 50 -1  -1
-1 -1 -1 -1 10
-1 -1 20 -1 60
-1 -1 -1 -1 -1
1 5

6
-1 1 12 -1 -1 -1
-1 -1 9 3 -1 -1
-1 -1 -1 -1 5 -1
-1 -1 4 -1 13 13
-1 -1 -1 -1 -1 4
-1 -1 -1 -1 -1 -1
1 6

*/