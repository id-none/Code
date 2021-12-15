#include <bits/stdc++.h>
using namespace std;


bool PredictTheWinner(vector<int> nums)
{

    int n = nums.size();
    if (n <= 2) {
        return true;
    }
    int dp[100][100];

    // base case
    for (int i = 0; i < n; i++) {
        dp[i][i] = nums[i];
    }
    for (int i = n - 2; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
        }
    }
    return dp[0][n - 1] >= 0;
}

int main()
{
    vector<int> v = { 1,10,100,10,1 };
    string flag = "";
    if (PredictTheWinner(v))
    {
        flag = flag + "先手";
    }
    else
    {
        flag = flag + "后手";
    }
    cout << "你应该是先手还是后手:" << flag << endl;
    system("pause");
    return 0;
}