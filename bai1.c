/*
Implement an ADT for chaining hash table providing the following operations:
–Init
–Hash function
–Insert (given key and element) 
–Search, Delete (given key) 
–IsEmpty
–Clear
–Traverse
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define TRUE 1
#define FALSE 0
#define M 11

typedef struct Node
{
    int key;
    struct Node*next;
}Node;
Node *Bucket[M];

void Init()
{
    int i;
    for(i = 0; i < M; i++)
    {
        Bucket[i] = NULL;
    }
}

//Hash Function
int H(int x)
{
    return x % M;
}

void InitBucket()
{
    int i;
    for(i = 0; i < M; i++)
    {
        Bucket[i] = NULL;
    }
}

void Display()
{
    int i;
    Node *p;
    for(i = 0; i < M; i++)
    {
        p = Bucket[i];
        printf("[%d]: ",i);
        if(p == NULL) printf("NULL");
        while(p!= NULL)
        {
            printf("%d ", p->key);
            p = p->next;
        }
        printf("\n");
    }
}

int search(int x)
{
    Node *p;
    int a;
    p = Bucket[H(x)];
    a = 0;
    while(p!= NULL && !a)
    {
        if(p->key == x) a = 1;
        else p = p->next;
    }
    return a;
}

void Insert(int x)
{
    int i;
    Node *p;
    if(!search(x))
    {
        i = H(x);
        p = (Node *)malloc(sizeof(Node));
        p -> key = x;
        p -> next = Bucket[i];
        Bucket[i] = p;
    }
    else printf("%d da co trong tu dien\n",x);
}

void Delete(int x)
{
    int i,a;
    Node *p, *q;
    i = H(x);
    if(Bucket[i] == NULL) printf("%d khong co trong tu dien\n",x);
    else
    {
        if(Bucket[i]->key == x)
        {
            p = Bucket[i];
            Bucket[i] = Bucket[i]->next;
            free(p);
        }
    else
    {
        q = Bucket[i];
        p = q -> next;
        a = 0;
        while(p != NULL && !a)
        {
            if(p -> key == x)
            {
                a = 1;
                q -> next = p -> next;
                free(p);
            }
            else
            {
                q = p;
                p = q -> next;
            }
        }
        if(!a) printf("%d khong co trong tu dien\n",x);
    }
    }
}
void processinsert()
{
    printf("Nhap gia tri muon chen vao tu dien: ");
    int value;
    scanf("%d",&value);
    Insert(value);
}

void processsearch()
{
    printf("Nhap gia tri can tim kiem: ");
    int value;
    scanf("%d", &value);
    if(search(value) == 0) printf("%d khong co trong tu dien\n",value);
    else if(search(value) == 1) printf("%d co trong tu dien\n",value);
}

void processdelete()
{
    printf("Nhap gia tri can xoa: ");
    int value;
    scanf("%d", &value);
    Delete(value);
}

void main()
{
    int i;
    int choice;
    Init();
    do
    {
        printf("\n-------MENU------\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Moi ban chon menu: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                processinsert();
                break;
            case 2:
                processdelete();
                break;
            case 3:
                processsearch();
                break;
            case 4:
                Display();
                break;
            case 5:
                printf("Thoat\n");
                break;
            
            Default: break;

        }
    } while (choice != 5);
    
}