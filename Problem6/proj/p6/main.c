#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include "main.h"
int count = 0;

#define offsetof(type, member) ((size_t) &((type *)0)->member)

#define GET_LIST_CONTAINER(ptr, type, member) ({                \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

int main()
{



    Info* i1 = __create(1);
    uint32_t i;
    for(i=2;i<10;i++)
    {
        i1 = insert_at_end(i1,i);
    }
    //printAll(n1);
/*
    n1=insert_at_position(n1,5,243);
    printAll(n1);
    n1=delete_at_position(n1,5);

    printAll(n1);
*/
    i1 = destroy(i1);
    printAll(i1);
}

/* TO __create an empty node */
Info * __create(uint32_t data)
{
    Info * head = (Info *)malloc(sizeof(Info));
    head->nd = (Node *)malloc(sizeof(Node));
    head->nd->prev = NULL;
    head->nd->next = NULL;
    head->data = data;
    //Info* nfo = GET_LIST_CONTAINER(head, Info, nd);
    //nfo->data = data;
    //printf("%d/n",nfo->data);
    count++;
    return head;
}

/*  TO insert at beginning */
Info * insert_at_beginning(Info * head, uint32_t data)
{
    Node * current = head->nd;
    Info * start;

    while(current->prev != NULL)
    {
        current = current->prev;
    }

    start = __create(data);
    start->nd->next = current;
    current->prev = start->nd;

    return head;
}

/* To insert at end */
Info * insert_at_end(Info * head, uint32_t data)
{
    Info * newhead = __create(data);
    head->nd->next = newhead->nd;
    newhead->nd->prev = head->nd;
    return newhead;
}

/* To insert at any position */
Info * insert_at_position(Info * head, int pos, uint32_t data)
{

    int i = count;
    if ((pos < 1) || (pos > count))
    {
        printf("\n Position out of range to insert");
        return head;
    }
    else if ((head == NULL) && (pos != 1))
    {
        printf("\n Empty list cannot insert other than 1st position");
        return head;
    }
    else if (pos == 1)
    {
        return insert_at_beginning(head, data);
    }
    else if (pos == count)
    {
        return insert_at_end(head, data);
    }
    else
    {
    	Node * current = head->nd;
        while (i > pos)
        {
            current = current->prev;
            i--;
        }

        //ORDER MATTERS HERE!!
        //OTHERWISE THERE ARE NODE LOOPS
        //WHICH CAUSE SEGFAULT
        Info * new_info = __create(data);
        new_info->nd->prev = current->prev;
        new_info->nd->next = current;
        current->prev->next = new_info->nd;
        current->prev = new_info->nd;
        return head;
    }
}

//not for external use
int __remove(Info * nfo)
{
    free(nfo);
    count--;
    return 0;
}

/*  TO delete at beginning */
Info * destroy(Info * head)
{
    printf("");
    Node * current = head->nd;

    while(current->prev != NULL)
    {
        current = current->prev;
        //printf("%u",current->data);
        __remove(GET_LIST_CONTAINER(current->next, Info, nd));
    }
    __remove(GET_LIST_CONTAINER(current, Info, nd));
    __remove(head);
    printf("Destroyed all Nodes\n");
    return NULL;
}

/*  TO delete at beginning */
Info * delete_from_beginning(Info * head)
{
    Node * current = head;

    while(current->prev != NULL)
    {
        current = current->prev;
    }

    current->next->prev = NULL;

    __remove(current);
    return head;
}

/* To delete at end */
Info * delete_at_end(Info * head)
{
    Node * newhead = head->nd->prev;

    newhead->next = NULL;

    __remove(head);

    return newhead;
}

/* To delete at any position */
Info * delete_at_position(Info * head, int pos)
{
    int i = count;

    if ((pos < 1) || (pos > count))
    {
        printf("\n Position out of range to delete");
        return head;
    }
    else if ((head == NULL) && (pos != 1))
    {
        printf("\n Empty list, nothing to delete");
        return head;
    }
    else if (pos == 1)
    {
        return delete_from_beginning(head);
    }
    else if (pos == count)
    {
        return delete_at_end(head);
    }
    else
    {
    	Node * current = head;
        while (i > pos)
        {
            current = current->prev;
            i--;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;

        __remove(current);

        return head;
    }
}

void printAll(Info * head)
{
    if(head!=NULL)
    {
        Node * current = head;

        //Info* nfo;

        int32_t number = count;
        printf("Node\tData\n");
        while(current->prev != NULL)
        {
           //nfo = ;
            printf("%u\t%u\n", number,GET_LIST_CONTAINER(current, Info, nd)->data);
            number--;
            current = current->prev;
        }
        //nfo = GET_LIST_CONTAINER(current, Info, nd);
        printf("%u\t%u\n", number,GET_LIST_CONTAINER(current, Info, nd)->data);
        printf("END\n");
    }
    else
    {
        printf("NULL Head Pointer");
    }
}
