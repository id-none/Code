#include <bits/stdc++.h>
#include <cctype>
using namespace std;
//���ʴ���
char change_lower(char word)
{
    word = tolower(word); //�ַ�ת����Сд
    return word;
}
//���ݴ���
void deal_data()
{
    map<char, int> word_count;
	multimap<int, char, greater<int> > count;
    char word;
    ifstream in("ciphertext.txt");
    while(in >> word)
    {
        //word = change_lower(word);
        word_count[word]++;
    }
 
    for(map<char,int>::iterator it = word_count.begin();
        it != word_count.end(); it++)
    {
        count.insert(make_pair(it->second, it->first));
    }
	for_each(count.begin(), count.end(), [](auto t1){
		cout << t1.second << "----->count: " << float(t1.first)/3931 << endl;
	}
	);
}
int main(void)
{
  deal_data();
  system("pause");  
  return 0;
}