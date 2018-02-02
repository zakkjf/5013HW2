#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

typedef struct node {
    struct node *prev;
    struct node *next;
    int32_t data;
} Node;

//As per instruction of Prof. Fosdick, I am leaving the structure as 
//a standard double linked list rather than a value-abtracted linked 
//list due to the conflicting architecture specification requiring 
//an independent node data structure that must also take a specific 
//data value and type from the info structure

typedef struct node {
    struct node *prev;
    struct node *next;
    int32_t data;
} Node;

Node * create(uint32_t data);

/*  TO insert at beginning */
Node * insert_at_beginning(Node * head, uint32_t data);

/* To insert at end */
Node * insert_at_end(Node * head, uint32_t data);

/* To insert at any position */
Node * insert_at_position(Node * head, int pos, uint32_t data);

//not for external use
int __remove(Node * nodeptr);

Node * destroy(Node * head);

/*  TO delete at beginning */
Node * delete_from_beginning(Node * head);
/* To delete at end */
Node * delete_at_end(Node * head);

/* To delete at any position */
Node * delete_at_position(Node * head, int pos);

/* To peek at a position in the stack's stored data without modification*/
uint32_t peek_value(Node * head, uint32_t pos);

void printAll(Node * head);
#endif // MAIN_H_INCLUDED
