#include <stdio.h>
#include <stdlib.h>
// 链表最大长度
#define MAX_SIZE 1000
// 静态链表使用数组下标代替指针 
// cur表示数组下标指向下一个结点位置 
typedef struct list_node
{
  int data;
  int cur;
}list_node;
//  使用一维数组实现单链表 
list_node link_list[MAX_SIZE]; 
// 初始化数组为空链表
// link_list[0]为链表头结点
// link_list[1]为空闲备用链表，用于记录未使用过的数组空间 
void init_link_list()
{
  // 当头结点的下标指向自己时，链表为空 
  link_list[0].cur = 0;  
  // 空链表时，所有的空间均未使用 
  int i;
  for(i=1; i<MAX_SIZE-1; i++)
    link_list[i].cur = i+1;
  link_list[MAX_SIZE-1].cur = 0;
} 
 
// 增加数据 
int insert_link_list(int data)
{
  // 空间已满，返回-1 
  if(link_list[1].cur == 0)
    return -1;
  
  // 在空闲备用链表中寻找一个空闲的位置存放数据
  int pos = link_list[1].cur;
  link_list[1].cur = link_list[pos].cur;
  
  // 头插法，直接将数据插入链表第一个位置
  link_list[pos].data = data;
  link_list[pos].cur = link_list[0].cur;
  link_list[0].cur = pos; 
  return 0;
}
// 删除指定位置 
int delete_link_list(int *data, int pos)
{
  if(data == NULL || link_list[0].cur == 0 || pos < 1)
    return -1;
  // 找到pos位置的前一个结点 
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
// 查看 
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
  printf("请输入数据总个数:");
  scanf("%d", &n);
  printf("请依次输入%d个整数:", n);
  int i;
  for(i=0; i<n; i++)
  {
    scanf("%d", &d);
    // 每次插入到链表首位，这样实现倒序 
    insert_link_list(d); 
  }  
  printf("静态链表输出结果:");
  print_link_list(); 
  
  printf("静态链表删除%d位置数据后:",n/2);
  delete_link_list(&d, n/2);
  print_link_list();
  system("pause"); 
  return 0;
}