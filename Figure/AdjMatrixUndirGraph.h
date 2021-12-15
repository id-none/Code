//无向图的邻接矩阵
#include <iostream>
using namespace std;
#define max=1000;
template <class Elemtype>
class AdjMatrixUndirGraph
{   
protected:
    int vexnum;87                 //当前顶点输入
    int arcnum;                 //当前弧属
    Elemtype *vertexes;         //存放点
    Elemtype **arcs;            //邻接矩阵，存放边
public:
    AdjMatrixUndirGraph(Elemtype a[],int vnum,int vertexmaxnum){
        if(vertexmaxnum<0 || vnum > vertexmaxnum) return;
        vexnum=vnum;

    };
};