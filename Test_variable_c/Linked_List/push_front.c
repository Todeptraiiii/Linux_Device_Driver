#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data; // data
    struct node *next; // dia chi cua node tiep theo
};
typedef struct node node;

node *makenode(int x)
{
    node *newnode;
    newnode = (node *) malloc(sizeof(node));
    newnode->data = x;
    newnode->next = NULL;
    return newnode;
}

void duyet(node *newnode)
{
    while(newnode != NULL)
    {
        printf("%d ", newnode->data);
        newnode = newnode->next;
    }
    printf("\n");
}

void push_front(int x, node **head)
{
    node *newnode;
    newnode = makenode(x); // xin cap phat mot node moi
    newnode->next = *head; // dia chi cua node tiep theo
    *head = newnode; //  cap nhat lai dia chi node head
}
int main()
{
    node *new = NULL;
    for(int i = 0 ; i < 5 ; i ++)
    {
        push_front(i,&new);
    }
    duyet(new);
    return 0;
}