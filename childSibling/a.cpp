#include<iostream>
#include<queue>
using namespace std;
template<class Elemtype>
struct node
{
	Elemtype data;
	node* first_child;
	node* next_brother;
public:
	node(void) {};
	node(Elemtype d);
};
template<class Elemtype>
node<Elemtype>::node(Elemtype d)
{
	data = d;
	first_child = NULL;
	next_brother = NULL;
}
template<class Elemtype>
class BroTree
{
	node<Elemtype>* root;
public:
	BroTree(void);
	~BroTree(void);
	void Insert(node<Elemtype>* P, Elemtype v);
	node<Elemtype>* GetNode(Elemtype v);
	int Hight(node<Elemtype>* root);
	node<Elemtype>* GetRoot(void);
	int Degree(node<Elemtype>* root);
};
template<class Elemtype>
BroTree<Elemtype>::BroTree(void)
{
	root = NULL;
}
template<class Elemtype>
BroTree<Elemtype>::~BroTree(void)
{
	if (root == NULL)
		return;
	node<Elemtype>* p;
	p = root;
	queue<node<Elemtype>*> q;
	q.push(p);
	while (!q.empty())
	{
		node<Elemtype>* t;
		t = q.front();
		q.pop();
		if (t->first_child != NULL)
		{
			q.push(t->first_child);
		}
		if (t->next_brother != NULL)
		{
			q.push(t->next_brother);
		}
		delete t;
		t = NULL;
	}
}
template<class Elemtype>
void BroTree<Elemtype>::Insert(node<Elemtype>* P, Elemtype v)
{
	if (P == NULL && root == NULL)
	{
		root = new node<Elemtype>(v);
		return;
	}
	if (P == NULL)
		return;
	node<Elemtype>* r, * t;
	t = new node<Elemtype>(v);
	r = P;
	if (r->first_child == NULL)
	{
		r->first_child = t;
	}
	else
	{
		r = r->first_child;
		while (r->next_brother != NULL)
			r = r->next_brother;
		r->next_brother = t;
	}
}
template<class Elemtype>
node<Elemtype>* BroTree<Elemtype>::GetNode(Elemtype v)
{
	if (root == NULL)return NULL;
	queue<node<Elemtype>*> q;
	node<Elemtype>* p, * r;
	p = root;
	r = NULL;
	q.push(p);
	while (!q.empty())
	{
		p = q.front();
		q.pop();
		if (p->data == v)
		{
			r = p;
			break;
		}
		if (p->first_child != NULL)
			q.push(p->first_child);
		if (p->next_brother != NULL)
			q.push(p->next_brother);
	}
	return r;
}
template<class Elemtype>
node<Elemtype>* BroTree<Elemtype>::GetRoot(void)
{
	return root;
}
template<class Elemtype>
int BroTree<Elemtype>::Hight(node<Elemtype>* R)
{
	if (R == NULL)
		return 0;
	return max(Hight(R->first_child) + 1, Hight(R->next_brother));
}
template<class Elemtype>
int BroTree<Elemtype>::Degree(node<Elemtype>* R)
{
	if (R == NULL)
		return 0;
	int ans = 0;
	int temp = 0;
	node<Elemtype>* p;
	p = R->first_child;
	while (p != NULL)
	{
		ans++;
		temp = max(temp, Degree(p));
		p = p->next_brother;
	}
	ans = max(ans, temp);
	return ans;
}
int main(void)
{
	BroTree<int> T;
	int root;
	cin>>root;
	T.Insert(NULL, root);
	int a, b;
	a = 0;
	b = 1;
	while (a != b)
	{
		cin >> a >> b;
		if (a == b)
			break;
		node<int>* p;
		p = T.GetNode(a);
		T.Insert(p, b);
	}
	cout << T.Hight(T.GetRoot()) << endl;
	cout << T.Degree(T.GetRoot()) << endl;
	system("pause");
	return 0;
}