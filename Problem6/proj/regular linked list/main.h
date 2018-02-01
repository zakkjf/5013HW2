#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

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

void printAll(Node * head);
#endif // MAIN_H_INCLUDED
