#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct Node{
   int start;
   int end;
} a[10001];
/**
  自定义的排序规则
*/
bool cmp(Node x,Node y){
    if(x.end<y.end)
        return true;
    else if(x.end==y.end&&x.start>y.start)
        return true;
    return false;
}
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i].start>>a[i].end;
    }
    //a是待排序的数组的首地址，a+n是尾地址
    //cmp是自定义排序规则
    sort(a,a+n,cmp);
    int ans =0;
    int end = -1000000000;
    for(int i=0;i<n;i++){
        if(a[i].start>=end){
            ans++;
            end=a[i].end;
        }
    }
    cout<<ans<<endl;
    system("pause");
    return 0;
}