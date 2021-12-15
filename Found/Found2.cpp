#include <iostream>
#include <string>
using namespace std;
struct node
{
	char data;
	node * lchild;
	node * rchild;
};
node *createNode(int Xb, int Xe, int Zb, int Ze,string xianxu,string zhongxu){
    if(Xb >Xe)
		return NULL;
	node *Node = new node;
	Node->data = xianxu[Xb];
	int k=0;
	for (int i = Zb; i <Ze+1; i++)
	{
		if (xianxu[Xb] == zhongxu[i])
		{
			k = i;
			break;
		}
	}
	Node->lchild = createNode(Xb + 1, Xb+k-Zb, Zb, k - 1, xianxu, zhongxu);
	Node->rchild = createNode(Xb+k-Zb + 1, Xe, k + 1, Ze, xianxu, zhongxu);
	
	return Node;
}
void houxu(node *Node)
{
    if (Node == NULL)
		return;
	houxu(Node->lchild);
	houxu(Node->rchild);
	cout << Node->data;
}

int Judge(node* root,char &MAX)
{
    if(root == NULL){//树为空则为二叉排序树 
        return 1;
    }
    int bst_l,bst_r;
    bst_l = Judge(root->lchild,MAX);//判断左子树是否为二叉排序树
    if(!bst_l || MAX >= root->data){
        return 0;
    }
    MAX = root->data;
    bst_r = Judge(root->rchild,MAX);//判断右子树是否为二叉排序树
    return bst_r;
}
int main()
{
	string xianxu;
	string zhongxu;
    char a = 'A';
	while (cin >> xianxu) {
		
		cin >> zhongxu;
		int Xb, Xe, Zb, Ze;//Xb表示先序开始字符位置Xe表示先序结束字符位置 Zb表示中序开始字符位置,Ze表示中序结束字符位置
		Xb = Zb = 0;
		Xe = xianxu.length() - 1;
		Ze = zhongxu.length() - 1;
		node *Node = new node;
		Node = createNode(Xb, Xe, Zb, Ze, xianxu, zhongxu);
		//houxu(Node);
        cout << Judge(Node,a);
	}
		system("pause");
	return 0;
}
