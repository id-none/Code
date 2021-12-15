#include<iostream>
enum Tags { UNVISITED, VISITED };//数据访问
enum StatuS {FAIL, SUCCESSED};//执行成功
//边
template<class W> struct AdjListNetworkArc {
    int adjVex;
    int father;
    W weight;
    AdjListNetworkArc<W>* nextarc;
    AdjListNetworkArc<W>() { adjVex = -1; };
    AdjListNetworkArc<W>(int v, W w, AdjListNetworkArc* next = NULL) { adjVex = v; weight = w; nextarc = next; };

};
//结点
template<class E, class W> struct AdjListNetworkVex
{
    E data;
    AdjListNetworkArc<W>* firstarc;
    AdjListNetworkVex<E, W>() { firstarc = NULL; };
    AdjListNetworkVex<E,W>(E d, AdjListNetworkArc<W>* adj) { data = d; firstarc = adj; };
};


template<class E,class W>
class AdjListDirNetwork {
protected:
    int vexNum, vexMaxNum, arcNum;//顶点数，允许的最大顶点数目，弧数。
    AdjListNetworkVex<E, W>* vexTable;//顶点表
    int * tag;
    W infinity;
public:
    AdjListDirNetwork<E, W>(int vmn, W i) {
        if (vexMaxNum < 0)
            throw "不能为负数！";
        vexNum = 0; vexMaxNum = vmn;
        arcNum = 0;
        infinity = i;
        tag = new int[vmn];
        vexTable =new AdjListNetworkVex<E, W>[vexMaxNum];
    }
    AdjListDirNetwork<E, W>(E *ex, int vn, int vmn, W i) {//
        if (vmn < 0) throw "非负！";
        if (vn > vmn) throw "越界！";
        vexNum = vn;
        vexMaxNum = vmn;
        arcNum = 0;
        infinity = i;
        tag = new int[vmn];
        vexTable = new AdjListNetworkVex<E, W>[vmn];
        for (int v = 0; v < vn; v++) {
            tag[v] = UNVISITED;
            vexTable[v].data = ex[v];
            vexTable[v].firstarc = NULL;

        }
    }
    void PrintTu()const {
        for (int j = 0; j < vexNum; j++) {
            std::cout << vexTable[j].data << ' ' << tag[j] << '\t';
            for (AdjListNetworkArc<int>* arc = vexTable[j].firstarc; arc != NULL; arc = arc->nextarc) {
                std::cout << '['<<arc->adjVex<<','<<arc->weight << ']'<<"->";
            }
            std::cout<<"NULL"<< std::endl;
        }
    }
    int FindE(E A) {
        int index_A = 0;
        for (; index_A < vexNum && vexTable[index_A].data != A; index_A++);
        return index_A;
    }
    void ResetTag() {
        for (int j = 0; j < vexNum; j++) {
            tag[j] = UNVISITED;
        }
    }
    StatuS MatchAToB_ByIndex(int index_A, int index_B) {
        //把A连上B
        AdjListNetworkArc<int>* newarc_a = new AdjListNetworkArc<int>(index_B, -1, NULL);
        if (vexTable[index_A].firstarc == NULL) {
            vexTable[index_A].firstarc = newarc_a;
        }
        else if (vexTable[index_A].firstarc != NULL) {
            AdjListNetworkArc<int>* arc = vexTable[index_A].firstarc;
            for (; arc->nextarc != NULL; arc = arc->nextarc);
            arc->nextarc = newarc_a;
        }
        return SUCCESSED;
    }
    StatuS MatchAToB_ByIndex_plus(int index_A, int index_B,int destence) {
        //把A连上B
        AdjListNetworkArc<int>* newarc_a = new AdjListNetworkArc<int>(index_B, destence, NULL);
        if (vexTable[index_A].firstarc == NULL) {//如果没有边
            newarc_a->father = index_A;
            vexTable[index_A].firstarc = newarc_a;
        }
        else if (vexTable[index_A].firstarc != NULL) {
            AdjListNetworkArc<int>* arc = vexTable[index_A].firstarc;
            for (; arc->nextarc != NULL; arc = arc->nextarc);
            arc->nextarc = newarc_a;
            arc->father = index_A;
        }

        return SUCCESSED;
    }
    StatuS MatchAWithB(E A,E B) {
        int index_A=FindE(A),index_B=FindE(B);

        //把A连上B
        MatchAToB_ByIndex(index_A, index_B);
        //把B连上A
        MatchAToB_ByIndex(index_B, index_A);
        //printf("%d,%d\n", index_A, index_B);
        return SUCCESSED;
    }
    StatuS MatchAWithB_plus(E A, E B,int destence) {
        int index_A = FindE(A), index_B = FindE(B);

        //把A连上B
        MatchAToB_ByIndex_plus(index_A, index_B,destence);
        //把B连上A
        MatchAToB_ByIndex_plus(index_B, index_A,destence);
        //printf("%d,%d\n", index_A, index_B);
        return SUCCESSED;
    }



    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    StatuS AtoB(E A, E B) {
        int index_A = FindE(A), index_B = FindE(B);
        AdjListNetworkArc<W>* j = vexTable[index_A].firstarc;
        for (; j != NULL; j = j->nextarc) {
            if (index_B == j->adjVex) {
                j->father = index_A;
                break;
            }
        }
        return SUCCESSED;
    }
    StatuS DeleteAToB(E A, E B) {
        int index_A = FindE(A), index_B = FindE(B);
        AdjListNetworkArc<int>* arc = vexTable[index_A].firstarc;
        if (arc->adjVex == index_B) {
            if (arc->nextarc == NULL) {
                delete arc;
                vexTable[index_A].firstarc = NULL;
            }
            else {
                AdjListNetworkArc<int>* delearc = arc;
                vexTable[index_A].firstarc = arc->nextarc;
                delete delearc;
            }
            return SUCCESSED;
        }
        for (; arc->nextarc->adjVex != index_B; arc = arc->nextarc);//只要下一条不AB的那条边一直找
        AdjListNetworkArc<int>* delearc = arc->nextarc;
        arc->nextarc = arc->nextarc->nextarc;
        delete delearc;
        return SUCCESSED;
    }
    StatuS DeleteAwithB(E A, E B) {
        DeleteAToB(A, B);
        DeleteAToB(B, A);
        return SUCCESSED;
    }
    //题1：判断两个顶点之间是否存在路径
    bool Is_A_to_B_OK(E A, E B) {
        int index_A = FindE(A), index_B = FindE(B);
        tag[index_A] = VISITED;
        for (AdjListNetworkArc<W>* i = vexTable[index_A].firstarc; i != NULL; i = i->nextarc) {
            if (i->adjVex == index_B) {
                return true;
            }
            else if (i->adjVex != index_B && tag[i->adjVex] == UNVISITED) {
                if (Is_A_to_B_OK(vexTable[i->adjVex].data, B)) {
                    return true;
                }
            }
        }
        return false;
    }
    bool Is_A_to_B_Both_OK(E A, E B)
    {
        if (Is_A_to_B_OK(A, B)|| Is_A_to_B_OK(B, A))
            return true;
    }
    //题2：求两顶点间所有简单路径
    void The_Way_A_To_B_All(E A,E B)
    {

        int* Stack = new int[vexNum];
        int index = 0;
        The_Way_A_To_B_All_dg(A, B, Stack,index);

    }
    void The_Way_A_To_B_All_dg(E Current, E B,int* &S,int &index) {
        int index_Current =0,index_B=0;
        index_Current = FindE(Current);
        index_B= FindE(B);

        tag[index_Current] = VISITED;//标记访问过了
        S[index++] = index_Current;

        if (index_Current == index_B) {
            for (int i = index-1; i>=0; i--) {
                std::cout << S[i];
            }
            std::cout << std::endl;
            index--;
            tag[index_Current] = UNVISITED;
            return;
        }
        for (AdjListNetworkArc<W>* i = vexTable[index_Current].firstarc; i != NULL; i = i->nextarc) {
            if (tag[i->adjVex] == VISITED)continue;
            The_Way_A_To_B_All_dg(vexTable[i->adjVex].data, B, S, index);
        }
        index--;
        tag[index_Current] = UNVISITED;
    }

    //题3prim算法
    bool tag_all_visit() {
        int i;
        for (i = 0; i < vexNum; i++);
        if (i == vexNum)
            return true;
        return false;
    }
    AdjListNetworkArc<W> GetMiniArc(AdjListDirNetwork<E, W> Tu) {
        AdjListNetworkArc<W> arcFlag;
        arcFlag.weight = -1;
        for (int i = 0; i < Tu.vexNum; i++) {
            for (AdjListNetworkArc<W>* j = vexTable[i].firstarc;j!=NULL&&j->nextarc!=NULL; j = j->nextarc) {
                if (arcFlag.weight == -1 || arcFlag.weight > j->weight) {
                    arcFlag.adjVex = j->adjVex;
                    arcFlag.weight = j->weight;
                    arcFlag.father = j->father;
                }
            }
        }
        std::cout << arcFlag.father << std::endl;
        return arcFlag;
    }


    AdjListDirNetwork<E, W> Prim(AdjListDirNetwork<E, W> Tu) {
        AdjListDirNetwork<char, int> smallTree(Tu.vexMaxNum, 1);//最小生成树的图

        for (int k = 0; k < Tu.vexNum; k++) { //将点放入标志图中
            smallTree.vexTable[k].data= Tu.vexTable[k].data;
            smallTree.vexTable[k].firstarc = NULL;
            smallTree.tag[k] = UNVISITED;
            smallTree.vexNum++;
        }
        int temp1[100];
        int temp2[100];
        int temp3[100];
        int index = 0;

        int noww = 0;
        for (int i = 0; i < Tu.vexNum; i++) {
            if(smallTree.tag[i]==VISITED)continue;
            smallTree.tag[i] = VISITED;
            for (AdjListNetworkArc<W>* j = vexTable[i].firstarc; j != NULL && j->nextarc != NULL; j = j->nextarc) {
                temp1[index] = i;
                temp2[index] = j->adjVex;
                temp3[index] = j->weight;
                index++;
            }//能到达的边全部入堆
            int flag1 = temp1[0];
            int flag2 = temp2[0];
            int flag3 = temp3[0];
            int index_flag=0;
            for (int j = 0; j < index; j++) {
                if (flag3 > temp3[j]) {
                    flag1 = temp1[j];flag2 = temp2[j];flag3 = temp3[j];index_flag = j;
                }
            }//flag123为最短边
            if (smallTree.tag[flag2] == VISITED)
            {
                temp3[index_flag] = 1000000;
            }
            else {
                smallTree.MatchAWithB_plus(vexTable[flag1].data, vexTable[flag2].data, flag3);
                temp3[index_flag] = 1000000;
            }


        }
        smallTree.PrintTu();
        return smallTree;
    }

    AdjListDirNetwork<E, W>& operator = (const AdjListDirNetwork<E, W>& copy) {
        if (&copy != this) {
            vexMaxNum = copy.vexMaxNum;
            vexNum = copy.vexNum;
            arcNum = copy.arcNum;
            for (int i = 0; i < vexNum; i++) {
                tag[i] = copy.tag[i];
                vexTable[i] = copy.vexTable[i];
            }
        }
        return *this;
    }
};

//void dfs(int now, int t, stack<int>& st) {
//	vis[now] = true;
//	st.push(now);
//	if (now == t) {
//		print();
//		st.pop();
//		vis[t] = 0;
//		return ;
//	}
//	for (int i = 0; i < G[now].size(); i++) {
//		int nx = G[now][i];
//		if (vis[nx]) continue;
//		dfs(nx, t, st);
//	}
//	st.pop();
//	vis[now] = false;
//}

int main() {
    char g[10] = { 'A', 'B', 'C',  'D' , 'E', 'F' ,'G','H' };
    AdjListDirNetwork<char, int > t1(g,8,10,1);

    t1.MatchAWithB('A','B');
    t1.MatchAWithB('A', 'C');
    t1.MatchAWithB('B', 'C');
    t1.MatchAWithB('B', 'D');

    t1.MatchAWithB('E', 'F');
    t1.MatchAWithB('H', 'F');
    t1.PrintTu();
    std::cout << (t1.Is_A_to_B_Both_OK('A', 'D')==1?"连通":"不连通")<<std::endl;
    t1.ResetTag();
    t1.The_Way_A_To_B_All('B','A');
    std::cout << "============================================="<<std::endl;

    char f[10] = { 'A', 'B', 'C',  'D' , 'E', 'F' };
    AdjListDirNetwork<char, int > t2(f, 6, 10, 1);
    t2.MatchAWithB_plus('A', 'B', 2);
    t2.MatchAWithB_plus('A', 'E', 4);
    t2.MatchAWithB_plus('A', 'F', 3);
    t2.MatchAWithB_plus('F', 'C', 2);
    t2.MatchAWithB_plus('E', 'F', 9);
    t2.MatchAWithB_plus('D', 'F', 10);

    t2.MatchAWithB_plus('B', 'F', 4);

    t2.MatchAWithB_plus('D', 'E', 5);
    t2.MatchAWithB_plus('B', 'C', 7);
    t2.MatchAWithB_plus('C', 'D', 3);



    t2.PrintTu();
    //t2.DeleteAwithB('A', 'B');
    //std::cout << std::endl;
    //t2.PrintTu();
    std::cout << "=============================================" << std::endl;

    std::cout << std::endl;
    //AdjListDirNetwork<char, int > t3(g, 8, 10, 1);
    AdjListNetworkArc<int> arcFlag;

    //arcFlag.weight=t2.GetMiniArc(t2).weight;
    t2.AtoB('B', 'A');
    //std::cout <<arcFlag.weight<< std::endl;
    t2.Prim(t2);



    return 0;
}