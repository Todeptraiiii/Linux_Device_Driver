#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
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

void duyet(node *head) // duyet tu head
{
    while(head != NULL)
    {
        printf("%d ", head->data);
        head = head->next; // cap nhat dia chi tiep theo
    }
    printf("\n");
}

void push_back(int x, node **head)
{
    node *temp = *head;
    node *newnode ;
    newnode = makenode(x);
    if(*head == NULL)
    {
        *head = newnode;return;
    }
    while(temp->next != NULL) // duyet tim null
    {
        temp = temp -> next;
    }

    temp->next = newnode;

}

int main()
{
    node *new = NULL;
    for(int i =0 ; i < 5 ; i++)
    {
        push_back(i,&new);
    }
    duyet(new);
}