#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include "dll.h"
int count = 0;

/* TO create an empty node */
Node * create(uint32_t data)
{
    Node * head = (Node *)malloc(sizeof(Node));
    head->prev = NULL;
    head->next = NULL;
    head->data = data;
    count++;
    return head;
}

/*  TO insert at beginning */
Node * insert_at_beginning(Node * head, uint32_t data)
{
    Node * current = head;
    Node * start;

    while(current->prev != NULL)
    {
	current = current->prev;
    }

    start = create(data);
    start->next = current;
    current->prev = start;

    return head;
}

/* To insert at end */
Node * insert_at_end(Node * head, uint32_t data)
{
    Node * newhead = create(data);
    head->next = newhead;
    newhead->prev = head;
    return newhead;
}

/* To insert at any position */
Node * insert_at_position(Node * head, int pos, uint32_t data)
{

    int i = count;
    if ((pos < 1) || (pos > count + 1))
    {
        //printf("\n Position out of range to insert");
        return head;
    }
    else if ((head == NULL) && (pos != 1))
    {
        //printf("\n Empty list cannot insert other than 1st position");
        return head;
    }
    else if (pos == 1)
    {
        return insert_at_beginning(head, data);
    }
    else if (pos == count+1)
    {
        return insert_at_end(head, data);
    }
    else
    {
    	Node * current = head;
        while (i > pos)
        {
            current = current->prev;
            i--;
        }

        //ORDER MATTERS HERE!!
        //OTHERWISE THERE ARE NODE LOOPS
        //WHICH CAUSE SEGFAULT
        Node * new_node = create(data);
        new_node->prev = current->prev;
        new_node->next = current;
        current->prev->next = new_node;
        current->prev = new_node;
        return head;
    }
}

//not for external use
int __remove(Node * nodeptr)
{
    free(nodeptr);
    count--;
    return 0;
}

/*  TO delete at beginning */
Node * destroy(Node * head)
{
    Node * current = head;

    while(current->prev != NULL)
    {
        current = current->prev;
        //printf("%u",current->data);
        __remove(current->next);
    }
    __remove(current);
    //printf("Destroyed all Nodes\n");
    return NULL;
}

/*  TO delete at beginning */
Node * delete_from_beginning(Node * head)
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
Node * delete_at_end(Node * head)
{
    Node * newhead = head->prev;

    newhead->next = NULL;

    __remove(head);

    return newhead;
}

/* To delete at any position */
Node * delete_at_position(Node * head, int pos)
{
    int i = count;

    if ((pos < 1) || (pos > count))
    {
        //printf("\n Position out of range to delete");
        return head;
    }
    else if ((head == NULL) && (pos != 1))
    {
        //printf("\n Empty list, nothing to delete");
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

uint32_t peek_value(Node * head, uint32_t pos)
{
    if(head!=NULL)
    {
        Node * current = head;

        int32_t number = count;
        while(number>pos)
        {
 
            number--;
            current = current->prev;
        }
	return current->data;
    }
    else
    {
	return -1;
    }
}

void printAll(Node * head)
{
    if(head!=NULL)
    {
        Node * current = head;

        int32_t number = count;
        printf("Node\tData\n");
        while(current->prev != NULL)
        {
            printf("%u\t%u\n", number,current->data);
            number--;
            current = current->prev;
        }
        printf("%u\t%u\n", number,current->data);
        printf("END\n");
    }
    else
    {
        printf("NULL Head Pointer");
    }
}
