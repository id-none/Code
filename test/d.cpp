#include <bits/stdc++.h>
using namespace std;

template <typename ElemType>
class Matrix
{
private:
    int **G;
    int num,maxsize,m;
    ElemType* tag;
    int GetIndex(ElemType &a) const;
    void init_floyd();
    void toposort(int cnt,int* indegree,int* ans,bool* vis);
    pair<vector<int>,vector<int> > topo();
    int Unique(pair<int,int>* degree,bool* vis);
public:
    Matrix();
    Matrix(int nnum,ElemType* name,int t=0,int nmaxsize=100);
    virtual ~Matrix();
    void traverse() const;
    bool AddEdge(ElemType a, ElemType b, int val);
    bool AddVertex(ElemType a);
    void floyd();
    void dijkstra(ElemType s,int* dis,int *path);
    void topologicalsort();
    void CirticalPath();
    int Prim();
    int BreakCircle();
};

template <typename ElemType>
int Matrix<ElemType>::Unique(pair<int,int>* degree,bool* vis){
    int sum=0;
    for(int i=0;i<num;i++){
        if(!vis[i]&&degree[i].first==1){
            sum+=degree[i].second;
            vis[i] = true;
            for(int k=0;k<num;k++){
                if(G[i][k]!=0x3f3f3f3f){
                    degree[k].first--;
                    degree[k].second-=G[i][k];
                }
            }
        }
    }
    return sum;
}

template <typename ElemType>
int Matrix<ElemType>::BreakCircle(){
    if(m!=0) {cout<<"Error!"<<endl;return -1;}
    int cnt=0,res=0,degree[num+5];
    bool mark[num+5][num+5],vis[num+5];
    memset(mark,0,sizeof(mark));
    memset(degree,0,sizeof(degree));
    memset(vis,0,sizeof(vis));
    for(int i=0;i<num;i++){
        mark[i][i]=true;
        for(int j=0;j<num;j++)
            if(G[i][j]!=0x3f3f3f3f)
                cnt++,degree[i]++;
    }
    cnt/=2;
    if(cnt<num-1) {cout<<"Error! inexist MST"<<endl;return -1;}
    while(cnt>num-1){
        int ii,jj,mx=-1;
        for(int i=0;i<num;i++){
            for(int j=0;j<num;j++){
                if(G[i][j]!=0x3f3f3f3f&&!mark[i][j]&&mx<G[i][j]&&degree[i]!=1&&degree[j]!=1){
                    mx = G[i][j];
                    ii = i,jj = j;
                }
            }
        }
        if(mx==-1) {cout<<"Error!"<<endl;return -1;}
        else{
            cout<<"delete "<<ii<<" "<<jj<<endl;
            cnt--;
            mark[ii][jj] = mark[jj][ii] = true;
            degree[ii]--;degree[jj]--;
        }
    }
    for(int i=0;i<num;i++)
        for(int j=i+1;j<num;j++)
            if(G[i][j]!=0x3f3f3f3f&&!mark[i][j]){
                res+=G[i][j];
            }
    return res;
}

template <typename ElemType>
int Matrix<ElemType>::Prim(){
    bool *vis = new bool[num+5];
    int *dis = new int[num+5];
    int res=0;
    for(int i=0;i<num+5;i++) dis[i] = 0x3f3f3f3f;
    dis[0] = 0;
    for(int i=0;i<num;i++){
        int mi = 0x3f3f3f3f,index = -1;
        for(int j=0;j<num;j++)
            if(!vis[j]&&mi>dis[j])
                mi = dis[j] , index = j;
        vis[index] = true;
        res+=dis[index];
        for(int j=0;j<num;j++)
            if(G[index][j]!=0x3f3f3f3f)
                dis[j] = min(dis[j],G[index][j]);
        
    }
    return res;
}

template <typename ElemType>
pair<vector<int>,vector<int> > Matrix<ElemType>::topo(){
    int in[num+5],out[num+5],mark;
    pair<vector<int>,vector<int> > ans;
    ans.first.clear(),ans.second.clear();
    memset(in,0,sizeof(in));
    memset(out,0,sizeof(out));

    for(int i=0;i<num;i++)
        for(int j=0;j<num;j++)
            if(G[i][j]!=0x3f3f3f3f)
                in[j]++,out[i]++;

    queue<int> q;
    for(int i=0;i<num;i++){
        if(in[i]==0) q.push(i);
        if(out[i]==0) mark=i;
    }

    while(q.size()){
        int now = q.front();
        q.pop();
        ans.first.push_back(now);
        for(int j=0;j<num;j++)
            if(G[now][j]!=0x3f3f3f3f){
                if(--in[j]==0)
                    q.push(j);
            }
    }

    q.push(mark);
    while(q.size()){
        int now = q.front();
        q.pop();
        ans.second.push_back(now);
        for(int i=0;i<num;i++)
            if(G[i][now]!=0x3f3f3f3f){
                if(--out[i]==0)
                    q.push(i);
            }
    }

    return ans;
}

template <typename ElemType>
void Matrix<ElemType>::CirticalPath(){
    int cnt = 0,mark[num+5][num+5];
    pair<vector<int>,vector<int> > array = topo();
    memset(mark,0x3f3f3f3f,sizeof(mark));
    for(int i=0;i<num;i++)
        for(int j=0;j<num;j++)
            if(G[i][j]!=0x3f3f3f3f)
                mark[i][j]=cnt , cnt++;
    
    int *vl = new int[num+5],*ve = new int[num+5];
    int *al = new int[cnt+5],*ae = new int[cnt+5];
    for(int i=0;i<num+5;i++) ve[i] = 0,vl[i]=0x3f3f3f3f;
    for(int i=0;i<cnt+5;i++) al[i] = ae[i] = 0x3f3f3f3f;
    
    for(int i=0;i<num;i++){
        int now = array.first[i];
        for(int j=0;j<num;j++)
            if(G[now][j]!=0x3f3f3f3f){
                ve[j] = max(ve[j],ve[now]+G[now][j]);
            }
    }
    vl[array.second[0]] = ve[array.second[0]];
    for(int i=0;i<num;i++){
        int now = array.second[i];
        for(int j=0;j<num;j++)
            if(G[j][now]!=0x3f3f3f3f){
                vl[j] = min(vl[j],vl[now]-G[j][now]);
            }
    }

    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            if(G[i][j]!=0x3f3f3f3f){
                ae[mark[i][j]] = ve[i];
                al[mark[i][j]] = vl[j] - G[i][j];
                //printf("<%d , %d> al: %d , ae: %d\n",i,j,al[mark[i][j]],ae[mark[i][j]]);
                
                if(al[mark[i][j]]==ae[mark[i][j]])
                    printf("<%d , %d>\n",i,j);
                
            }
        }
    }
    delete[] vl;
    delete[] ve;
    delete[] al;
    delete[] ae;
}

template <typename ElemType>
void Matrix<ElemType>::toposort(int cnt,int* indegree,int* ans,bool* vis){
    if(cnt==num){
        for(int i=0;i<num;i++){
            cout<<tag[ans[i]]<<" ";
        }cout<<endl;
    }
    else{
        for(int i=0;i<num;i++){
            if(!vis[i]&&indegree[i]==0){
                for(int j=0;j<num;j++){
                    if(G[i][j]!=0x3f3f3f3f){
                        indegree[j]--;
                    }
                }
                vis[i]=true;
                ans[cnt]=i;
                toposort(cnt+1,indegree,ans,vis);
                vis[i]=false;
                for(int j=0;j<num;j++){
                    if(G[i][j]!=0x3f3f3f3f){
                        indegree[j]++;
                    }
                }
            }
        }
    }
}

template <typename ElemType>
void Matrix<ElemType>::topologicalsort(){
    if(m!=1) {cout<<"Error!"<<endl;return ;}
    int *indegree = new int[num+10],*ans = new int[num+10];
    bool *vis = new bool[num+10];
    for(int i=0;i<num;i++) vis[i] = false,indegree[i]=0;
    for(int j=0;j<num;j++){
        for(int i=0;i<num;i++)
            if(G[i][j]!=0x3f3f3f3f)
                indegree[j]++;
    }

    toposort(0,indegree,ans,vis);

    delete [] vis;
    delete [] indegree;
    delete [] ans;
}

template <typename ElemType>
Matrix<ElemType>::~Matrix(){
    if(G!=nullptr){
        for(int i=0;i<maxsize;i++)
            delete[] G[i];
        delete[] G;
    }
    if(tag!=nullptr)
        delete[] tag;
}

template <typename ElemType>
void Matrix<ElemType>::dijkstra(ElemType s,int* dis,int *path){
    for(int i=0;i<num;i++) dis[i] = 0x3f3f3f3f,path[i]=-1;
    bool *vis = new bool[num+10];
    memset(vis,0,sizeof(vis));
    int index_s = GetIndex(s);
    priority_queue<pair<int,int> ,vector<pair<int,int> > ,greater<pair<int,int> > > q;

    q.push({0,index_s});
    dis[index_s] = 0;
    while(q.size()){
        pair<int,int> now = q.top();
        q.pop();
        if(vis[now.second]) continue;
        vis[now.second] = true;
        for(int i=0;i<num;i++){
            if(dis[i]>dis[now.second]+G[now.second][i]){
                dis[i] = dis[now.second]+G[now.second][i];
                path[i] = now.second;
                q.push({dis[i],i});
            }
        }
        cout<<"vis ";
        for(int i=0;i<num;i++)
            cout<<setw(4)<<vis[i]<<" ";
        cout<<endl<<"dis ";
        for(int i=0;i<num;i++)
            if(dis[i]==0x3f3f3f3f) cout<<setw(4)<<" inf ";
            else cout<<setw(4)<<dis[i]<<" ";
        cout<<endl<<"path";
        for(int i=0;i<num;i++)
            cout<<setw(4)<<path[i]<<" ";
        cout<<endl<<endl;
    }

    delete [] vis;
}

template <typename ElemType>
void Matrix<ElemType>::init_floyd(){
    for(int i=0;i<num;i++) G[i][i] = 0;
}

template <typename ElemType>
void Matrix<ElemType>::floyd(){
    init_floyd();
    for(int k=0;k<num;k++)
        for(int i=0;i<num;i++)
            for(int j=0;j<num;j++)
                if(G[i][j] < G[i][k]+G[k][j])
                    G[i][j] = G[i][k]+G[k][j];
}

template <typename ElemType>
bool Matrix<ElemType>::AddVertex(ElemType a){
    if(num==maxsize) return false;
    tag[num++] = a;
    for(int i=0;i<num;i++){
        G[num-1][i] = 0x3f3f3f3f;
    }
    for(int j=0;j<num;j++){
        G[j][num-1] = 0x3f3f3f3f;
    }
    return true;
}

template <typename ElemType>
bool Matrix<ElemType>::AddEdge(ElemType a, ElemType b,int val){
    int tag_a = GetIndex(a),tag_b = GetIndex(b);
    if(tag_a==-1||tag_b==-1) return false;
    if(m==0) G[tag_a][tag_b] = G[tag_b][tag_a] = val;
    else G[tag_a][tag_b] = val;
    return true;
}

template <typename ElemType>
int Matrix<ElemType>::GetIndex(ElemType &a) const{
    for(int i=0;i<num;i++){
        if(tag[i]==a)
            return i;
    }
    return -1;
}

template <typename ElemType>
void Matrix<ElemType>::traverse() const{
    for(int i=0;i<num;i++,cout<<"\n"){
        cout<<tag[i]<<" ";
        for(int j=0;j<num;j++)
            G[i][j]>=0x3f3f3f3f?cout<<"INF " : cout<<G[i][j]<<" ";
    }
}

template <typename ElemType>
Matrix<ElemType>::Matrix(){
    num = m = 0;
    maxsize = 100;
    tag = new ElemType[maxsize];
    G = new int*[maxsize];
    for(int i=0;i<maxsize;i++)
        G[i] = new int[maxsize];
}

template <typename ElemType>
Matrix<ElemType>::Matrix(int nnum,ElemType* name,int t,int nmaxsize){
    num = nnum>0 ? nnum : 0;
    maxsize = nmaxsize>0 ? nmaxsize : 0;
    m = t;
    tag = new ElemType[maxsize];
    G = new int*[maxsize];
    for(int i=0;i<maxsize;i++)
        G[i] = new int[maxsize];
    for(int i=0;i<num;i++)
        tag[i] = name[i];
    for(int i=0;i<maxsize;i++){
        for(int j=0;j<maxsize;j++){
            G[i][j] = 0x3f3f3f3f;
        }
    }
}

void test01(){//topologicalsort
    int s[7] = {0,1,2,3,4,5};
    Matrix<int> g(6,s,1);
    g.AddEdge(1,0,1);
    g.AddEdge(1,4,1);
    g.AddEdge(0,2,1);
    g.AddEdge(0,3,1);
    g.AddEdge(2,3,1);
    g.AddEdge(4,0,1);
    g.AddEdge(5,2,1);
    g.AddEdge(5,3,1);
    g.AddEdge(5,4,1);
    g.topologicalsort();
}

void test02(){//AOE
    int s[7] = {0,1,2,3,4,5,6};
    Matrix<int> g(7,s,1);
    g.AddEdge(0,1,8);g.AddEdge(0,4,5);g.AddEdge(0,3,4);
    g.AddEdge(3,4,1);
    g.AddEdge(4,1,2);g.AddEdge(4,2,7);g.AddEdge(4,5,2);
    g.AddEdge(1,2,3);
    g.AddEdge(5,2,3);g.AddEdge(5,6,9);
    g.AddEdge(2,6,6);
    g.CirticalPath();
}

void test03(){//10
    int s[7] = {0,1,2,3};
    Matrix<int> g(4,s,0);
    g.AddEdge(0,1,1);g.AddEdge(0,2,1);g.AddEdge(0,3,1);
    g.AddEdge(1,2,2);g.AddEdge(1,3,3);g.AddEdge(2,3,4);
    int res=g.BreakCircle();
    cout<<res<<endl;
}

/*----------------------------------------------------------------
int s[7] = {0,1,2,3};
    Matrix<int> g(4,s,0);
    g.AddEdge(0,1,1);g.AddEdge(0,2,1);g.AddEdge(0,3,1);
    g.AddEdge(1,2,2);g.AddEdge(1,3,3);g.AddEdge(2,3,4);
-----------------------------------------------------------------*/

void test04(){
    int s[6] = {0,1,2,3,4,5};
    Matrix<int> g(6,s,1);
    g.AddEdge(0,1,45);g.AddEdge(0,2,50);g.AddEdge(0,3,15);
    g.AddEdge(1,2,5);g.AddEdge(1,4,20);g.AddEdge(1,5,15);
    g.AddEdge(3,0,10);g.AddEdge(3,1,10);g.AddEdge(3,4,79);
    g.AddEdge(4,1,30);g.AddEdge(5,4,20);
    int path[6],dis[6];
    g.dijkstra(0,dis,path);
}

/*
int s[6] = {0,1,2,3,4,5};
    Matrix<int> g(6,s,1);
    g.AddEdge(0,1,45);g.AddEdge(0,2,50);g.AddEdge(0,3,15);
    g.AddEdge(1,2,5);g.AddEdge(1,4,20);g.AddEdge(1,5,15);
    g.AddEdge(3,0,10);g.AddEdge(3,1,10);g.AddEdge(3,4,79);
    g.AddEdge(4,1,30);g.AddEdge(5,4,20);
    int path[6],dis[6];
*/

int main(){
    test04();
    system("PAUSE");
    return 0;
}