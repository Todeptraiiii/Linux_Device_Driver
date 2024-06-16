#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
    struct node *prev;
};

typedef struct node node;

node *makenode(int x)
{
    node *newnode;
    newnode = (node*) malloc(sizeof(node));
    newnode->data = x;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

void duyet(node *head)
{
    while(head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
        printf("\n");
}

void push_front(int x, node **head)
{
    node *newnode;
    newnode = makenode(x);
    newnode->next = *head;
    if(*head != NULL)
    {
        (*head)-> prev = newnode;
    }
    *head = newnode;
}

void push_back(int x, node **head)
{
    node *newnode = makenode(x);
    node *temp = *head;

    if(*head == NULL)
    {
        *head = newnode; return; // cho thang nay la newnode neu no rong
    }
    while(temp -> next != NULL)
    {
        temp = temp -> next;
    }
    temp -> next = newnode;
    newnode -> prev = temp;
}

int main()
{
    node *new = NULL;
    for(int i = 0 ; i < 5 ; i ++ )
    {
        // push_front(i,&new);
        push_back(i,&new);
    }
        duyet(new);
}