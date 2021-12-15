#include <stdio.h>
#include <stdlib.h>
// ������󳤶�
#define MAX_SIZE 1000
// ��̬����ʹ�������±����ָ�� 
// cur��ʾ�����±�ָ����һ�����λ�� 
typedef struct list_node
{
  int data;
  int cur;
}list_node;
//  ʹ��һά����ʵ�ֵ����� 
list_node link_list[MAX_SIZE]; 
// ��ʼ������Ϊ������
// link_list[0]Ϊ����ͷ���
// link_list[1]Ϊ���б����������ڼ�¼δʹ�ù�������ռ� 
void init_link_list()
{
  // ��ͷ�����±�ָ���Լ�ʱ������Ϊ�� 
  link_list[0].cur = 0;  
  // ������ʱ�����еĿռ��δʹ�� 
  int i;
  for(i=1; i<MAX_SIZE-1; i++)
    link_list[i].cur = i+1;
  link_list[MAX_SIZE-1].cur = 0;
} 
 
// �������� 
int insert_link_list(int data)
{
  // �ռ�����������-1 
  if(link_list[1].cur == 0)
    return -1;
  
  // �ڿ��б���������Ѱ��һ�����е�λ�ô������
  int pos = link_list[1].cur;
  link_list[1].cur = link_list[pos].cur;
  
  // ͷ�巨��ֱ�ӽ����ݲ��������һ��λ��
  link_list[pos].data = data;
  link_list[pos].cur = link_list[0].cur;
  link_list[0].cur = pos; 
  return 0;
}
// ɾ��ָ��λ�� 
int delete_link_list(int *data, int pos)
{
  if(data == NULL || link_list[0].cur == 0 || pos < 1)
    return -1;
  // �ҵ�posλ�õ�ǰһ����� 
  int i = 1;
  int cur = 0;
  while(i<pos && link_list[cur].cur)
  {
    i++;
    cur = link_list[cur].cur;
  }
  
  if(i==pos && link_list[cur].cur)
  {
    int t = link_list[cur].cur;
    *data = link_list[t].data;
    link_list[cur].cur = link_list[t].cur;
    link_list[t].cur = link_list[1].cur;
    link_list[1].cur = t;
  }
  return 0;  
}
// �鿴 
void print_link_list()
{
  int cur = link_list[0].cur;
  while(cur != 0)
  {
    printf("%d ", link_list[cur].data);
    cur = link_list[cur].cur;
  }
  printf("\n");
 } 
 
int main(void)
{
  init_link_list();
  int n,d;
  printf("�����������ܸ���:");
  scanf("%d", &n);
  printf("����������%d������:", n);
  int i;
  for(i=0; i<n; i++)
  {
    scanf("%d", &d);
    // ÿ�β��뵽������λ������ʵ�ֵ��� 
    insert_link_list(d); 
  }  
  printf("��̬����������:");
  print_link_list(); 
  
  printf("��̬����ɾ��%dλ�����ݺ�:",n/2);
  delete_link_list(&d, n/2);
  print_link_list();
  system("pause"); 
  return 0;
}