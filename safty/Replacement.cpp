#include <bits/stdc++.h>
using namespace std;
void encrypt(string text, string k, string &result)
{
	int m = k.length();
	int i = 0, j = 0;
	int table = 1;
	vector<string> vec;		//新建向量作为储存矩阵的介质
	if (text.length() % m)  //判断是否满足整除条件，不满足直接返回
        return;
	int n = text.length() / m;
	for (int i = 0; i < n; i++)
	{
		int tmp = i * m;
		vec.push_back(text.substr(tmp, m));		//矩阵向量的初始化操作
	}
	for (;; table ? i++ : i--)
	{
		if (((i == n - 1 && table) || (i == 0 && !table)) && j < m)
		{
			table = !table;
			result += vec[i][j];
			j++;
			if (j >= m) break;
		}
		result += vec[i][j];
	}
}
void decrypt(string text, string k, string &result)
{
	int m = k.length();
	if (text.length() % m)
		return;
	int n = text.length() / m;
	vector<string> vec;
	int i = 0, j = 0;
	bool table = true;	
	for (int k = 0; k < n; k++)
	{
		vec.push_back("");
	}
	int count = 0;
	for (;; table ? i++ : i--)
	{
		if (((i == n - 1 && table) || (i == 0 && !table)) && j < m)
		{
			vec[i] += text[count];
			count += 1;
			table = !table;
			j++;
			if (j >= m) break;
		}
		vec[i] += text[count];
		count += 1;
	}
	for (int i = 0; i < vec.size(); i++)
		result += vec[i];
}
int main()
{
	string text;
    string result;
    string k;
    int type;
    /**欢迎**/
    cout << "--------置换密码-----------" << endl;
    cout << "请填写明文或者密文" << endl;
    cin >> text;
    cout << "请选择加密方式，输入1加密，输入2解密" <<endl;
    cin >> type;
    cout << "请输入密钥k" << endl;
    cin >> k;
    if(type == 1){
        encrypt(text,k,result);
        cout << "明文为" << text << "密文为" << result;
    }else if(type == 2){
        decrypt(text,k,result);
        cout << "密文为" << text << "明文为" << result << endl;
    }
    system("pause");
    return 0;
}
