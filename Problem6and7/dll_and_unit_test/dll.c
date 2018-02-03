/*****************************************************************************
​ ​*​ ​Copyright​ ​(C)​ ​2018 ​by​ Zach Farmer
​ ​*
​ ​*​ ​Redistribution,​ ​modification​ ​or​ ​use​ ​of​ ​this​ ​software​ ​in​ ​source​ ​or​ ​binary
​ ​*​ ​forms​ ​is​ ​permitted​ ​as​ ​long​ ​as​ ​the​ ​files​ ​maintain​ ​this​ ​copyright.​ ​Users​ ​are
​ ​*​ ​permitted​ ​to​ ​modify​ ​this​ ​and​ ​use​ ​it​ ​to​ ​learn​ ​about​ ​the​ ​field​ ​of​ ​embedded
​ ​*​ ​software.​ ​Alex​ ​Fosdick​ ​and​ ​the​ ​University​ ​of​ ​Colorado​ ​are​ ​not​ ​liable​ ​for
​ ​*​ ​any​ ​misuse​ ​of​ ​this​ ​material.
​ ​*
*****************************************************************************/
/**
​ ​*​ ​@file​ ​dll.c
​ ​*​ ​@brief​ ​Doubly-linked list source
​ ​*
​ ​*​ ​This​ ​is the source ​file​ for a doubly-linked list data structure
​ ​*
​ ​*​ ​@author​ ​Zach Farmer
​ ​*​ ​@date​ ​Feb 2 2018
​ ​*​ ​@version​ ​1.0
​ ​*
​ ​*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include "dll.h"
int count = 0;

/**
​ ​*​ ​@brief​ ​Create an empty node
​ ​*
​ ​*​ ​Creates an empty doubly-linked list node. 
 * Must be called to create the first node.
​ ​*
​ ​*​ ​@param​ ​data Data to place in the first node
​ *
​ ​*​ ​@return​ Pointer to the head node
​ ​*/
Node * create(uint32_t data)
{
    Node * head = (Node *)malloc(sizeof(Node));
    head->prev = NULL;
    head->next = NULL;
    head->data = data;
    count++;
    return head;
}

/**
​ ​*​ ​@brief​ ​Insert at beginning of the DLL
​ ​*
​ ​*​ ​Inserts a node at the beginning of the doubly linked list
​ ​*
 *​ ​@param​ ​head the head pointer of the list to place data in
​ ​*​ ​@param​ ​data Data in the inserted node at beginning
​ *
​ ​*​ ​@return​ Pointer to the head node
​ ​*/
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

/**
​ ​*​ ​@brief​ ​Insert at end of the DLL
​ ​*
​ ​*​ ​Inserts a node at the end of the doubly linked list
​ ​*
 *​ ​@param​ ​head the head pointer of the list to place data in
​ ​*​ ​@param​ ​data Data in the inserted node at end
​ *
​ ​*​ ​@return​ Pointer to the head node
​ ​*/
Node * insert_at_end(Node * head, uint32_t data)
{
    Node * newhead = create(data);
    head->next = newhead;
    newhead->prev = head;
    return newhead;
}

/**
​ ​*​ ​@brief​ ​Insert at any position in DLL
​ ​*
​ ​*​ ​Inserts a node at a specified position of the doubly linked list
​ ​*
 *​ ​@param​ ​head the head pointer of the list to place data in
​ ​*​ ​@param​ ​pos position in list to place the node
​ ​*​ ​​@param​ ​data Data in the inserted node at pos
​ *
​ ​*​ ​@return​ Pointer to the head node
​ ​*/
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

/**
​ ​*​ ​@brief​ ​Remove a node
​ ​*
​ ​*​ ​Removes a node in a list. NOT FOR EXTERNAL USE.
​ ​*
 *​ ​@param​ nodeptr pointer to the node to remove
​ *
​ ​*​ ​@return​ Pointer to the head node
​ ​*/
int __remove(Node * nodeptr)
{
    free(nodeptr);
    count--;
    return 0;
}

/**
​ ​*​ ​@brief​ Delete an entire linked list
​ ​*
​ ​*​ ​Deletes an entire linked list
​ ​*
 *​ ​@param​ ​head the head pointer of the list to destroy
​ *
​ ​*​ ​@return​ NULL node pointer
​ ​*/
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

/**
​ ​*​ ​@brief​ ​Delete at beginning of the DLL
​ ​*
​ ​*​ ​Delete a node at the beginning of the doubly linked list
​ ​*
 *​ ​@param​ ​head the head pointer of the list to delete from
​ *
​ ​*​ ​@return​ Pointer to the head node
​ ​*/
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

/**
​ ​*​ ​@brief​ ​Delete at end of the DLL
​ ​*
​ ​*​ ​Delete a node at the end of the doubly linked list
​ ​*
 *​ ​@param​ ​head the head pointer of the list to delete from
​ *
​ ​*​ ​@return​ Pointer to the head node
​ ​*/
Node * delete_at_end(Node * head)
{
    Node * newhead = head->prev;

    newhead->next = NULL;

    __remove(head);

    return newhead;
}


/**
​ ​*​ ​@brief​ ​Delete at any  position of the DLL
​ ​*
​ ​*​ ​Delete a node at a given position in the doubly linked list
​ ​*
 *​ ​@param​ ​head the head pointer of the list to delete from
 *​ ​@param​ pos position in the list to delete from
​ *
​ ​*​ ​@return​ Pointer to the head node
​ ​*/
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

/**
​ ​*​ ​@brief​ Peek at any  position of the DLL
​ ​*
​ ​*​ ​Give data of node at a given position in the doubly linked list
​ ​*
 *​ ​@param​ ​head the head pointer of the list to peek into
 *​ ​@param​ pos position in the list to view data at
​ *
​ ​*​ ​@return​ Data at given node
​ ​*/
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

/**
​ ​*​ ​@brief​ ​Print the entire DLL
​ ​*
​ ​*​ ​Delete a node at a given position in the doubly linked list
​ ​*
 *​ ​@param​ ​head the head pointer of the list to delete from
 *​ ​@param​ pos position in the list to delete from
​ *
​ ​*​ ​@return​ Pointer to the head node
​ ​*/
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
