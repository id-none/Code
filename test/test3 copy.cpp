#include <bits/stdc++.h>

using namespace std;

int times;

int main()
{
    cin >> times;
    int n,x1,y1,x2,y2;
    long long int sum = 0;
    while(times--){
        sum = 0;
        scanf("%d %d %d %d %d",&n,&x1,&y1,&x2,&y2);
        for(int i = y1; i<=y2;++i){
            sum += i*((double)(x1+x2)/2*(x2-x1+1));
        }
        cout << sum % 1000000007 << endl;
    }
    system("pause");
    return 0;
}