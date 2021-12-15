#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_SIZE 20

typedef struct{
    char data;
    int front;
    int cur;
}Static_List_t;

extern void Reserve_List(Static_List_t *list);
extern int Malloc_List(Static_List_t *list);
extern int Insert_List(Static_List_t *list, int add_idx, char in_char);
extern void Free_List(Static_List_t *list, int k);
extern int Delet_List(Static_List_t *list, char delete_char);
extern void Traverse_List(Static_List_t *list);


void Reserve_List(Static_List_t *list)
{
    int i;
    assert(MAX_SIZE > 1);
    for (i = 0; i < MAX_SIZE - 2; i++)
    {
        list[i + 1].front = i;
        list[i].cur = i + 1;
    }
    list[MAX_SIZE - 2].cur = 0;
    list[0].front = MAX_SIZE - 1;
    list[MAX_SIZE - 1].cur = 0;
    list[MAX_SIZE - 1].front = MAX_SIZE -2;
}

int Malloc_List(Static_List_t *list)
{
    int i = list[0].cur;
    /* i=0 mean the list is full */
    if (i == 0)
    {
        printf("the list is full \n");
    }
    else
    {
        list[list[i].cur].front = 0;
        list[0].cur = list[i].cur;
    }

    return i;
}

int Delet_List_ByChar(Static_List_t *list, const char in_char)
{
    int j;
    int i = list[MAX_SIZE - 1].cur;
    while (list[i].cur != 0)
    {
        j = i;
        i = list[i].cur;
        if (list[j].data == in_char)
        {
            list[list[j].cur].front = list[j].front;
            list[list[j].front].cur = list[j].cur;
            Free_List(list, j);
        }
    }
    if (list[i].data == in_char)
    {
        list[list[i].front].front = 0;
        Free_List(list, i);
    }
    return 0;
}

int Insert_List_Piro(Static_List_t *list, char in_char)
{
    int i = list[MAX_SIZE - 1].cur;
    int temp_head_idx = MAX_SIZE - 1;
    int insert = Malloc_List(list);
    if (insert == 0)
    {
        printf("  Insert_List() filen \n");
    }
    else
    {
        if (i == 0)
        {
            list[insert].cur = list[MAX_SIZE - 1].cur;
            list[MAX_SIZE - 1].cur = insert;

            list[insert].data = in_char;
            list[insert].front = MAX_SIZE - 1;
        }
        else
        {
            while (in_char >= list[i].data)
            {
                if (list[i].cur == 0)
                    break;
                i = list[i].cur;
            }
            if (list[i].cur == 0)
            {
                list[insert].cur = 0;
                list[insert].front = i;
                list[insert].data = in_char;
                list[i].cur = insert;
            }
            else
            {
                list[list[i].front].cur = insert;
                list[insert].front = list[i].front;
                list[i].front = insert;
                list[insert].cur = i;
                list[insert].data = in_char;
            }
        }
    }
    return 0;
    /* insert num with the idx in insert_list */
}

int Insert_List(Static_List_t *list, int add_idx, char in_char)
{
    int i;
    int temp_head_idx = MAX_SIZE - 1;
    int insert = Malloc_List(list);
    if (insert == 0)
    {
        printf("  Insert_List() filen \n");
    }
    else
    {
        if (add_idx == 1)
        {
            if (list[MAX_SIZE - 1].cur != 0)
                list[list[MAX_SIZE - 1].cur].front = insert;
            list[insert].cur = list[MAX_SIZE - 1].cur;
            list[insert].data = in_char;
            list[MAX_SIZE - 1].cur = insert;
            list[insert].front = MAX_SIZE - 1;
        }
        else
        {
            for (i = 0; i < add_idx - 1; i++)
                temp_head_idx = list[temp_head_idx].cur;
            list[insert].cur = list[temp_head_idx].cur;
            list[insert].data = in_char;
            list[list[temp_head_idx].cur].front = insert;
            list[temp_head_idx].cur = insert;
            list[insert].front = temp_head_idx;
        }
    }
    return 0;
    /* insert num with the idx in insert_list */
}

void Free_List(Static_List_t *list, int k)
{
    list[k].cur = list[0].cur;
    list[0].cur = k;
    list[list[0].cur].front = k;
    list[k].front = 0;
}

int Delet_List(Static_List_t *list, char delete_char)
{
    int ret = 1;
    int i = list[MAX_SIZE - 1].cur;
    while (list[i].data != delete_char)
    {
        i = list[i].cur;
        if (i == 0)
        {
            printf("char can't be find\n");
            /*  char can't be find */
            return 0;
        }
    }
    if (list[i].cur == 0)
    {
        list[list[i].front].cur = 0;
    }
    else
    {
        list[list[i].front].cur = list[i].cur;
        list[list[i].cur].front = list[i].front;
    }
    Free_List(list, i);
}

void Traverse_List(Static_List_t *list)
{
    int i = MAX_SIZE - 1;

    while (list[i].cur != 0)
    {

        printf("the list[%d]'s ", list[i].cur);
        i = list[i].cur;
        printf("data is %c\n", list[i].data);
    }
}

int main(int argc, char const *argv[])
{
    Static_List_t list[MAX_SIZE];
    Reserve_List(list);
    Insert_List(list, 1, 'y');
    Insert_List(list, 1, 'y');
    Insert_List(list, 1, '5');
    Insert_List(list, 1, '5');
    Insert_List(list, 3, 'p');
    Delet_List(list,'y');
    Delet_List(list,'y');
    Insert_List(list, 1, '5');
    Insert_List(list, 3, 'p');
    Traverse_List(list);
    system("pause");
    return 0;
}