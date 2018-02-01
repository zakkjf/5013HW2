#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

typedef struct node {
    struct node *prev;
    struct node *next;
    //int32_t data;
} Node;

typedef struct info{
	uint32_t data;
	struct node *nd;
} Info;

Info * __create(uint32_t data);

/*  TO insert at beginning */
Info * insert_at_beginning(Info * head, uint32_t data);

/* To insert at end */
Info * insert_at_end(Info * head, uint32_t data);

/* To insert at any position */
Info * insert_at_position(Info * head, int pos, uint32_t data);

//not for external use
int __remove(Info * nodeptr);

Info * destroy(Info * head);

/*  TO delete at beginning */
Info * delete_from_beginning(Info * head);
/* To delete at end */
Info * delete_at_end(Info * head);

/* To delete at any position */
Info * delete_at_position(Info * head, int pos);

void printAll(Info * head);
#endif // MAIN_H_INCLUDED
