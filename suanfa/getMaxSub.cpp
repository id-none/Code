#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> getMaxSub(vector<int> v)
{
    int size = v.size();
    vector<int> len(size, 1);
    vector<int> pos(size); //记录位置
    //res[i]代表以第i个元素结尾的长度
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (v[j] < v[i] && len[i] < len[j] + 1)
            {
                len[i] = len[j] + 1;
                pos[i] = j;
            }
        }
    }

    int max = -1;
    int lastPos = -1;
    for (int i = 0; i < len.size(); ++i)
    {
        if (max < len[i])
        {
            max = len[i];
            lastPos = i;
        }
    }

    vector<int> res;
    for (int i = 0; i < max; ++i)
    {
        res.push_back(v[lastPos]);
        lastPos = pos[lastPos];
    }
    reverse(res.begin(), res.end());

    return res;
}

int main()
{
    int T;
    cin >> T;
    vector<int> v;
    while (T--)
    {
        int size;
        cin >> size;
        int temp;
        for (int i = 0; i < size; ++i)
        {
            cin >> temp;
            v.push_back(temp);
        }
        auto ans = getMaxSub(v);

        for (int i = 0; i < ans.size() - 1; ++i)
        {
            cout << ans[i] << ' ';
        }
        cout << ans[ans.size() - 1] << endl;
        v.clear();
    }
    system("pause");
    return 0;
}