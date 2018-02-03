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
​ ​*​ ​@file​ ​dll.h
​ ​*​ ​@brief​ ​Doubly-linked list header
​ ​*
​ ​*​ ​This​ ​is the header ​file​ for a doubly-linked list data structure
​ ​*
​ ​*​ ​@author​ ​Zach Farmer
​ ​*​ ​@date​ ​Feb 2 2018
​ ​*​ ​@version​ ​1.0
​ ​*
​ ​*/

#ifndef DLL_H_INCLUDED
#define DLL_H_INCLUDED

typedef struct node {
    struct node *prev;
    struct node *next;
    int32_t data;
} Node;

/*As per instruction of Prof. Fosdick, I am leaving the structure as 
 *a standard double linked list rather than a value-abtracted linked 
 *list due to the conflicting architecture specification requiring 
 *an independent node data structure that must also take a specific 
 *data value and type from the info structure. */

typedef struct info {
    struct node *nd;
    int32_t data;
} Info;

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
Node * create(uint32_t data);

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
Node * insert_at_beginning(Node * head, uint32_t data);

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
Node * insert_at_end(Node * head, uint32_t data);

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
Node * insert_at_position(Node * head, int pos, uint32_t data);

/**
​ ​*​ ​@brief​ ​Remove a node
​ ​*
​ ​*​ ​Removes a node in a list. NOT FOR EXTERNAL USE.
​ ​*
 *​ ​@param​ nodeptr pointer to the node to remove
​ *
​ ​*​ ​@return​ Pointer to the head node
​ ​*/
int __remove(Node * nodeptr);

/**
​ ​*​ ​@brief​ Delete an entire linked list
​ ​*
​ ​*​ ​Deletes an entire linked list
​ ​*
 *​ ​@param​ ​head the head pointer of the list to destroy
​ *
​ ​*​ ​@return​ NULL node pointer
​ ​*/
Node * destroy(Node * head);

/**
​ ​*​ ​@brief​ ​Delete at beginning of the DLL
​ ​*
​ ​*​ ​Delete a node at the beginning of the doubly linked list
​ ​*
 *​ ​@param​ ​head the head pointer of the list to delete from
​ *
​ ​*​ ​@return​ Pointer to the head node
​ ​*/
Node * delete_from_beginning(Node * head);
/**
​ ​*​ ​@brief​ ​Delete at end of the DLL
​ ​*
​ ​*​ ​Delete a node at the end of the doubly linked list
​ ​*
 *​ ​@param​ ​head the head pointer of the list to delete from
​ *
​ ​*​ ​@return​ Pointer to the head node
​ ​*/
Node * delete_at_end(Node * head);


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
Node * delete_at_position(Node * head, int pos);

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
uint32_t peek_value(Node * head, uint32_t pos);

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
void printAll(Node * head);
