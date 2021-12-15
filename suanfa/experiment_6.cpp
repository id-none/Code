/**
 * 【实验6-跳马问题】
 * 给定8*8方格棋盘，求棋盘上一只马从一个位置到达另一位置的最短路径长。
 * 注意马是走“日”形的。
*/
#include<bits/stdc++.h>
using namespace std;

#define pi pair<int,int>
const int N=10;
bool vis[N][N];
int dis[N][N];

int dx[]={1,2,-1,-2,1,2,-1,-2};
int dy[]={2,1,2,1,-2,-1,-2,-1};

struct node
{
    int x,y,dis;
};

int main()
{
    string s,t;
    while(cin>>s>>t)
    {
        memset(vis,0,sizeof(vis));
        int sx=s[0]-'a',sy=s[1]-'1',tx=t[0]-'a',ty=t[1]-'1';
        //BFS
        queue<node> q;
        q.push({sx,sy,0});
        vis[sx][sy]=1;
        while(q.size())
        {
            node cur=q.front(); q.pop();
            dis[cur.x][cur.y]=cur.dis;
            if(cur.x==tx && cur.y==ty) break;   //已找到跳出
            for(int i=0;i<8;i++)
            {
                int vx=cur.x+dx[i],vy=cur.y+dy[i];
                if( !(0<=vx && vx<=7 && 0<=vy && vy<=7) ) continue; //边界判断
                if(vis[vx][vy]) continue;
                vis[vx][vy]=1;
                q.push({vx,vy,cur.dis+1});
            }
        }
        cout<<s<<"==>"<<t<<": "<<dis[tx][ty]<<" moves\n";
    }

    return 0;
}