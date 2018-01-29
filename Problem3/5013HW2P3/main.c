#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 256

int main()
{

    srand(time(0));
    int32_t *ptr1 = (int32_t *) malloc(SIZE * sizeof (int32_t));
    int32_t *ptr2 = (int32_t *) malloc(SIZE * sizeof (int32_t));


    int32_t i;
    for(i=0;i<SIZE;i++)
    {
        *(ptr1+i) = (rand()%1000);
    }

    clock_t start = clock(), diff;
    syscall(333, ptr1, ptr2, SIZE);
    diff = clock() - start;

    printf("Presort\tPostsort\n");

    for(i=0;i<SIZE;i++)
    {
        printf("%d\t%d\n",*(ptr1+i),*(ptr2+i));
    }

    int msec = diff * 1000000 / CLOCKS_PER_SEC;
    printf("Time taken %d seconds %d milliseconds", msec/1000000, msec%1000000);

    return 0;
}
