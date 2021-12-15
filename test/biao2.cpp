#include <iostream>
#define maxsize 100
using namespace std;
struct ArcNode
{
    int adjvex;              //�ñ���ָ��Ľ��λ��
    struct ArcNode *nextarc; //ָ����һ����ָ��
    int info;                //Ȩֵ
    ArcNode() { adjvex = -1; };
    ArcNode(int v, int w, ArcNode *next)
    {
        adjvex = v;
        info = w;
        nextarc = next;
    };
};
struct VNode
{
    char data; //������Ϣ
    int count;
    ArcNode *firstarc; //ָ���һ���ߵ�ָ��
    VNode() { firstarc = NULL; };
    VNode(char val, ArcNode *adj = NULL)
    {
        data = val;
        firstarc = adj;
    };
};
class AGraph
{
private:
    VNode *adjlist;   //�ڽӱ�
    int *flag;        //��־����
    int vexnum, maxv; //������
    int arcnum;       //����
    int INF;          //����ֵ
public:
    AGraph(int maxnum, int infinit)
    {
        vexnum = 0;
        maxv = maxnum;
        arcnum = 0;
        INF = infinit;
        flag = new int[maxv];
        adjlist = new VNode[maxv];
    };
    AGraph(char es[], int vnum, int vmax, int inifinit)
    {
        vexnum = vnum;
        maxv = vmax;
        INF = inifinit;
        flag = new int[maxv];
        adjlist = new VNode[maxv];
        for (int i = 0; i < vnum; i++)
        {
            flag[i] = 0;
            adjlist[i].data = es[i];
            adjlist[i].firstarc = NULL;
        }
    };
    ~AGraph()
    {
        delete[] flag;
        delete[] adjlist;
    };
    /*int FirstVnum(int v) const //��ĳ��ĵ�һ���ڽӵ����
    { 
        if(adjlist[v].firstarc == NULL) return -1;
        return adjlist[v].firstarc ->adjvex;
    };*/
    void InsertVertex(const char &d) //���붥��d
    {
        if (vexnum >= maxv)
            printf("���������");
        adjlist[vexnum].data = d;
        adjlist[vexnum].firstarc = NULL;
        flag[vexnum] = 0;
        vexnum++;
    };
    void InsertEdge(int v1, int v2, int w) //�����
    {
        if (v1 < 0 || v2 > vexnum)
            printf("���Ϸ�");
        if (v2 < 0 || v2 > vexnum)
            printf("���Ϸ�");
        if (v1 == v2)
            printf("���㲻�����");
        if (w == INF)
            printf("Ȩֵ�������޴�");
        ArcNode *p, *q;
        p = adjlist[v1].firstarc;
        adjlist[v1].firstarc = new ArcNode(v2, w, p);
        arcnum++;
    };
    void DeleteVertex(char &d) //ɾ����
    {
        ArcNode *p, *q;
        int i, j;
        for (i = 0; i < vexnum; i++)
            if (adjlist[i].data == d)
                break;
        for (j = 0; j < vexnum; j++)
            if (j != i)
                DeleteArc(i, j);
        p = adjlist[i].firstarc;
        while (p != NULL)
        {
            adjlist[i].firstarc = p->nextarc;
            delete p;
            p = adjlist[i].firstarc;
            arcnum--;
        }
        vexnum--;
        adjlist[i].data = adjlist[vexnum].data;
        adjlist[i].firstarc = adjlist[vexnum].firstarc;
        adjlist[vexnum].firstarc = NULL;
        flag[i] = flag[vexnum];
        for (int j = 0; j < vexnum; j++)
            if (j != i)
            {
                p = adjlist[j].firstarc;
                while (p != NULL)
                {
                    if (p->adjvex = vexnum)
                        p->adjvex = i;
                    p = p->nextarc;
                }
            }
    };
    void DeleteArc(int v1, int v2) //ɾ����
    {
        if (v1 < 0 || v2 > vexnum)
            printf("���Ϸ�");
        if (v2 < 0 || v2 > vexnum)
            printf("���Ϸ�");
        if (v1 == v2)
            printf("���㲻�����");
        ArcNode *p, *q;
        p = adjlist[v1].firstarc;
        while (p != NULL && p->adjvex != v2)
        {
            q = p;
            p = p->nextarc;
        }
        if (p == NULL)
        {
            if (adjlist[v1].firstarc == p)
                adjlist[v1].firstarc = p->nextarc;
            else
                q->nextarc = p->nextarc;
            delete p;
            arcnum--;
        }
    };
    void Visit(int v)
    {
        cout << adjlist[v].data << "  :";
        ArcNode *p;
        p = adjlist[v].firstarc;
        while (p != NULL)
        {
            /* code */
            cout << "<" << v << "," << p->adjvex << ">"
                 << "   ";
            p = p->nextarc;
        }
        cout << endl;
    }
    void DFS(AGraph &G, int v) //�����������
    {
        ArcNode *p;
        flag[v] = 1;
        //Visit(v);
        p = G.adjlist[v].firstarc;
        while (p != NULL)
        {
            if (flag[p->adjvex] == 0)
                DFS(G, p->adjvex);
            p = p->nextarc;
        }
    };
    void DFS2(AGraph *G, int v, int &vn, int &en)
    {
        ArcNode *p;
        flag[v] = 1;
        ++vn;
        p = G->adjlist[v].firstarc;
        while (p != NULL)
        {
            ++en;
            if (flag[p->adjvex] == 0)
                DFS2(G, p->adjvex, vn, en);
            p = p->nextarc;
        }
    };
    int GisTree(AGraph *G)
    {
        int vn = 0, en = 0, i;
        for (i = 0; i < G->vexnum; ++i)
            flag[i] = 0;
        DFS2(G, 1, vn, en);
        if (vn == G->vexnum && (G->vexnum - 1) == en / 2)
            return 1;
        else
            return 0;
    }
    int topsort(AGraph *G)
    {
        int i, j, n = 0;
        int stack[maxsize], top = -1;
        ArcNode *p;
        for (i = 0; i < G->vexnum; i++)
            if (G->adjlist[i].count == 0)
                stack[++top] = i;
        while (top != -1)
        {
            /* code */
            i = stack[top--];
            ++n;
            cout << i << " ";
            p = G->adjlist[i].firstarc;
            while (p != NULL)
            {
                /* code */
                j = p->adjvex;
                --(G->adjlist[j].count);
                if (G->adjlist[j].count == 0)
                    stack[++top] = j;
                p = p->nextarc;
            }
        }
        if (n == G->vexnum)
            return 1;
        else
            return 0;
    };
    void DFStopsort(AGraph *p)
    {
        int v;
        for (int i = 0; i < p->vexnum; i++)
        {
            flag[i] = 0;
        }
        for (v = 0; v < p->vexnum; ++v)
            if (!flag[v])
            {
                DFS(*p, v);
                cout << v << " ";
            }
    }
};
int main()
{
    char a[5];
    for (int i = 0; i < 5; i++)
        cin >> a[i];
    AGraph A(a, 5, 5, 1234);
    /*A.InsertEdge(1,2,1);
    A.InsertEdge(2,1,1);
    A.InsertEdge(2,3,1);
    A.InsertEdge(3,2,1);
    if(A.GisTree(&A) == 1)
        printf("����");*/
    A.InsertEdge(1, 2, 1);
    A.InsertEdge(3, 2, 1);
    A.DFStopsort(&A);
    system("pause");
    return 0;
}