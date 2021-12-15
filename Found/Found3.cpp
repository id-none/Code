// 平衡二叉树
#include "AVL.h"
#include <bits/stdc++.h>
using namespace std;

int main()
{
    AVL A;
    A.insert(1);
    A.insert(2);
    A.insert(3);
    A.insert(4);
    A.insert(0);
    A.insert(5);
    cout << A.kth(3) << endl;
    system("pause");
}