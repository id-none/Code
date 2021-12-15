#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        ListNode *ans = new ListNode(-1);
        ListNode *a = ans;
        vector<int> v;
        ListNode *v1 = l1;
        ListNode *v2 = l2;
        while (v1 != nullptr)
        {
            v.push_back(v1->val);
            v1 = v1->next;
        }
        while (v2 != nullptr)
        {
            v.push_back(v2->val);
            v2 = v2->next;
        }
        sort(v.begin(), v.end());
        for (int i = 0; i < v.size(); i++)
        {
            ListNode *node = new ListNode(v[i]);
            ans->next = node;
            ans = ans->next;
        }
        ans->next = nullptr;
        return a->next;
    }

    int missingNumber(vector<int> &nums)
    {
        unordered_set<int> set;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            set.insert(nums[i]);
        }
        int missing = -1;
        for (int i = 0; i <= n; i++)
        {
            if (!set.count(i))
            {
                missing = i;
                break;
            }
        }
        return missing;
    }

    int maxCount(int m, int n, vector<vector<int>> &ops)
    {
        int length = ops.size();
        int mina = 0, minb = 0;
        for (int i = 0; i < length; i++)
        {
            mina = min(mina, ops[i][0]);
            minb = min(minb, ops[i][1]);
        }
        return mina * minb;
    }

    string getHint(string secret, string guess)
    {
        int bulls = 0;
        vector<int> cntS(10), cntG(10);
        for (int i = 0; i < secret.length(); ++i)
        {
            if (secret[i] == guess[i])
            {
                ++bulls;
            }
            else
            {
                ++cntS[secret[i] - '0'];
                ++cntG[guess[i] - '0'];
            }
        }
        int cows = 0;
        for (int i = 0; i < 10; ++i)
        {
            cows += min(cntS[i], cntG[i]);
        }
        return to_string(bulls) + "A" + to_string(cows) + "B";
    }

    int findPoisonedDuration(vector<int> &timeSeries, int duration)
    {
        int time = 0;
        int length = timeSeries.size();
        for (int i = 1; i < length; ++i)
        {
            int before_time = timeSeries[i] - timeSeries[i - 1];
            if (before_time <= duration)
            {
                time += before_time;
                continue;
            }
            time += duration;
        }
        return time + duration;
    }

    int kInversePairs(int n, int k)
    {
        //不会写 over
        int dp[2][1003];
        const int mod = 1000000007;
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= k; j++)
            {
                int now = i & 1, last = now ^ 1;
                dp[now][j] = (j - 1 >= 0 ? dp[now][j - 1] : 0) + dp[last][j] - (j - i >= 0 ? dp[last][j - i] : 0);
                if (dp[now][j] >= mod)
                    dp[now][j] -= mod;
                if (dp[now][j] < 0)
                    dp[now][j] += mod;
            }
        }
        return dp[n & 1][k];
    }

    int romanToInt(string s)
    {
        unordered_map<char, int> symbolValues = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000},
        };

        int ans = 0;
        int n = s.length();
        for (int i = 0; i < n; ++i)
        {
            int value = symbolValues[s[i]];
            if (i < n - 1 && value < symbolValues[s[i + 1]])
            {
                ans -= value;
            }
            else
            {
                ans += value;
            }
        }
        return ans;
    }

    // 中序遍历递归版
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> ans;
        inoderTraversal(root, ans);
        return ans;
    }
    void inoderTraversal(TreeNode *root, vector<int> &ans)
    {
        if (root == nullptr)
        {
            return;
        }
        else
        {
            inoderTraversal(root->left, ans);
            ans.push_back(root->val);
            inoderTraversal(root->right, ans);
        }
    }

    //中序遍历非递归版本
    vector<int> inorderTraversal_2(TreeNode *root)
    {
        vector<int> ans;
        stack<TreeNode *> st;
        while (!st.empty() || root != nullptr)
        {
            while (root != nullptr)
            {
                st.push(root);
                root = root->left;
            }
            root = st.top();
            st.pop();
            ans.push_back(root->val);
            root = root->right;
        }
        return ans;
    }

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
    }

    int getMoneyAmount(int n)
    {
        vector<vector<int>> f(n + 1, vector<int>(n + 1));
        for (int i = n - 1; i >= 1; i--)
        {
            for (int j = i + 1; j <= n; j++)
            {
                int minCost = INT_MAX;
                for (int k = i; k < j; k++)
                {
                    int cost = k + max(f[i][k - 1], f[k + 1][j]);
                    minCost = min(minCost, cost);
                }
                f[i][j] = minCost;
            }
        }
        return f[1][n];
    }

    vector<vector<int>> threeSum(vector<int> &nums)
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        for (int first = 0; first < n; first++)
        {
            if (first > 0 && nums[first] == nums[first - 1])
            {
                continue;
            }
            int third = n - 1;
            int key = -nums[first];
            for (int second = first + 1; second < n; second++)
            {
                if (second > first + 1 && nums[second] == nums[second - 1])
                {
                    continue;
                }
                while (second < third && nums[second] + nums[third] > key)
                {
                    --third;
                }
                if (second == third)
                {
                    break;
                }
                if (nums[second] + nums[third] == key)
                {
                    ans.push_back({nums[first], nums[second], nums[third]});
                }
            }
        }
        return ans;
    }

    //杨辉三角
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> ret(numRows);
        for (int i = 0; i < numRows; ++i)
        {
            ret[i].resize(i + 1);
            ret[i][0] = ret[i][i] = 1;
            for (int j = 1; j < i; ++j)
            {
                ret[i][j] = ret[i - 1][j] + ret[i - 1][j - 1];
            }
        }
        return ret;
    }

    //删除链表倒数第N个节点
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *root = head;
        int sum = 0;
        while (root)
        {
            sum++;
            root = root->next;
        }
        root = head;
        while (root)
        {
            sum--;
            if (sum - 1 == n)
            {
                root->next = root->next->next;
            }
            root = root->next;
        }
        return head;
    }

    vector<int> numberOfLines(vector<int> &widths, string ss)
    {
        int width = 1;
        int sum = 0;
        for (char s : ss)
        {
            int w = widths[s - 'a'];
            sum += w;
            if (sum > 100)
            {
                width++;
                sum = w;
            }
        }
        return {width, sum};
    }

    bool canThreePartsEqualSum(vector<int> &nums)
    {
        int sum = 0;
        int n = nums.size();
        for (int num : nums)
        {
            sum += num;
        }
        if (sum % 3 != 0 && n % 3 != 0)
        {
            return false;
        }
    }

    int bulbSwitch(int n)
    {
        vector<bool> v(n + 1, 0);
        int num = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = i; j <= n; j += i)
            {
                v[j] = !v[j];
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (v[i])
            {
                num++;
            }
        }
        return num;
    }

    int integerReplacement(int n)
    {
        vector<vector<int>> v(n + 1, vector<int>(n + 1, 0));
        int Min = 0xffffffff;
        for (int i = 0; i <= n; i++)
        {
            if (n % 2 == 0)
            {
                v[n][n / 2] = 1;
            }
            else
            {
                v[n][n - 1] = 1;
                v[n][n + 1] = 1;
            }
        }
        for (int i = n; i >= 1; i--)
        {
            for (int j = 1; j < n + 1; i++)
            {
                for (int k = j; k <= i; k++)
                {
                    Min = min(v[i][k] + v[k][j], Min);
                }
                v[i][j] = Min;
            }
        }
        return v[n][1];
    }

    int poorPigs(int buckets, int minutesToDie, int minutesToTest)
    {
        int n = minutesToTest / minutesToDie;
        int pigs = ceil(log(buckets) / log(n));
        return pigs;
    }

    TreeNode *searchBST(TreeNode *root, int val)
    {
        if (root == nullptr)
        {
            return NULL;
        }
        if (root->val == val)
        {
            return root;
        }
        if (val > root->val)
            return searchBST(root->left, val);
        else
            return searchBST(root->right, val);
    }

    int long_same(string s)
    {
        int n = s.size();
        vector<int> dp(n, 1);
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                if (dp[j] == dp[j - 1])
                {
                    dp[i] = max(dp[i-1]+1,dp[i]);
                }
            }
        }
        int Max = 0;
        for (int i = 0; i < n; i++)
        {
            Max = max(Max, dp[i]);
        }
        return Max;
    }
};