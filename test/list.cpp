#include <iostream>
using namespace std;
struct node
{
	int data;
	struct node *next;
	/* data */
};
class list
{
private:
	node *head;
public:
	list(){head=NULL;};
	~list(){
		node *p = head;
		while (head)
		{
			/* code */
			p=head;
			head = head->next;
			delete(p);
		}
	};
bool Insert(int i, int e)
{
    node *p = head,*s;
    int j = 0;
    if (i == 0)
    {
        s = (node *)new node[1];
        s->data = e;
        s->next = p;
        head = s;
        return true;
    }
    while (p&&j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (p == NULL)
        return false;//到队尾了
    s= (node *)new node[1];
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
};
	void out(){
		while(head)
		{
			cout<<head->data<<endl;
			head = head ->next;
		}
	} 

};
bool init(list a,list b){
    node *p,*q;
    p = a.head->next;
    q = b.head->next;
	 while (p)
	 {
		 if (p->data != q->data) {
			 p = p->next;
			 q = b.head->next;
		 }
		 else {
			 p = p->next;
			 q = q->next;
		 }
	 }
	 if (q==NULL)return true;
	 else return false;
}

int main()
{
	list a,b;
	a.Insert(0,1);
	a.Insert(1,2);
	a.Insert(2,3);
	a.out();
	b.Insert(0,1);
	b.Insert(1,2);
	b.out();
	cout<<init(a,b);
	system("pause");
	return 0;
}


