#include <bits/stdc++.h>
using namespace std;
void encrypt(string text, string k, string &result)
{
	int m = k.length();
	int i = 0, j = 0;
	int table = 1;
	vector<string> vec;		//�½�������Ϊ�������Ľ���
	if (text.length() % m)  //�ж��Ƿ���������������������ֱ�ӷ���
        return;
	int n = text.length() / m;
	for (int i = 0; i < n; i++)
	{
		int tmp = i * m;
		vec.push_back(text.substr(tmp, m));		//���������ĳ�ʼ������
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
    /**��ӭ**/
    cout << "--------�û�����-----------" << endl;
    cout << "����д���Ļ�������" << endl;
    cin >> text;
    cout << "��ѡ����ܷ�ʽ������1���ܣ�����2����" <<endl;
    cin >> type;
    cout << "��������Կk" << endl;
    cin >> k;
    if(type == 1){
        encrypt(text,k,result);
        cout << "����Ϊ" << text << "����Ϊ" << result;
    }else if(type == 2){
        decrypt(text,k,result);
        cout << "����Ϊ" << text << "����Ϊ" << result << endl;
    }
    system("pause");
    return 0;
}
