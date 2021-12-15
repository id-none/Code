#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char Elemtype;
typedef struct Node
{
    char data[80];
    struct Node* next;
}Node,*LinkList;


//����ͷ�ڵ�
void creat_firsthead(LinkList *pHead)
{
	*pHead = (LinkList)malloc(sizeof(Node));
	if(*pHead != NULL)
		(*pHead)->next = NULL;
	else
		printf("�ڴ濪��ʧ��");
}

//�����½��
LinkList get_newNode(char e[])
{
	int n = strlen(e);
    LinkList newNode=(LinkList)malloc(sizeof(Node));
    if(NULL!=newNode)
	{
		for(int i = 0;i <= n; ++i)
            newNode->data[i]=e[i];
		newNode->next=NULL;
		return newNode;
	}
	else
	{ 
		printf("�ڴ濪��ʧ��\n");
		return 0;
	} 
}

//ͷ��
void push_Front(LinkList *L,char e[])
{
	LinkList p;
	p=get_newNode(e);
	p->next=(*L)->next;
	(*L)->next=p; 
}

//β��
void push_Back(LinkList *L,char e[])
{
	LinkList tail; 
	tail=*L;
	while(NULL!=tail->next)		//��tailָ�����һ����� 
		tail=tail->next;
	tail->next=get_newNode(e);
}

//ͷɾ 
void pop_Front(LinkList *L)
{
	LinkList p;
	p=(*L)->next;
	if(p!=NULL) 
	{
		(*L)->next=p->next;
		free(p);
		p=NULL;		//�����ͷ��ڴ��ָ�븳ֵ�ɿյ�ϰ�ߣ���ֹ���ΪҰָ�� 
		printf("OK\n"); 
	}
} 

//βɾ 
void pop_Back(LinkList *L)
{
	LinkList p,q;
	p=*L;
	while(p->next!=NULL)
	{
		q=p;
		p=p->next;
	}
	free(p);
	p=NULL;
	q->next=NULL;
	printf("OK\n"); 
} 

//ָ��Ԫ��ɾ�� 
void delete_List(LinkList *L,char key[])
{
	LinkList p,q;
    int flag = 0;
    int n = strlen(key);
	for(p=*L;NULL!=p->next;p=p->next)
	{
		for(int i = 0;i < n; ++i)   
            if(p->next->data[i]!=key[i])
                flag = 1;
		if(flag == 0)
        {
			q=p->next;		//��Ϊ���Ҫ�ͷű�ɾ���Ľ�㣬�����ȼ�¼���� 
			p->next=q->next;
			free(q);
			q=NULL;
			printf("ɾ���ɹ�\n");
			return;
		}
	} 
	printf("ɾ��ʧ��\n"); 
}

//��ӡ 
void print_List(LinkList *L)
{
	LinkList p;
	p=(*L)->next;

	if(p==NULL)
		printf("NULL\n");
	else
	{
		while(NULL!=p)
		{
		 	int n = strlen(p->data);
            for(int i = 0;i <n; ++i)
                printf("%c ",p->data[i]);
		 	p=p->next;
		}
	 	printf("\n"); 
	}
}

//���� 
int search_List(LinkList *L,char e[])
{
	LinkList p=(*L)->next;
	int i=1;
    int n = strlen(e);
	while(NULL!=p)
	{
		int flag = 0;
        for(int j = 0;j < n; ++j)
            if(p->data[j]!=e[j])
                flag = 1;
        if(flag == 1) p =p->next;
		if(flag == 0) return i;
		i++;
	}
	printf("�����ڵ�\n");
	return 0; 
}

int main()
{
	char a[8] = "abcdefg";
    //printf("%d",strlen(a));
	LinkList L;
    creat_firsthead(&L);
	
    push_Front(&L,a);
	push_Back(&L,a);
    print_List(&L);
	printf("%d",search_List(&L,a));
	delete_List(&L,a);
	system("pause");
	return 0;
}