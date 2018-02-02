#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dll.h"

int main()
{

    Node * n1 = create(1);
    uint32_t i;
    for(i=2;i<10;i++)
    {
        n1 = insert_at_end(n1,i);
    }
    printAll(n1);

    n1=insert_at_position(n1,5,243);
    printAll(n1);
    n1=delete_at_position(n1,5);

    printAll(n1);

    n1 = destroy(n1);
    printAll(n1);

    return 0;
}
